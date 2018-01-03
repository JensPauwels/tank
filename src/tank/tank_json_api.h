#ifndef TANK_H
#define TANK_H

#include <wembed/wembed.h>

extern struct wembed_json_rest_module_routes tank_router;

void tank_api_get_gpio(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res);
void tank_api_set_gpio(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res);
void tank_api_set_camera(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res);
void tank_api_login(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res);
void tank_api_get_temperature(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res);
#endif
