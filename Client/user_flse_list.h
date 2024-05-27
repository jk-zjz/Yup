#ifndef USER_FLSE_LIST_H
#define USER_FLSE_LIST_H
#include <QString>
#include <QDebug>
class User_Flse_List
{
public:
    User_Flse_List();
    User_Flse_List(unsigned int id,
                   QString sha256,
                   QString createtime,
                   QString filename,
                   bool shared_status,
                   unsigned int pv);
    void to_string();
public:
    unsigned int id;
    QString sha256;
    QString createtime;
    QString filename;
    bool shared_status;
    unsigned int pv;
};

#endif // USER_FLSE_LIST_H
