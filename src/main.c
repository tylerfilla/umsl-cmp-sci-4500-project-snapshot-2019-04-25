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

  LOGT("Test %s", _str("TRACE"));
  LOGD("Test %s", _str("DEBUG"));
  LOGI("Test %s", _str("INFO"));
  LOGW("Test %s", _str("WARN"));
  LOGE("Test %s", _str("ERROR"));
  LOGF("Test %s", _str("FATAL"));
}
