#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <wembed/wembed.h>

extern struct wembed_json_rest_module_routes tank_router;


void validate_json(struct wembed_json_rest_response *res, json_object *jsonObj);
void control_if_exists(json_object *request, json_object **state, char* key, struct wembed_json_rest_response *res);
void handle_camera(unsigned char* bytes, int len);
unsigned char* hexstr_to_char(const char* hexstr);

#endif
