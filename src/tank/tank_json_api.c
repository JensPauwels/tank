#include <stdbool.h>
#include <wembed/wembed.h>
#include <stdio.h>
#include "gpio.h"
#include <string.h>
#include "tank_json_api.h"
#include "helper_functions.h"

void tank_api_get_gpio(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res) {
    int id = req->urlvars[0].integer;
    json_object_object_add(res->http_body, "state", json_object_new_int(gpio_get_state(id)));
    res->http_result = WEMBED_HTTP_RES_OK;
};

void tank_api_get_temperature(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res){
    // hier request doen voor mijn temperatuur
    json_object_object_add(res->http_body, "temperature", json_object_new_double(16.4));
    res->http_result = WEMBED_HTTP_RES_OK;
};

void tank_api_set_camera(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res) {

    json_object *request = json_tokener_parse(req->request_body);
    validate_json(res, request);

    json_object *hex_code = NULL;
    control_if_exists(request, &hex_code, "hex_code", res);

    const char *hexx = json_object_get_string(hex_code);
    wembed_log(WEMBED_LOG_INFO, "hexcode: %s", hexx);
    unsigned char* bytes = hexstr_to_char(hexx);
    int len = strlen(hexx) / 2;
    handle_camera(bytes, len);
    json_object_put(request);
    res->http_result = WEMBED_HTTP_RES_OK;
};

void tank_api_set_gpio(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res) {

    json_object *request = json_tokener_parse(req->request_body);
    validate_json(res, request);

    json_object *j_state = NULL;
    control_if_exists(request, &j_state, "state", res);
    bool state = json_object_get_boolean(j_state);

    int id = req->urlvars[0].integer;

    gpio_write_and_close(id, state ? 1 : 0);

    json_object_put(request);
    res->http_result = WEMBED_HTTP_RES_OK;
};

void tank_api_login(struct wembed_json_rest_request *req, struct wembed_json_rest_response *res) {
    json_object *request = json_tokener_parse(req->request_body);
    validate_json(res, request);

    char *username_to_compare = "jens.pauwels";
    char *password_to_compare = "123";

    json_object *j_username = NULL;
    json_object *j_password = NULL;

    control_if_exists(request, &j_username, "username", res);
    control_if_exists(request, &j_password, "password", res);

    const char *username = json_object_get_string(j_username);
    const char *password = json_object_get_string(j_password);

    //bool loggin_acces = ;
    //change to sha512 encryption
    json_object_object_add(res->http_body, "login_accepted", json_object_new_boolean(strcmp(username_to_compare, username) == 0 && strcmp(password_to_compare, password) == 0));

    json_object_put(request);
    res->http_result = WEMBED_HTTP_RES_OK;
};
