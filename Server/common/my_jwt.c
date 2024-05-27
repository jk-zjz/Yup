//
// Created by 35148 on 2024/3/13.
//

#include <stdlib.h>
#include "my_jwt.h"

jwt_t *jwt_init(const char *Key, const char *json) {
    jwt_t *jwt = NULL;
    int ret = jwt_new(&jwt);
    if (ret != 0) {
        LOG("jwt", "error", "jwt_new   [%d]\n", __LINE__);
    }
    ret = jwt_set_alg(jwt, JWT_ALG_HS256, (unsigned char *) Key, strlen(Key));
    if (ret != 0) {
        LOG("jwt", "error", "jwt_set_alg   [%d]\n", __LINE__);
    }
    return jwt;
}

//加密
char *jwt_encryption(const char *Key, const char *json) {

    jwt_t *jwt = NULL;
    int ret = jwt_new(&jwt);
    if (ret != 0) {
        LOG("jwt", "error", "jwt_new fial %d\n", __LINE__);
        return NULL;
    }
    ret = jwt_add_grants_json(jwt, json);
    if (ret != 0) {
        LOG("jwt", "error", "jwt_add_grants_json fial %d\n", __LINE__);
        return NULL;
    }
    ret = jwt_set_alg(jwt, JWT_ALG_HS256, (unsigned char *) Key, strlen(Key));
    if (ret != 0) {
        LOG("jwt", "error", "jwt_set_alg fial %d\n", __LINE__);
        return NULL;
    }
    LOG("jwt", "ok", "%s\n", jwt_dump_str(jwt, 1));
    LOG("jwt", "key", "%s--%s\n", jwt_encode_str(jwt), Key);
    char *buf = jwt_encode_str(jwt);
    jwt_free(jwt);
    return buf;
}

//解密--获取数据段
cJSON *jwt_decrypt(const char *data, const char *Key) {
    jwt_t *jwt_ = NULL;

    LOG("jwt","data","%s____%s\n",data,Key);
    int ret = jwt_decode(&jwt_, data, (const char unsigned *) Key, strlen(Key));

    if (ret != 0) {
        LOG("jwt", "error", "jwt_get_grants_json %d\n", __LINE__);
        return NULL;
    }
    char *token = jwt_dump_str(jwt_, 1);
    if (!token) {
        LOG("jwt","error","[%d]\n",__LINE__);
        return NULL;
    }
    char buf[128]={0};
    int i=0;
    char* breack = strstr(token,".")+2;
    while(true){
        buf[i]=*breack;
        if(*breack=='}'){
            break;
        }
        breack++;
        i++;
    }
    free(token);
    breack=NULL;
    token=NULL;
    return cJSON_Parse(buf);
}

/*
 * char buf[SHA256_DIGEST_LENGTH * 2 + 1];
 *
 *
 *
 * */
void sha256(const char* input, char outputBuffer[65]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(hash, &sha256);

    // 将哈希值转换为十六进制字符串
    int i = 0;
    for (; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
}

void sha256_K(char *buf, const char *data_) {
    sha256(data_,buf);
    LOG("sha256_K", "passwrod", "%s:%s\n",buf,data_);
}

int base64_encode(char *in_str, int in_len, char *out_str) {
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    size_t size = 0;

    if (in_str == NULL || out_str == NULL)
        return -1;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    // 设置Base64编码不添加换行符
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(bio, in_str, in_len);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bptr);
    memcpy(out_str, bptr->data, bptr->length);
    out_str[bptr->length] = '\0';
    size = bptr->length;

    BIO_free_all(bio);
    return (int)size;
}
