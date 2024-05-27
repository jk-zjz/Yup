#include "user.h"


USER_register::~USER_register()
{

}

USER_register::USER_register(QString user_account, QString user_name, QString user_password, QString user_ac_passwrod, QString user_phone, QString user_EM)
{
    this->user_account=user_account;
    this->user_name=user_name;
    this->user_password=user_password;
    this->user_ac_passwrod=user_ac_passwrod;
    this->user_phone=user_phone;
    this->user_EM=user_EM;
}

QString USER_register::to_string()
{
    return user_account+":"+user_name+":"+user_password+":"+user_ac_passwrod+":"+user_phone+":"+user_EM+":";
}

QString USER_register::get_user_phone()
{
    QString phone=this->user_phone;
    privacy(phone);
    return phone;
}

QString USER_register::get_user_EM()
{
    QString EM=this->user_EM;
    privacy(EM);
    return EM;
}

QString USER_register::get_user_password() const
{
    return this->user_ac_passwrod;
}

QString USER_register::get_user_account()
{
    QString account=this->user_account;
    privacy(account);
    return account;
}

void USER_register::privacy(QString &s)
{
    int i=s.size()/3;
    for(i;i<s.size()-i;i++){
        s[i]='*';
    }
}
