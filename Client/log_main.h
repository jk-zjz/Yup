#ifndef LOG_MAIN_H
#define LOG_MAIN_H
#include <QWidget>
#include"singletoninfouser.h"
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkCookieJar>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include"common.h"
#include"QsLog/include/QsLog.h"
#include"QsLog/include/QsLogDest.h"
#include <QJsonObject>
#include <QVector>
#include"user_flse_list.h"
#include<QVBoxLayout>
#include<form.h>
#include<QMainWindow>
namespace Ui {
class log_main;
}

class log_main : public QWidget
{
    Q_OBJECT
private:
    void post_user();
    void post_my_file();
    void User_Info(QByteArray *data);
    void flie_list(QByteArray *data);
    void set_button(int height,int width);
public:
    explicit log_main(QWidget *parent = nullptr);
    ~log_main();

private:
    Ui::log_main *ui;
    //父
    QWidget * parent_;
    //静态内存信息
    singletoninfouser *info;
    //网络请求
    QNetworkAccessManager * network;
    //鼠标移动差
    QPoint mous_x_y;
    int height;
    int width;
    QVBoxLayout* layout;
    Form *F;

};

#endif // LOG_MAIN_H
