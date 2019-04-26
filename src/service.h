/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef SERVICE_H
#define SERVICE_H

struct service_iface;
struct service_state;

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
};

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

#endif // #ifndef SERVICE_H
