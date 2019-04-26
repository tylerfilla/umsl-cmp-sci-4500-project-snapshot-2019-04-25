/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "log.h"
#include "monitor.h"
#include "service.h"

/** Service load callback. */
static void on_load(struct service* svc) {
  LOGT("Monitor service loaded");
}

/** Service start callback. */
static void on_start(struct service* svc) {
  LOGT("Monitor service started");
}

/** Service stop callback. */
static void on_stop(struct service* svc) {
  LOGT("Monitor service stopping");
}

/** Service unload callback. */
static void on_unload(struct service* svc) {
  LOGT("Monitor service unloading");
}

static struct service_iface IFACE = {
  .on_load = &on_load,
  .on_start = &on_start,
  .on_stop = &on_stop,
  .on_unload = &on_unload,
};

struct service* const MONITOR_SERVICE = &(struct service) {
  .name = "monitor",
  .desc = "The monitor service renders monitor views.",
  .iface = &IFACE,
};
