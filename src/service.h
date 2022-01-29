/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_H
#define SERVICE_H

#include <stddef.h>

struct service_connection;
struct service_iface;

/** An app service definition. */
struct service {
  /** The service name. */
  const char* name;

  /** The service description. */
  const char* desc;

  /** The service interface. */
  struct service_iface* iface;

  /** The internal service state. */
  struct service_state* state;
};

/** A service interface. */
struct service_iface {
  /**
   * Called after the service loads.
   *
   * @param svc The service definition
   */
  void (* on_load)(struct service* svc);

  /**
   * Called before the service unloads.
   *
   * @param svc The service definition
   */
  void (* on_unload)(struct service* svc);

  /**
   * Called after the service starts.
   *
   * @param svc The service definition
   */
  void (* on_start)(struct service* svc);

  /**
   * Called before the service stops.
   *
   * @param svc The service definition
   */
  void (* on_stop)(struct service* svc);

  /**
   * Called when a client connects to the service.
   *
   * @param svc The service definition
   * @param conn The service connection
   * @return An arbitrary userdata pointer
   */
  void* (* on_connect)(struct service* svc, struct service_connection* conn);

  /**
   * Called when a client disconnects from the service.
   *
   * @param svc The service definition
   * @param conn The service connection
   * @param userdata The userdata pointer provided during connection
   */
  void (* on_disconnect)(struct service* svc, struct service_connection* conn, void* userdata);
};

/** Info for a connection to a service. */
struct service_connection;

/** State for a service. */
struct service_state;

/** The status of a service. */
enum service_status {
  service_status_ready = 0,
  service_status_started,
  service_status_stopped,
};

/**
 * Load a defined service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_load(struct service* svc);

/**
 * Unload a defined service.
 *
 * It may not be re-loaded again in this process.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_unload(struct service* svc);

/**
 * Start a service.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_start(struct service* svc);

/**
 * Stop a service.
 *
 * It may be restarted at a later time.
 *
 * @param svc The service definition
 * @return Zero on success, otherwise nonzero
 */
int service_stop(struct service* svc);

/**
 * Connect to a service for communication.
 *
 * @param svc The service definition
 * @return The service connection
 */
struct service_connection* service_connect(struct service* svc);

/**
 * Disconnect a service connection.
 *
 * @param conn The service connection
 * @return Zero on success, otherwise nonzero
 */
int service_disconnect(struct service_connection* conn);

/**
 * Open a service connection for local read.
 *
 * This should only be called on the local (non-service) end of a connection.
 *
 * The result of calling this function is a real Unix file descriptor. All valid
 * Unix file I/O applies to this read-only file descriptor.
 *
 * @param conn The service connection
 * @return A read-only Unix file descriptor
 */
int service_local_read(struct service_connection* conn);

/**
 * Open a service connection for local write.
 *
 * This should only be called on the local (non-service) end of a connection.
 *
 * The result of calling this function is a real Unix file descriptor. All valid
 * Unix file I/O applies to this write-only file descriptor.
 *
 * @param conn The service connection
 * @return A write-only Unix file descriptor
 */
int service_local_write(struct service_connection* conn);

/**
 * Open a service connection for remote read.
 *
 * This should only be called on the remote (service) end of a connection.
 *
 * The result of calling this function is a real Unix file descriptor. All valid
 * Unix file I/O applies to this read-only file descriptor.
 *
 * @param conn The service connection
 * @return A read-only Unix file descriptor
 */
int service_remote_read(struct service_connection* conn);

/**
 * Open a service connection for remote write.
 *
 * This should only be called on the remote (service) end of a connection.
 *
 * The result of calling this function is a real Unix file descriptor. All valid
 * Unix file I/O applies to this write-only file descriptor.
 *
 * @param conn The service connection
 * @return A write-only Unix file descriptor
 */
int service_remote_write(struct service_connection* conn);

/**
 * Access userdata in a service connection.
 *
 * This should only be called on the remote (service) end of a connection.
 *
 * @param conn The service connection
 * @return The userdata on the connection
 */
void* service_remote_userdata(struct service_connection* conn);

#endif // #ifndef SERVICE_H
