#include <wembed/wembed.h>
#include "tank_json_api.h"

/**
 * @brief The GET routes from the tank module.
 */
struct wembed_json_rest_module_handler tank_post_routes[] = {
    {
        .url = "login",
        .user_handler = tank_api_login,
    },
    {
        .url = "camera",
        .user_handler = tank_api_set_camera
    },
    {
        .url = NULL,
        .user_handler = NULL
    }
};

struct wembed_json_rest_module_handler tank_get_routes[] = {
    {
        .url = "gpio/%d",
        .user_handler = tank_api_get_gpio,
    },
    {
        .url = "temperature",
        .user_handler = tank_api_get_temperature
    },
    {
        .url = NULL,
        .user_handler = NULL,
    }
};

/**
 * @brief The GET routes from the tank module.
 */
struct wembed_json_rest_module_handler tank_put_routes[] = {
    {
        .url = "gpio/%d",
        .user_handler = tank_api_set_gpio,
    },
    {
        .url = NULL,
        .user_handler = NULL,
    }
};

/**
 * @brief The LAN network module router.
 */
struct wembed_json_rest_module_routes tank_router = {
    .module_prefix = "tank",
    .module_handlers = {
        [WEMBED_HTTP_METHOD_GET] = tank_get_routes,
        [WEMBED_HTTP_METHOD_PUT] = tank_put_routes,
        [WEMBED_HTTP_METHOD_POST] = tank_post_routes,
        [WEMBED_HTTP_METHOD_DELETE] = NULL,
        [WEMBED_HTTP_METHOD_PATCH] = NULL,
    }
};
