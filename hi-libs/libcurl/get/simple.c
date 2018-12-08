#include <stdio.h>
#include <curl/curl.h>

void do_curl(char * url)
{
    CURL * curl = curl_easy_init();

    if(!curl) {
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
        fprintf(stderr, "\033[37mcurl_easy_perform() failed: %s\033[0m\n", curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
}

int main(int argc, char * argv[])
{
    char * url = "https://yuyuan.org";

    if (argc < 2) {
        fprintf(stderr, "\033[37mUsage: %s hostname\n\033[0m", argv[0]);
        fprintf(stderr, "\033[37mUsing default hostname: %s\033[0m\n", url);
    } else {
        url = argv[1];

        if (argc > 2) {
            fprintf(stderr, "\033[37mUsage: %s hostname\033[0m\n", argv[0]);
            fprintf(stderr, "\033[37mignoring args");
            for (int i = 2; i < argc; i++) {
                fprintf(stderr, " %s", argv[i]);
            }
            fprintf(stderr, "\033[0m\n");
        }
    }

    do_curl(url);

    return 0;
}
