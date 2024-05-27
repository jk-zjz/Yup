#include <my_http_analysis.h>
void delet_file(HTTP_fiel_information * HTTP){
    int i=0;
    for(;i<HTTP->size;i++){
        if(HTTP->hhtp_head[i].data!=NULL){
            free(HTTP->hhtp_head[i].data);
        }
    }
    free(HTTP);
    HTTP=NULL;
}
HTTP_fiel_information* init_file_size(char * data){
    HTTP_fiel_information * P =(HTTP_fiel_information *)malloc(sizeof (HTTP_fiel_information));
    P->size=0;
    char * start = strstr(data,";");
    if(start==NULL){
        strcpy(P->Content_Disposition,strstr(data,"/")+1);
        strcpy(P->KEY,"NULL");
        P->type=false;
        return P;
    }
    strcpy(P->Content_Disposition,"txt");
    strcpy(P->KEY,strrchr(data,'-')+1);
    P->type=true;
    return P;
}

void data_migration(const char * file_name,HTTP_fiel_information * HTTP)
{
    bool key_=false;
    bool rn=false;
    bool HTTP_DATA =true;
    int Counting_key_=0;
    size_t lien =0;
    FILE  * file = fopen(file_name,"r");
    char line[1000];
    FILE  * file_2 = fopen("./R-C.jpg","w");
    while (fgets(line, sizeof(line), file) != NULL) {
        // 在这里处理每一行数据
        LOG("file","data","%s\n",line);
        if(strstr(line,HTTP->KEY)!=NULL){
            key_=true;
            Counting_key_++;
        }
        if(Counting_key_>1){
            Counting_key_=1;
            key_=true;
            rn = false;
            HTTP_DATA=true;
            //上传
            fclose(file_2);
            HTTP->size++;
            continue;
        }
        if(lien<5){
            char * i = strstr(line,":");
            if(i&&HTTP_DATA){
                memccpy(HTTP->Content_Disposition,i+1,';',29);
                char * name = strrchr(i,'=');
                memccpy(HTTP->hhtp_head[HTTP->size].filename,name+1,';',99);
                HTTP_DATA=false;
            }
        }
        if(rn&&key_){
            fwrite(line,1, strlen(line),file_2);
        }
        if(!strcmp(line,"\r\n")){
            rn=true;
        }
        lien++;
    }
    fclose(file);

}
