#ifndef COMMON_H
#define COMMON_H
#include <QRegularExpression>
#include <qfile.h>
#define CONFFILE "1" //配置文件
#define RECORDDIR "2" //上传下载记录
#define FILETYPEDIR "3" //文件存储类型目录
#include<qdebug.h>
#include<QObject>
#include"user.h"

#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonParseError>
#include<QCryptographicHash>

#include<QUrl>
/* 用户账号规则 */
#define USER_REG "^[\\w.]{0,10}$"
/* 密码规则 */
#define PASSWD_REG "^[a-zA-Z0-9.]{0,10}$"
/* 电话规则 */
#define PHONE_REG "^1\\d{10}$"
/* 邮箱规则 */
#define EMAIL_REG "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"
/* ip地址规则 */
#define IP_REG "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
/* 端口规则 */
#define PORT_REG "^(6553[0-5]|655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{0,3}|0)$"


// HTTP接口宏


#define CLILOGIN "/clilogin"
#define REGISTER "/register"
#define USERINFO "/userinfo"




/*demo

    QRegularExpression accountRegex("^[\\w.]{1,}$");
    QString account("asdasd稍等");
    if(common::Q_USER_REG->match(account).hasMatch()){
        qDebug("匹配失败");
    }else{
        qDebug("匹配成功");
    }
*/
/*用户配置 */
struct Login{
    QString pwd;
    QString remember;
    QString user;
}typedef Login;
/*存储*/
struct Type_path{
    QString path;
}typedef Type_path;
/*服务器设置*/
struct Web_server{
    QString ip;
    QString port;
}typedef Web_server;


class MY_JSON
{
public:
    MY_JSON(const QString* file);
    ~MY_JSON();

    //获取json类
    QJsonObject get_obj_login();

    /*初始化文件内容*/
    Login * init_Login();
    Type_path * init_Type_path();
    Web_server * init_Web_server();

    /*初始化入文件*/
    void set_Login(Login * L);
    void set_Type_path(Type_path *T);
    void set_Web_server(Web_server *W);

    //显示
    void show_Login(Login*L);
public:
    //注册逻辑
    static QByteArray register_Json(USER_register * user);

    //重新读取data
    void set_file_json();

public:
    //文件数据
    static QString file_data;
    //错误
    QJsonParseError jsonError;
    //json文件对象
    QJsonDocument doucment;
    //文件名字
    QString file_name;
    //加密
    QCryptographicHash* md5;
    QCryptographicHash* sha256;
private:

};

class NetWorkSocket
{
public:
    NetWorkSocket(MY_JSON* J);
    ~NetWorkSocket();

    //设置服务器请求
    void set_post(QString ip,QString prot);
    void set_key(QNetworkCookieJar *cookieJar,Login *L);
public:
    QString Agent;

    //login的请求路径
    QUrl login_url;
    QNetworkRequest login;

    QUrl register_url;
    QNetworkRequest registe;



};


#endif // COMMON_H

/*demo
*
*
    QString p(QApplication::applicationDirPath());
    p+="/conf/clicn.json";
    MY_JSON JK(&p);
    Login * jk = JK.init_Login();
    Type_path *LK =new Type_path{"123"};
    jk->pwd="12233";
    jk->remember="0987";
    JK.set_Login(jk);
    JK.set_Type_path(LK);
    qDebug()<<p;
    qDebug()<<JK.file_data;
*
*
*/
