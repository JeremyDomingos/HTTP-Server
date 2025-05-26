// This header file contains functions that assits in evealuting URL's from 
// clients and processing them


#ifndef URL_PROC_H
#define URL_PROC_H

#define MAX_URL_LENGTH 2048
// check for vaild scheme
void isUrl(char URL[MAX_URL_LENGTH]);
// Evaluate Parameters
void check_url_len(char URL[MAX_URL_LENGTH]);
void evalu_url(char URL[MAX_URL_LENGTH]);



#endif