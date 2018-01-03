
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wembed/wembed.h>
#include "helper_functions.h"


void validate_json(struct wembed_json_rest_response *res, struct json_object *json_obj) {
    if(json_obj == NULL) {
        json_object_put(json_obj);
        res->http_result = WEMBED_HTTP_RES_BAD_REQUEST;
        wembed_log(WEMBED_LOG_ERROR, "received invalid JSON while setting GPIO");
        return;
    }
}

void control_if_exists(struct json_object *request, struct json_object **state, char* key, struct wembed_json_rest_response *res) {
    if(!json_object_object_get_ex(request, key, state)) {
        json_object_put(request);
        res->http_result = WEMBED_HTTP_RES_BAD_REQUEST;
        return;
    }
}

unsigned char* hexstr_to_char(const char* hexstr){
    size_t len = strlen(hexstr);
    if(len % 2 != 0) return NULL;
    size_t final_len = len / 2;
    unsigned char* chrs = (unsigned char*)malloc((final_len+1) * sizeof(*chrs));
    for (size_t i=0, j=0; j<final_len; i+=2, j++)
        chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i+1] % 32 + 9) % 25;
    chrs[final_len] = '\0';
    return chrs;
}

void handle_camera(unsigned char* bytes, int len) {
    FILE *fp;
    fp = fopen("/dev/ttyATH0", "wb");
    fwrite(bytes, sizeof(uint8_t), len, fp);
    fclose(fp);
    free(bytes);
}
