#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wembed/wembed.h>
#include "config/config.h"
#include "tank/tank_json_api.h"

/**
 * @brief The tank API interface router.
 */
struct wembed_json_rest_routes tank_server_router = {
    .api_prefix = "api",
    .error_handlers = { },
    .modules = {
        &tank_router,
        NULL
    }
};


int main(int argc, char** argv)
{
    /* Check if the configuration file is given as a program argument  */
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <configfile>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Create empty wembed configuration structure */
    struct wembed_config cfg = {0};

    /* Load the configuration */
    if(!config_load(argv[1], &cfg)) {
        fprintf(stderr, "[SETTINGS] The application configuration could not be loaded, exiting\n");
        return EXIT_FAILURE;
    }

    /* Initialize the JSON RESTful router and wembed */
    wembed_json_rest_init(&cfg, &tank_server_router, NULL);

    /* Initialize the wembed server */
    wembed_init(&cfg);
    /* Daemonize if needed */
    wembed_daemonize(config_get_boolean("daemonize"));

    /* Write the PID file */
    if(!wembed_write_pidfile(config_get_string("pid_file"))) {
        wembed_log(WEMBED_LOG_ERROR, "[TANK-SERVER] Could not create PID file '%s'\n", config_get_string("pid_file"));
        return EXIT_FAILURE;
    }

    /* Start the wembed event loop */
    while(wembed_service());

    return EXIT_SUCCESS;
}
