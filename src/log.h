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

/**
 * Annotate a log message format argument as type char.
 *
 * @param x The format argument
 */
#define LOG_ARG_CHAR(x) ((char) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _c(x) LOG_ARG_CHAR(x)
#endif

/**
 * Annotate a log message format argument as type signed char.
 *
 * @param x The format argument
 */
#define LOG_ARG_SIGNED_CHAR(x) ((signed char) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _sc(x) LOG_ARG_SIGNED_CHAR(x)
#endif

/**
 * Annotate a log message format argument as type unsigned char.
 *
 * @param x The format argument
 */
#define LOG_ARG_UNSIGNED_CHAR(x) ((unsigned char) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _uc(x) LOG_ARG_UNSIGNED_CHAR(x)
#endif

/**
 * Annotate a log message format argument as type int.
 *
 * @param x The format argument
 */
#define LOG_ARG_INT(x) ((int) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _i(x) LOG_ARG_INT(x)
#endif

/**
 * Annotate a log message format argument as type unsigned int.
 *
 * @param x The format argument
 */
#define LOG_ARG_UNSIGNED_INT(x) ((unsigned int) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _u(x) LOG_ARG_UNSIGNED_INT(x)
#endif

/**
 * Annotate a log message format argument as type long.
 *
 * @param x The format argument
 */
#define LOG_ARG_LONG(x) ((long) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _l(x) LOG_ARG_LONG(x)
#endif

/**
 * Annotate a log message format argument as type unsigned long.
 *
 * @param x The format argument
 */
#define LOG_ARG_UNSIGNED_LONG(x) ((unsigned long) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _ul(x) LOG_ARG_UNSIGNED_LONG(x)
#endif

/**
 * Annotate a log message format argument as type long long.
 *
 * @param x The format argument
 */
#define LOG_ARG_LONG_LONG(x) ((long long) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _ll(x) LOG_ARG_LONG_LONG(x)
#endif

/**
 * Annotate a log message format argument as type unsigned long long.
 *
 * @param x The format argument
 */
#define LOG_ARG_UNSIGNED_LONG_LONG(x) ((unsigned long long) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _ull(x) LOG_ARG_UNSIGNED_LONG_LONG(x)
#endif

/**
 * Annotate a log message format argument as type float.
 *
 * @param x The format argument
 */
#define LOG_ARG_FLOAT(x) ((float) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _f(x) LOG_ARG_FLOAT(x)
#endif

/**
 * Annotate a log message format argument as type double.
 *
 * @param x The format argument
 */
#define LOG_ARG_DOUBLE(x) ((double) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _d(x) LOG_ARG_DOUBLE(x)
#endif

/**
 * Annotate a log message format argument as type long double.
 * 
 * @param x The format argument
 */
#define LOG_ARG_LONG_DOUBLE(x) ((long double) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _ld(x) LOG_ARG_LONG_DOUBLE(x)
#endif

/**
 * Annotate a log message format argument as a string.
 *
 * @param x The format argument
 */
#define LOG_ARG_STR(x) ((const char*) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _str(x) LOG_ARG_STR(x)
#endif

/**
 * Annotate a log message format argument as type pointer.
 *
 * @param x The format argument
 */
#define LOG_ARG_PTR(x) ((void*) (x))

#ifndef LOG_NO_SHORT_ARGS
#define _ptr(x) LOG_ARG_PTR(x)
#endif

#endif // #ifndef LOG_H
