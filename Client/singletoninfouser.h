#ifndef SINGLETONINFOUSER_H
#define SINGLETONINFOUSER_H
#include<QString>
#include"user.h"
#include"user_flse_list.h"
class singletoninfouser
{
public:
    static singletoninfouser* get_setinfouser();
    void setinfouser(QString user_,int id_,QString cookie_,QString ip_,QString port_);
    QString getuser() const;
    int getid()const;
    QString getcookie()const;
    QString getip()const;
    QString getport()const;
    void setiport(QString ip,QString port);
    void set_user_info(USER_register* user_info);
    QString get_user_info();
    USER_register * get_user_info_();
    bool get_request();
    void set_request(bool R);
    QList<User_Flse_List>* get_FileList();
    void erase_FileList();
    void show_FileList();
private:
    singletoninfouser();
    ~singletoninfouser();
    singletoninfouser(const singletoninfouser&);
    singletoninfouser& operator=(const singletoninfouser&);
private:
    static singletoninfouser * infouser;

    QString user;
    int id;
    QString cookie;
    QString ip;
    QString port;
    USER_register* user_info;
    QList<User_Flse_List>file_list;
    bool request;
};

#endif // SINGLETONINFOUSER_H
