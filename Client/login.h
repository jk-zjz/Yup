#ifndef LOGIN_H
#define LOGIN_H
#include<QPainter>
#include <QDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "common.h"
#include<QLineEdit>
#include"user.h"
#include<QMessageBox>
#include<QString>
#include<iostream>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
//日志
#include"QsLog/include/QsLog.h"
#include"QsLog/include/QsLogDest.h"
#include"singletoninfouser.h"
#include"log_main.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
public:
    enum MyFlags {
        OK = 200,
        CONNECT_FAILED = 401,
        INSERTION_ERROR = 402,
        TOKEN_FAILED = 403,
        QUERY_ERROR = 404,
        DATA_READ_FAILED = 405
    };
public:
    explicit login(QWidget *parent = nullptr);
    void initLogger();
    void destroyLogger();
    ~login();
    static void logFunction(const QString &message, QsLogging::Level level);
private:
    //切换清空框
    void empty_frame(void);
    //设置校验对象以及错误
    bool init_QV_obj(QString data, QRegularExpression*QV);
    //初始化校验对象
    void init_ONJ();
    void user_test(const QString& data,QLineEdit * EV,QRegularExpression *QV);
    //设置默认服务器设置

    //设置登录页面的记录问题
    void set_login_password_key();

    //处理过期&回到登录界面
    void secondary_login(QString  data);

    //判断文件存在，创建，和初始化
    QString conf_file_handle();
    //初始化文件
    void set_conf_file();
private:
    log_main * log_main_;

    Ui::login *ui;

    //日志对象
    QsLogging::Logger& logger;
    //校验对象
    QRegularExpression *QV_USER_REG;
    QRegularExpression *QV_PASSWD_REG;
    QRegularExpression *QV_PHONE_REG;
    QRegularExpression *QV_EMAIL_REG;
    QRegularExpression *QV_PORT_REG;
    QRegularExpression *QV_IP_REG;

    //json对象
    MY_JSON* JSON;

    //网络对象
    NetWorkSocket *network_information;
    QNetworkAccessManager * network;

protected:
    void paintEvent(QPaintEvent *ev);
private slots:
    //注册按钮
    void on_toolButton_7_clicked();
    //登录按钮
    void on_toolButton_2_clicked();
    //服务器按钮
    void on_toolButton_6_clicked();

};

#endif // LOGIN_H
