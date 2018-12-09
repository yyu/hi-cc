/*
 * build
 *
 *   $ gcc `curl-config --libs` philips_hue.c
 *
 * usage
 *
 *   $ ./a.out on
 *   $ ./a.out off
 *
 *   which are equivalent to
 *
 *   $ curl -X PUT -d '{"on":true}' 192.168.10.110/api/sUvh09ovb7BgQnPjONJB19jsZuoEMMb91tI0nCAm/lights/1/state
 *   $ curl -X PUT -d '{"on":false}' 192.168.10.110/api/sUvh09ovb7BgQnPjONJB19jsZuoEMMb91tI0nCAm/lights/1/state
 *
 *   respectively
 *
 * see also
 *
 *   libcurl
 *
 *     https://curl.haxx.se/libcurl/c/post-callback.html
 *     https://curl.haxx.se/libcurl/c/httpput.html
 *
 *   philips hue
 *
 *     https://developers.meethue.com/develop/get-started/
 *
 * will do something like
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define HUE_IP "192.168.10.110"
#define HUE_USER "sUvh09ovb7BgQnPjONJB19jsZuoEMMb91tI0nCAm"

/*
 * payload is tiny; safely assuming data size < (size * nmemb)
 */
static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
    //fprintf(stderr, "stream: %s, size: %zu, nmemb: %zu\n", stream, size, nmemb);
    int len = strlen(stream);
    memcpy(ptr, stream, len);
    return len;
}

void usage(char * prog) {
    fprintf(stderr, "Usage: %s [on|off]\n", prog);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    char payload[] = "{\"on\":     }";
    //                        ^^^^^will be replaced with " true" or "false"
    char * placeholder = strchr(payload, ' '); 

    if (strcmp(argv[1], "on") == 0) {
        memcpy(placeholder, " true", 5);
    } else if (strcmp(argv[1], "off") == 0) {
        memcpy(placeholder, "false", 5);
    } else {
        usage(argv[0]);
        return 2;
    }

    curl_global_init(CURL_GLOBAL_ALL); /* In windows, this will init the winsock stuff */

    CURL * curl = curl_easy_init(); /* get a curl handle */
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); /* enable uploading */
        curl_easy_setopt(curl, CURLOPT_PUT, 1L); /* HTTP PUT please */
        curl_easy_setopt(curl, CURLOPT_URL, "http://"HUE_IP"/api/"HUE_USER"/lights/2/state");
        curl_easy_setopt(curl, CURLOPT_READDATA, payload);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, (long)strlen(payload));

        CURLcode res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl); /* always cleanup */
    }

    curl_global_cleanup();

    fprintf(stdout, "\n");

    return 0;
}
