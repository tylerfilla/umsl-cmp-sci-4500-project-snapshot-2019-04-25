/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdlib.h>

#include "log.h"
#include "service.h"

/** An internal service state. */
struct service_state {
  /** The service status. */
  enum service_status status;
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
    case service_status_started:
      break;
    case service_status_ready:
    case service_status_stopped:
      goto not_started;
  }

  // The service interface
  struct service_iface* iface = svc->iface;

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
