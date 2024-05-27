#ifndef USER_H
#define USER_H
#include <QString>
#include<qDebug>
class USER_register{
public:
    ~USER_register();
    USER_register(QString user_account,
                    QString user_name,
                    QString user_password,
                    QString user_ac_passwrod,
                    QString user_phone,
                    QString user_EM);
    QString to_string();

    QString get_user_phone();
    QString get_user_EM();
    //现在的密码存储到注册时间
    QString get_user_password() const;
    QString get_user_account();
    void privacy(QString & s);
public:
    QString user_account;
    QString user_name;
    QString user_password;
    QString user_ac_passwrod;
    QString user_phone;
    QString user_EM;
};

#endif // USER_H
