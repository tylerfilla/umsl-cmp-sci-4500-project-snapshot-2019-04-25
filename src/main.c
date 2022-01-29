/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include "client.h"
#include "global.h"
#include "log.h"
#include "monitor.h"
#include "service.h"

int main(int argc, char* argv[]) {
  g_mut->argc = argc;
  g_mut->argv = (const char**) argv;

  service_load(CLIENT_SERVICE);
  service_load(MONITOR_SERVICE);

  service_start(CLIENT_SERVICE);
  service_start(MONITOR_SERVICE);

  // Connect to the monitor service
  struct service_connection* conn = service_connect(MONITOR_SERVICE);
  int fdr = service_local_read(conn);
  int fdw = service_local_write(conn);

  // Disconnect from the monitor service
  service_disconnect(conn);

  service_stop(MONITOR_SERVICE);
  service_stop(CLIENT_SERVICE);

  service_unload(MONITOR_SERVICE);
  service_unload(CLIENT_SERVICE);
}
