/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <pthread.h>

#include "log.h"
#include "monitor.h"
#include "service.h"

/** The monitor thread. */
static pthread_t thread;

/** The monitor loop kill switch. */
static volatile int kill; // atomic x86_64 gcc gnu/linux

/**
 * The monitor thread main function.
 *
 * @param arg Not used
 * @return Not used
 */
static void* thread_main(void* arg) {
  LOGD("The monitor thread is online");

  // The monitor loop
  do {
    // Break out if kill switch is set
    if (kill) {
      break;
    }
  } while (1);

  LOGD("The monitor thread is shutting down");
  return arg;
}

/** Service load callback. */
static void on_load(struct service* svc) {
  LOGT("Monitor service loaded");
}

/** Service start callback. */
static void on_start(struct service* svc) {
  LOGT("Monitor service started");

  // Spawn the monitor thread
  kill = 0;
  pthread_create(&thread, NULL, &thread_main, NULL); // extern barrier after kill = 0
}

/** Service stop callback. */
static void on_stop(struct service* svc) {
  LOGT("Monitor service stopping");

  // Kill the monitor thread
  kill = 1;
  pthread_join(thread, NULL); // extern barrier after kill = 1
}

/** Service unload callback. */
static void on_unload(struct service* svc) {
  LOGT("Monitor service unloading");
}

/** Service connect callback. */
static void* on_connect(struct service* svc, struct service_connection* conn) {
  LOGT("Incoming connection to monitor service");
  return NULL;
}

static void on_disconnect(struct service* svc, struct service_connection* conn, void* userdata) {
  LOGT("Monitor service detects a connection lost");
}

static struct service_iface IFACE = {
  .on_load = &on_load,
  .on_start = &on_start,
  .on_stop = &on_stop,
  .on_unload = &on_unload,
  .on_connect = &on_connect,
  .on_disconnect = &on_disconnect,
};

struct service* const MONITOR_SERVICE = &(struct service) {
  .name = "monitor",
  .desc = "The monitor service renders monitor views",
  .iface = &IFACE,
};
