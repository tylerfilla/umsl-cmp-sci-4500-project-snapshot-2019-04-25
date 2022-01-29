/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "log.h"
#include "service.h"

/** An internal service state. */
struct service_state {
  /** The service status. */
  enum service_status status;

  /** The number of connections. */
  int connections;
};

int service_load(struct service* svc) {
  if (!svc) {
    return 1;
  }

  LOGD("Request to load service \"%s\"", _str(svc->name));

  if (svc->state) {
    // A service with state is already loaded
    goto already_loaded;
  } else {
    svc->state = calloc(1, sizeof(struct service_state));
  }

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call load callback if present
  if (iface->on_load) {
    iface->on_load(svc);
  }

  LOGI("Service \"%s\" was loaded successfully", _str(svc->name));
  return 0;

already_loaded:
  LOGE("Service \"%s\" is already loaded", _str(svc->name));
  return 1;
}

int service_unload(struct service* svc) {
  if (!svc) {
    return 1;
  }

  LOGD("Request to unload service \"%s\"", _str(svc->name));

  if (!svc->state) {
    // A service without state is not loaded
    goto not_loaded;
  }

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call unload callback if present
  if (iface->on_unload) {
    iface->on_unload(svc);
  }

  free(svc->state);
  svc->state = NULL;

  LOGI("Service \"%s\" was unloaded successfully", _str(svc->name));
  return 0;

not_loaded:
  LOGE("Service \"%s\" is not loaded", _str(svc->name));
  return 1;
}

int service_start(struct service* svc) {
  if (!svc) {
    return 1;
  }

  LOGD("Request to start service \"%s\"", _str(svc->name));

  if (!svc->state) {
    // A service without state is not ready
    goto not_ready;
  }

  switch (svc->state->status) {
    case service_status_started:
      goto not_ready;
    case service_status_ready:
    case service_status_stopped:
      break;
  }

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call start callback if present
  if (iface->on_start) {
    iface->on_start(svc);
  }

  // Update status
  svc->state->status = service_status_started;

  LOGI("Service \"%s\" was started successfully", _str(svc->name));
  LOGI("%s", _str(svc->desc));
  return 0;

not_ready:
  LOGE("Service \"%s\" is not ready", _str(svc->name));
  return 1;
}

int service_stop(struct service* svc) {
  if (!svc) {
    return 1;
  }

  LOGD("Request to stop service \"%s\"", _str(svc->name));

  if (!svc->state) {
    // A service without state is not started
    goto not_started;
  }

  switch (svc->state->status) {
    case service_status_ready:
    case service_status_stopped:
      goto not_started;
    case service_status_started:
      break;
  }

  // If service has outstanding connections...
  if (svc->state->connections > 0) {
    // We won't stop the shutdown, but we will leak memory
    LOGW("Service \"%s\" has %d outstanding connections! LEAKING...", _str(svc->name), _i(svc->state->connections));
  }

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call stop callback if present
  if (iface->on_stop) {
    iface->on_stop(svc);
  }

  // Update status
  svc->state->status = service_status_stopped;

  LOGI("Service \"%s\" was stopped successfully", _str(svc->name));
  return 0;

not_started:
  LOGE("Service \"%s\" is not started", _str(svc->name));
  return 1;
}

struct service_connection {
  /** The connected service. */
  struct service* svc;

  /** Read (0) and write (1) file descriptors for client->service transfer. */
  int fds_local[2];

  /** Read (0) and write (1) file descriptors for service->client transfer. */
  int fds_remote[2];

  /** An arbitrary userdata pointer. */
  void* userdata;
};

struct service_connection* service_connect(struct service* svc) {
  if (!svc || !svc->state) {
    return NULL;
  }

  LOGD("Request to connect to service \"%s\"", _str(svc->name));

  switch (svc->state->status) {
    case service_status_ready:
    case service_status_stopped:
      LOGE("Service \"%s\" is not running", _str(svc->name));
      return NULL;
    case service_status_started:
      break;
  }

  // Allocate connection instance
  struct service_connection* conn = calloc(1, sizeof(struct service_connection));
  conn->svc = svc;

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call connect callback if present
  if (iface->on_connect) {
    // The connect callback can provide userdata
    void* userdata = iface->on_connect(svc, conn);

    // Squirrel it away in the connection
    conn->userdata = userdata;
  }

  // Try to establish local (client->service) anonymous pipe
  if (pipe(conn->fds_local)) {
    LOGE("Failed to create local pipe: %d", errno);
    free(conn);
    return NULL;
  }

  // Try to establish remote (service->client) anonymous pipe
  if (pipe(conn->fds_remote)) {
    LOGE("Failed to create remote pipe: %d", errno);
    free(conn);
    return NULL;
  }

  // Increment connection count on service
  ++svc->state->connections;

  return conn;
}

int service_disconnect(struct service_connection* conn) {
  if (!conn || !conn->svc || !conn->svc->state) {
    return 1;
  }

  // The connected service
  struct service* svc = conn->svc;

  LOGD("Request to disconnect from service \"%s\"", _str(svc->name));

  // The service interface
  struct service_iface* iface = svc->iface;

  // Call disconnect callback if present
  if (iface->on_disconnect) {
    // Also remind the service what their userdata was
    iface->on_disconnect(svc, conn, conn->userdata);
  }

  // Close everything
  int close_error = 0;
  close_error = close_error || close(conn->fds_local[0]);
  close_error = close_error || close(conn->fds_local[1]);
  close_error = close_error || close(conn->fds_remote[0]);
  close_error = close_error || close(conn->fds_remote[1]);

  // If not every file descriptor could be closed
  if (close_error) {
    LOGE("Failed to close all file descriptors");
  }

  // Decrement connection count on service
  --svc->state->connections;

  free(conn);
  return !close_error;
}

int service_local_read(struct service_connection* conn) {
  // The file descriptor is already open
  return conn->fds_local[0];
}

int service_local_write(struct service_connection* conn) {
  // The file descriptor is already open
  return conn->fds_local[1];
}

int service_remote_read(struct service_connection* conn) {
  // The file descriptor is already open
  return conn->fds_remote[0];
}

int service_remote_write(struct service_connection* conn) {
  // The file descriptor is already open
  return conn->fds_remote[1];
}

void* service_remote_userdata(struct service_connection* conn) {
  return conn->userdata;
}
