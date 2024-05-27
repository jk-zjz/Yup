//
// Created by 35148 on 2024/3/13.
//

#ifndef UNTITLED_MY_JWT_H
#define UNTITLED_MY_JWT_H
#include <jwt.h>
#include "make_log.h"
#include <stdio.h>
#include <string.h>
#include <cJSON.h>
#include "openssl/sha.h"
#include <stdbool.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
//创造jwt对象
jwt_t * jwt_init(const char * Key,const char * json);
//加密
char* jwt_encryption(const char * Key,const char * json);
//解密
cJSON* jwt_decrypt(const char  *data, const char *Key);


//sha256加密
void sha256_K(char * buf,const char * data);
//bas64加密
int base64_encode(char *in_str, int in_len, char *out_str);
#endif //UNTITLED_MY_JWT_H