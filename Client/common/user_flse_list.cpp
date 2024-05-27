#include "user_flse_list.h"

User_Flse_List::User_Flse_List() {}

User_Flse_List::User_Flse_List(unsigned int id, QString sha256, QString createtime, QString filename, bool shared_status, unsigned int pv)
{
    this->id=id;
    this->sha256=sha256;
    this->createtime=createtime;
    this->filename=filename;
    this->shared_status=shared_status;
    this->pv=pv;
}
void User_Flse_List::to_string()
{
    qDebug()<<this->id<<"-"<<this->sha256<<"-"<<this->createtime<<"-"<<this->filename<<"-"<<this->shared_status<<"-"<<this->pv;
}
