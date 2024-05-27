#include "singletoninfouser.h"

singletoninfouser* singletoninfouser::get_setinfouser()
{
    return infouser;
}

void singletoninfouser::setinfouser(QString user_, int id_, QString cookie_, QString ip_, QString port_)
{
    this->user=user_;
    this->id=id_;
    this->cookie=cookie_;
    this->ip=ip_;
    this->port=port_;
}

QString singletoninfouser::getuser() const
{
    return this->user;
}

int singletoninfouser::getid() const
{
    return this->id;
}

QString singletoninfouser::getcookie() const
{
    return this->cookie;
}

QString singletoninfouser::getip() const
{
    return this->ip;
}

QString singletoninfouser::getport() const
{
    return this->port;
}

void singletoninfouser::setiport(QString port, QString ip)
{
    this->ip=ip;
    this->port=port;
}

void singletoninfouser::set_user_info(USER_register* user_info)
{
    if(this->user_info!=NULL){
        delete(this->user_info);
    }
    this->user_info =user_info;
}

QString singletoninfouser::get_user_info()
{
    return user_info->user_account+":"
           + user_info->user_name+":"
           + user_info->user_password+":"
           + user_info->user_ac_passwrod+":"
           + user_info->user_phone+":"
           + user_info->user_EM+":";
}

USER_register *singletoninfouser::get_user_info_()
{
    return this->user_info;
}

bool singletoninfouser::get_request()
{
    return request;
}

void singletoninfouser::set_request(bool R)
{
    this->request=R;
}

QList<User_Flse_List> *singletoninfouser::get_FileList()
{
    return &this->file_list;
}

void singletoninfouser::erase_FileList()
{
    this->file_list.clear();
}

void singletoninfouser::show_FileList()
{
    for(auto &i:this->file_list){
        i.to_string();
    }
}

singletoninfouser::singletoninfouser():request(true) {}

singletoninfouser::~singletoninfouser()
{

}

singletoninfouser::singletoninfouser(const singletoninfouser &)
{

}

singletoninfouser &singletoninfouser::operator=(const singletoninfouser &)
{

}

singletoninfouser* singletoninfouser::infouser =new singletoninfouser();
