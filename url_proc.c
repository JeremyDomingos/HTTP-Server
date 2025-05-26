#include "url_proc.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 2048

void isUrl(char URL[MAX_URL_LENGTH])
{
    if (sizeof(URL) > MAX_URL_LENGTH)
    {
        printf("Invalid Url: Max Size");
    }
    else
    {
        }
}
void check_url_len(char URL[MAX_URL_LENGTH]);
void evalu_url(char URL[MAX_URL_LENGTH]);