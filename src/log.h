/*
 * Cozmonaut
 * Copyright 2019 The Cozmonaut Contributors
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/** A log severity level. */
enum log_level {
  log_level_trace,
  log_level_debug,
  log_level_info,
  log_level_warn,
  log_level_error,
  log_level_fatal,
};

/**
 * Get the name of a log level.
 *
 * @param lvl The log level
 * @return The log level name
 */
inline static const char* log_level_name(enum log_level lvl) {
  switch (lvl) {
    case log_level_trace:
      return "TRACE";
    case log_level_debug:
      return "DEBUG";
    case log_level_info:
      return "INFO";
    case log_level_warn:
      return "WARN";
    case log_level_error:
      return "ERROR";
    case log_level_fatal:
      return "FATAL";
    default:
      return NULL;
  }
}

/**
 * Log with the given level.
 *
 * @param lvl The log level
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOG(lvl, fmt, ...)                  \
    do {                                    \
      printf("%s: ", log_level_name(lvl));  \
      printf(fmt, ##__VA_ARGS__);           \
      printf("\n");                         \
    } while (0)

/**
 * Log with TRACE severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGT(fmt, ...) LOG(log_level_trace, (fmt), ##__VA_ARGS__)

/**
 * Log with DEBUG severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGD(fmt, ...) LOG(log_level_debug, (fmt), ##__VA_ARGS__)

/**
 * Log with INFO severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGI(fmt, ...) LOG(log_level_info, (fmt), ##__VA_ARGS__)

/**
 * Log with WARN severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGW(fmt, ...) LOG(log_level_warn, (fmt), ##__VA_ARGS__)

/**
 * Log with ERROR severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGE(fmt, ...) LOG(log_level_error, (fmt), ##__VA_ARGS__)

/**
 * Log with FATAL severity.
 *
 * @param fmt The message format string
 * @param ... The message format arguments
 */
#define LOGF(fmt, ...) LOG(log_level_fatal, (fmt), ##__VA_ARGS__)

#endif // #ifndef LOG_H
