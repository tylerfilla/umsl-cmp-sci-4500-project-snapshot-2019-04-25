/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#include <stdio.h>

#include "global.h"
#include "log.h"

int main(int argc, char* argv[]) {
  g_mut->argc = argc;
  g_mut->argv = (const char**) argv;

  printf("Hello, world!\n");

  LOGT("Test %s", "TRACE");
  LOGD("Test %s", "DEBUG");
  LOGI("Test %s", "INFO");
  LOGW("Test %s", "WARN");
  LOGE("Test %s", "ERROR");
  LOGF("Test %s", "FATAL");
}
