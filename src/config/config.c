#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <wembed/wembed.h>

#include "config.h"

/**
 * @brief The configuration JSON object.
 */
json_object *_config_json = NULL;

/**
 * @brief Path to the log output file.
 */
char *_config_logfile = NULL;

/**
 * @brief Path to the session file.
 */
char *_config_session_file = NULL;

/**
 * @brief A list of required configuration file options.
 */
const char *_config_required_entries[] = {
    "daemonize",
    "listen_port",
    "loglevel",
    "logfile",
    "pid_file",
    "persistent_db"
};

/**
 * @brief Check if all required configuration parameters are present.
 *
 * This function loops through all the required configuration file
 * entries and checks if they exist in the parsed configuration file.
 *
 * @return True when all required parameters are present.
 */
static bool _config_check_required_config_entries() {
    json_object *j_tmp;
    int i;

    for (i = 0; i < (sizeof (_config_required_entries) / sizeof (_config_required_entries[0])); i++) {
        json_object_object_get_ex(_config_json, _config_required_entries[i], &j_tmp);
        if (!j_tmp) {
            fprintf(stderr, "Required config parameter '%s' is missing.\n", _config_required_entries[i]);
            return false;
        }
    }
    return true;
}

/**
 * @brief This function parses the wembed config level.
 *
 * The wembed logging level is parsed from the string in the configuration file.
 *
 * @param The string representation of the log level.
 *
 * @return The wembed log level or WEMBED_LOG_ERROR when the level was not recognized.
 */
static enum wembed_log_level _config_parse_loglevel(const char *level) {
    if (level && strlen(level)) {
        switch (level[0]) {
            case 'N': return WEMBED_LOG_NONE;
            case 'E': return WEMBED_LOG_ERROR;
            case 'W': return WEMBED_LOG_WARNING;
            case 'I': return WEMBED_LOG_INFO;
            case 'D': return WEMBED_LOG_DEBUG;

            default:
                fprintf(stderr, "The configuration file did not contain a valid logging level, falling back to LOG_ERROR\n");
                return WEMBED_LOG_ERROR;
                break;
        }
    } else {
        fprintf(stderr, "The configuration file did not specify a logging level, falling back to LOG_ERROR\n");
        return WEMBED_LOG_ERROR;
    }
}

/**
 * @brief Load the configuration file.
 *
 * This function parses the JSON configuration file and checks if all the
 * required configuration parameters are present.
 *
 * @param path The path where to find the configuration file.
 * @param cfg The wembed configuration for low level network configuration.
 *
 * @return True if the configuration could be parsed successfully.
 */
bool config_load(const char *path, struct wembed_config *cfg)
{
    /* Free the JSON configuration file if there is one */
    if(_config_json != NULL) {
        json_object_put(_config_json);
    }

    /* Try to load the JSON configuration file */
    _config_json = json_object_from_file(path);
    if(_config_json == NULL) {
        fprintf(stderr, "Could not parse the JSOn configuration file '%s'\n", path);
        return false;
    }

    /* Check if the required configuration file entries are present */
    if(!_config_check_required_config_entries()) {
        return false;
    }

    /* Prepare the internal wembed configuration and apply compile time options */
    cfg->service_timeout = CONFIG_OPTION_WBD_SERVICE_TIMEOUT;
    cfg->req_body_limit = CONFIG_OPTION_WBD_REQ_BODY_LIMIT;
    cfg->use_ipv6 = false;
    cfg->loglevel = _config_parse_loglevel(config_get_string("loglevel"));
    _config_logfile = strdup(config_get_string("logfile"));
    cfg->logfile = _config_logfile;
    cfg->port = config_get_int("listen_port");
    cfg->ws_protocols = NULL;
    cfg->pbkdf2_hash_mech = WEMBED_PASSWORD_HASH_SHA512;
    cfg->pbkdf2_iterations = 5000;
    _config_session_file = strdup(config_get_string("session_file"));
    cfg->session_storage_path = _config_session_file;
    cfg->session_expire_time = 30;

    return true;
}

/**
 * @brief Destroy the application wide configuration.
 *
 * This function will release the memory used by the
 * application wide configuration.
 *
 * @return None
 */
void config_destroy()
{
    /* Free strings */
    free(_config_logfile);
    free(_config_session_file);

    /* Release parsed JSON and return */
    json_object_put(_config_json);
}


/**
 * @brief This function returns a configuration boolean.
 *
 * This function tries to parse a boolean from the JSon configuration
 * object.
 *
 * @param name The name of the configuration parameter.
 *
 * @return The configuration parameter.
 */
bool config_get_boolean(const char *name)
{
    json_object *j_tmp;

    json_object_object_get_ex(_config_json, name, &j_tmp);
    return json_object_get_boolean(j_tmp);
}

/**
 * @brief This function returns a configuration integer.
 *
 * This function tries to parse an integer from the JSON configuration object.
 *
 * @param name The name of the configuration parameter.
 *
 * @return The configuration integer.
 */
int config_get_int (const char *name)
{
    json_object *j_tmp;

    json_object_object_get_ex(_config_json, name, &j_tmp);
    return json_object_get_int(j_tmp);
}


/**
 * @brief This function returns a configuration string.
 *
 * This function tries to parse a string from the JSON configuration object.
 *
 * @param name The name of the configuration parameter.
 *
 * @return The configuration string.
 */
const char * config_get_string (const char *name)
{
    json_object *j_tmp;

    json_object_object_get_ex(_config_json, name, &j_tmp);
    return json_object_get_string(j_tmp);
}
