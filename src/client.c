/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stddef.h>

#include "client.h"
#include "log.h"
#include "service.h"

/** Service load callback. */
static void on_load(struct service* svc) {
  LOGT("Client service loaded");
}

/** Service start callback. */
static void on_start(struct service* svc) {
  LOGT("Client service started");
}

/** Service stop callback. */
static void on_stop(struct service* svc) {
  LOGT("Client service stopping");
}

/** Service unload callback. */
static void on_unload(struct service* svc) {
  LOGT("Client service unloading");
}

static struct service_iface IFACE = {
  .on_load = &on_load,
  .on_start = &on_start,
  .on_stop = &on_stop,
  .on_unload = &on_unload,
};

struct service* const CLIENT_SERVICE = &(struct service) {
  .name = "client",
  .desc = "The client service hosts the Python interpreter and calls the entry point.",
  .iface = &IFACE,
};
