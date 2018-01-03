#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <wembed/wembed.h>

/**
 * @defgroup CONFIG_OPTION_WBD compile time options.
 * @{
 */

/**
 * @brief The number of milliseconds to wait in an event loop.
 */
#define CONFIG_OPTION_WBD_SERVICE_TIMEOUT              5000

/**
 * @brief The maximum number of bytes in a HTTP request body.
 */
#define CONFIG_OPTION_WBD_REQ_BODY_LIMIT               1048576

/** @}*/

bool config_load(const char *path, struct wembed_config *cfg);
void config_destroy();

bool config_get_boolean(const char *name);
int config_get_int(const char *name);
const char* config_get_string(const char *name);

#endif
