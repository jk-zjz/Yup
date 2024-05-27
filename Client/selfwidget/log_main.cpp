#include "log_main.h"
#include "ui_log_main.h"

void log_main::post_user()
{
    QString ip=this->info->getip();
    QString port = this->info->getport();
    QUrl URL ="http://"+ip+":"+port+USERINFO;
    QString agent=R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0)";
    QNetworkRequest Request(URL);
    QNetworkCookie Web_cookie("cookie",this->info->getcookie().toLatin1()+";");
    QVariant V;
    V.setValue(Web_cookie);
    Request.setHeader(QNetworkRequest::UserAgentHeader,agent);
    Request.setHeader(QNetworkRequest::CookieHeader,V);
    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QString data_ = "{\"type\":101,\"id\":";
    data_+=QString::number(this->info->getid(),10)+"}";
    QNetworkReply* J_K = this->network->post(Request,data_.toLatin1());
    connect(J_K,&QNetworkReply::finished,this,[=](){
        if(J_K->error()==QNetworkReply::NoError){
            QByteArray J=J_K->readAll();
            QJsonDocument doc =QJsonDocument::fromJson(J);
            QJsonObject json=doc.object();
            QString data_ = json.value("data").toString();
            QByteArray Data = QByteArray::fromBase64(data_.toLatin1());
            User_Info(&Data);
        }else{
            QLOG_ERROR()<<"鸡：服务器没得搞"<<301;
            exit(0);
        }
        delete(J_K);
    });

}

void log_main::post_my_file()
{
    //产生了更改
    if(!this->info->get_request()){
        qDebug()<<"内存";
        set_button(ui->page_2->height(),ui->page_2->width());
        this->info->show_FileList();
        return ;
    }
    QString ip=this->info->getip();
    QString port = this->info->getport();
    QUrl URL ="http://"+ip+":"+port+USERINFO;
    QString agent=R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0)";
    QNetworkRequest Request(URL);
    QNetworkCookie Web_cookie("cookie",this->info->getcookie().toLatin1()+";");
    QVariant V;
    V.setValue(Web_cookie);
    Request.setHeader(QNetworkRequest::UserAgentHeader,agent);
    Request.setHeader(QNetworkRequest::CookieHeader,V);
    Request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QString data_ = "{\"type\":102,\"id\":";
    data_+=QString::number(this->info->getid(),10)+"}";
    QNetworkReply* J_K = this->network->post(Request,data_.toLatin1());
    connect(J_K,&QNetworkReply::finished,this,[=](){
        if(J_K->error()==QNetworkReply::NoError){
            QByteArray J=J_K->readAll();
            QJsonDocument doc =QJsonDocument::fromJson(J);
            QJsonObject json=doc.object();
            QString data_ = json.value("data").toString();
            QByteArray Data = QByteArray::fromBase64(data_.toLatin1());
            flie_list(&Data);
        }else{
            QLOG_ERROR()<<"鸡：服务器没得搞"<<301;
            exit(0);
        }
        delete(J_K);
    });

}
void log_main::flie_list(QByteArray *data)
{
    QJsonDocument jsonO =QJsonDocument::fromJson(*data);
    this->info->erase_FileList();
    QList<User_Flse_List>* file = this->info->get_FileList();
    QJsonObject json=jsonO.object();
    QJsonObject Data = json.value("data").toObject();
    for(auto it = Data.constBegin();it!=Data.constEnd();it++){
        QJsonObject data = it.value().toObject();
        User_Flse_List flis_list((unsigned int)data.value("user").toInt(),
                       data.value("sha256").toString(),
                       data.value("createtime").toString(),
                       data.value("filename").toString(),
                       data.value("shared_status").toBool(),
                       (unsigned int)data.value("pv").toInt()
                       );
         file->push_back(flis_list);
    }
    qDebug()<<"请求";
    this->info->show_FileList();
    this->info->set_request(false);
}
void log_main::set_button(int height, int width)
{
    F = new Form(ui->page_2,info->get_FileList()->size(),4,QStringList() << "文件名" << "创建时间" << "共享状态"<<"共享次数",1);
    delete(F);
}
void log_main::User_Info(QByteArray *data)
{
    QJsonDocument jsonO =QJsonDocument::fromJson(*data);
    QJsonObject json=jsonO.object();
    QJsonObject Data = json.value("data").toObject().value(QString::number(info->getid())).toObject();
    QJsonDocument jsonDoc(Data);
    QString account=Data.value("username").toString();
    QString nickname=Data.value("nickname").toString();
    QString createtime=Data.value("createtime").toString();
    QString email=Data.value("email").toString();
    QString phone=Data.value("phone").toString();
    USER_register * bbll = new USER_register(account,
                                            nickname,
                                            createtime,
                                            createtime,
                                            email,
                                            phone
                                            );
    this->info->set_user_info(bbll);
}

log_main::log_main(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::log_main)
{

    ui->setupUi(this);
    this->network=new QNetworkAccessManager(this);
    this->info=singletoninfouser::get_setinfouser();
    this->parent_=parent;
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    setWindowIcon(QIcon(":/qrc/favicon.ico"));
    connect(ui->widget,&log_navigation::closelog,this,[=]{
        this->close();
    });
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    ui->label_9->setText("Hi !"+info->getuser());
    post_user();
    this->height=-1;
    this->width=-1;
    connect(ui->widget,&log_navigation::set_ui,this,[=](int i){
        switch (i) {
        case 1:
            ui->stackedWidget->setCurrentWidget(ui->page_2);
            post_my_file();
            break;
        case 2:
            ui->stackedWidget->setCurrentWidget(ui->page_3);
            break;
        case 3:
            ui->stackedWidget->setCurrentWidget(ui->page_4);
            break;
        case 4:
            ui->stackedWidget->setCurrentWidget(ui->page_5);
            break;
        case 5:
            ui->stackedWidget->setCurrentWidget(ui->page_6);
            break;
        case 6:
            ui->stackedWidget->setCurrentWidget(ui->page);
            ui->label_5->setText(this->info->get_user_info_()->get_user_account());
             ui->label_6->setText(this->info->get_user_info_()->get_user_phone());
             ui->label_7->setText(this->info->get_user_info_()->get_user_EM());
            ui->label_8->setText(this->info->get_user_info_()->get_user_password());
            break;
        default:
            break;
        }
        qDebug()<<i;
    });
}

log_main::~log_main()
{
    delete(this->network);
    delete ui;
}
