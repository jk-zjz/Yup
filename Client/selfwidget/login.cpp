#include "login.h"
#include "ui_login.h"
#include "common.h"
#include<QIntValidator>
#include<QToolTip>
#include<QDir>
login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
    ,logger(QsLogging::Logger::instance())
{
    ui->setupUi(this);

    QString p = conf_file_handle();

    //设置日志等级
    this->logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(QCoreApplication::applicationDirPath()).filePath("log.txt"));
    QsLogging::DestinationPtr fileDestination(QsLogging::DestinationFactory::MakeFileDestination(
        sLogPath, QsLogging::EnableLogRotation, QsLogging::MaxSizeBytes(512), QsLogging::MaxOldLogCount(2)));
    QsLogging::DestinationPtr debugDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    QsLogging::DestinationPtr functorDestination(QsLogging::DestinationFactory::MakeFunctorDestination(&login::logFunction));

    this->logger.addDestination(debugDestination);
    this->logger.addDestination(fileDestination);
    this->logger.addDestination(functorDestination);

    this->JSON=new MY_JSON(&p);
    setWindowIcon(QIcon(":/qrc/favicon.ico"));
    /*设置无边框不可以的缩放*/
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    init_ONJ();

    /*密文显示*/
    ui->lineEdit_13->setEchoMode(QLineEdit::Password);
    ui->lineEdit_14->setEchoMode(QLineEdit::Password);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
     initLogger();
    /*设置全局字体*/
    this->setFont(QFont("黑体",12,1,false));
    set_login_password_key();
    ui->stackedWidget->setCurrentWidget(ui->long_page);

    this->network_information=new NetWorkSocket(this->JSON);
    this->network=new QNetworkAccessManager(this);\
    connect(ui->navigation,&navigation_wg::showsetWG,[=](){
        //切换 设置界面
        empty_frame();
        if(ui->stackedWidget->currentWidget()==ui->setup_page){
            set_login_password_key();
            ui->stackedWidget->setCurrentWidget(ui->long_page);
        }else{
            Web_server* W = this->JSON->init_Web_server();

            if(!W->ip.isEmpty()&&!W->port.isEmpty()){
                ui->lineEdit_9->setText(W->ip);
                ui->lineEdit_10->setText(W->port);
            }
            ui->stackedWidget->setCurrentWidget(ui->setup_page);
            delete(W);
        }
    });

    connect(ui->toolButton,&QToolButton::clicked,[=](){
        empty_frame();
        ui->stackedWidget->setCurrentWidget(ui->register_page);
    });

    connect(ui->navigation,&navigation_wg::closewg,[=](){
        // 关闭--->切换
        empty_frame();
        if(ui->stackedWidget->currentWidget()== ui->long_page){
            this->close();
        }else{
            set_login_password_key();
            ui->stackedWidget->setCurrentWidget(ui->long_page);
        }
    });
    connect(ui->lineEdit,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit,this->QV_USER_REG);});
    connect(ui->lineEdit_2,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_2,this->QV_PASSWD_REG);});
    connect(ui->lineEdit_11,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_11,this->QV_USER_REG);});
    connect(ui->lineEdit_13,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_13,this->QV_PASSWD_REG);});
    connect(ui->lineEdit_14,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_13,this->QV_PASSWD_REG);});
    connect(ui->lineEdit_15,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_15,this->QV_PHONE_REG);});
    connect(ui->lineEdit_16,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_16,this->QV_EMAIL_REG);});
    connect(ui->lineEdit_9,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_9,this->QV_IP_REG);});
    connect(ui->lineEdit_10,&QLineEdit::textChanged,this,[=](const QString &test){user_test(test,ui->lineEdit_10,this->QV_PORT_REG);});
}

void login::initLogger()
{

}

void login::destroyLogger()
{

}
login::~login()
{
    delete(this->QV_EMAIL_REG);
    delete(this->QV_PASSWD_REG);
    delete(this->QV_USER_REG);
    delete(this->QV_PORT_REG);
    delete(this->QV_IP_REG);
    delete ui;
    delete(this->JSON);
    delete(this->network);
    destroyLogger();

}

void login::logFunction(const QString &message, QsLogging::Level level)
{
    std::cout << "From log function: " << qPrintable(message) << " " << static_cast<int>(level)
              << std::endl;
}
void login::empty_frame()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->checkBox->setChecked(false);
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
}

bool login::init_QV_obj(QString data, QRegularExpression *QV)
{
    return QV->match(data).hasMatch();
}

void login::init_ONJ()
{
    this->QV_USER_REG = new QRegularExpression(USER_REG);
    this->QV_PASSWD_REG =new QRegularExpression(PASSWD_REG);
    this->QV_PHONE_REG=new QRegularExpression(PHONE_REG);
    this->QV_IP_REG=new QRegularExpression(IP_REG);
    this->QV_PORT_REG=new QRegularExpression(PORT_REG);
    this->QV_EMAIL_REG=new QRegularExpression(EMAIL_REG);
    ui->lineEdit->setMaxLength(10);
    ui->lineEdit_2->setMaxLength(10);
    ui->lineEdit_11->setMaxLength(10);
    ui->lineEdit_12->setMaxLength(10);
    ui->lineEdit_13->setMaxLength(10);
    ui->lineEdit_14->setMaxLength(10);
    ui->lineEdit_15->setMaxLength(11);
    ui->lineEdit_10->setMaxLength(5);
}

void login::user_test(const QString &data,QLineEdit *EV,QRegularExpression *QV)
{
    if(!init_QV_obj(data,QV)){
        EV->setStyleSheet("QLineEdit{border:1px solid rgb(255, 0, 0);}");
        QToolTip::showText(EV->mapToGlobal(QPoint(100, 0)), "输入错误");
    }else{
        EV->setStyleSheet("QLineEdit{border:1px solid gray border-radius:1px}");
    }
}

void login::set_login_password_key()
{
    Login * login = this->JSON->init_Login();
    if(!QString::localeAwareCompare(login->remember,"true")){
        ui->lineEdit_2->setText("123456");
        ui->checkBox->setChecked(true);

    }
    ui->lineEdit->setText(login->user);
}

void login::secondary_login(QString  data)
{
    //处理过期&回到登录界面
    singletoninfouser * set =singletoninfouser::get_setinfouser();
    QNetworkAccessManager* m_manager = new QNetworkAccessManager(this);
    QNetworkRequest* m_request = new QNetworkRequest(QUrl("http://hhap.cn/clilogin/"));
    QString Agent=R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0)";
    m_request->setHeader(QNetworkRequest::UserAgentHeader,QVariant(Agent));
    m_request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *JK = m_manager->post(*m_request,data.toLatin1());
    Web_server *W =this->JSON->init_Web_server();

    QString IP=W->ip;
    QString PORT =W->port;

    delete(W);

    connect(m_manager,&QNetworkAccessManager::finished,this,[=](){
        //没有cookie
        if(JK->error()==QNetworkReply::NoError){
            QByteArray J = JK->readAll();
            QJsonDocument doc =QJsonDocument::fromJson(J);
            QJsonObject  i=doc.object();
            int type = i.value("type").toInt();
            if(type==200){

                singletoninfouser * set =singletoninfouser::get_setinfouser();
                set->setinfouser(ui->lineEdit->text(),i["id"].toInt(),i["cookie"].toString(),IP,PORT);

                Login L{i["cookie"].toString(),
                        "flase",
                        ui->lineEdit->text()};
                QLOG_WARN()<<"登录成功 "<<type<<ui->lineEdit->text();
                //登录成功
                this->JSON->set_Login(&L);
                this->hide();
                this->log_main_= new log_main;
                this->log_main_->show();
            }else{
                QLOG_WARN()<<"cookie过期 登录失败 "<<type<<ui->lineEdit->text();
                QMessageBox::warning(this,tr("登录"),tr("登录失败"));
            }
        }else{
            QLOG_WARN()<<"服务器未响应 "<<304;
            QMessageBox::warning(this,tr("304"),tr("服务器无响应"));
        }
    });
}

QString login::conf_file_handle()
{
    QFile file(QApplication::applicationDirPath()+"/clicn.json");
    if(file.exists()){
        return  QApplication::applicationDirPath()+"/clicn.json";
    };
    set_conf_file();
    return QApplication::applicationDirPath()+"/clicn.json";
}

void login::set_conf_file()
{
    QJsonObject  A;
    QJsonObject  B;
    QJsonObject  C;
    QJsonObject  D;
    QJsonObject  E;
    B.insert("pwd",QJsonValue(""));
    B.insert("remember",QJsonValue(""));
    B.insert("user",QJsonValue(""));
    A.insert("login",B);
    C.insert("path",QJsonValue(""));
    A.insert("type_path",C);
    D.insert("ip",QJsonValue(""));
    D.insert("port",QJsonValue(""));
    A.insert("web_server",D);
    QJsonDocument B_B(A);
    QByteArray data =B_B.toJson();

    QFile file(QApplication::applicationDirPath()+"/clicn.json");
    if(file.open(QIODevice::WriteOnly)){
        //成功
        file.write(data);
    }else{
        QLOG_ERROR()<<"conf ./clicn.json absent";
        exit(0);
    }
}



void login::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/qrc/background_2.jpg"));
}

void login::on_toolButton_7_clicked()
{
    if(QString::localeAwareCompare(ui->lineEdit_14->text(),ui->lineEdit_13->text())){
        QMessageBox::warning(this,tr("密码"),tr("两次密码不相同"));
    }
    else if(!init_QV_obj(ui->lineEdit_11->text(),this->QV_USER_REG)||
        !init_QV_obj(ui->lineEdit_13->text(),this->QV_PASSWD_REG)||
        !init_QV_obj(ui->lineEdit_14->text(),this->QV_PASSWD_REG)||
        !init_QV_obj(ui->lineEdit_15->text(),this->QV_PHONE_REG)||
        !init_QV_obj(ui->lineEdit_16->text(),this->QV_EMAIL_REG))
    {
        QMessageBox::warning(this,tr("用户"),tr("输入错误"));
    }
    else if(ui->lineEdit_11->text().isEmpty()||
        ui->lineEdit_12->text().isEmpty()||
        ui->lineEdit_13->text().isEmpty()||
        ui->lineEdit_14->text().isEmpty()||
        ui->lineEdit_15->text().isEmpty()||
        ui->lineEdit_16->text().isEmpty())
    {
        QMessageBox::warning(this,tr("用户"),tr("输入框为空"));
    }else{
        //注册验证
        USER_register user(ui->lineEdit_11->text(),
                           ui->lineEdit_12->text(),
                           ui->lineEdit_13->text(),
                           ui->lineEdit_14->text(),
                           ui->lineEdit_15->text(),
                           ui->lineEdit_16->text());
        QByteArray sb = MY_JSON::register_Json(&user);
        QNetworkReply *JK =this->network->post(this->network_information->registe,sb);
        connect(JK,&QNetworkReply::finished,this,[=](){
            if(JK->error()==QNetworkReply::NoError){
                QByteArray J = JK->readAll();

                QJsonDocument doc =QJsonDocument::fromJson(J);
                QJsonObject  i=doc.object();
                int StatusCode = i.value("StatusCode").toInt();
                if(StatusCode==200){
                    Login L{i["key"].toString(),
                            "true",
                            user.user_account};
                    if(!ui->checkBox->isChecked()){
                        L.remember="flase";
                    }
                    this->JSON->set_Login(&L);
                    QMessageBox::warning(this,tr("注册"),tr("成功"));
                    QLOG_WARN()<<"注册成功 "<<StatusCode<<"user:"<<user.user_account<<"name:"<<user.user_name;
                    ui->lineEdit->setText(user.user_account);
                    ui->stackedWidget->setCurrentWidget(ui->long_page);
                }else{
                    QLOG_WARN()<<"注册失败 "<<StatusCode<<user.user_account;
                    QMessageBox::warning(this,tr("注册"),tr("注册失败"));
                }
            }else{
                QLOG_ERROR()<<"服务器未响应"<<301;
                QMessageBox::warning(this,tr("设置"),tr("服务器连接失败"));
            }
            delete(JK);
        });
    }
}
//登录按钮
void login::on_toolButton_2_clicked()
{
    if(!init_QV_obj(ui->lineEdit->text(),this->QV_USER_REG)||
        !init_QV_obj(ui->lineEdit_2->text(),this->QV_PASSWD_REG)||
        ui->lineEdit_2->text().isEmpty()){
        QMessageBox::warning(this,tr("用户"),tr("输入错误"));
    }else{
        QByteArray hash = QCryptographicHash::hash(ui->lineEdit_2->text().toLatin1(),QCryptographicHash::Sha256);


        /* 设置浏览器*/
        QString ARR;
        ARR = R"({"user":")"+ui->lineEdit->text()+R"(","password":")"+hash.toHex()+R"("})";

        Login * L =  this->JSON->init_Login();
        Web_server *W =this->JSON->init_Web_server();

        QString IP=W->ip;
        QString PORT =W->port;

        QNetworkCookie Web_cookies("cokin",L->pwd.toLatin1()+";");
        QVariant var;
        var.setValue(Web_cookies);
        this->network_information->login.setHeader(QNetworkRequest::CookieHeader,var);
        QNetworkReply* JK= this->network->post(this->network_information->login,ARR.toLatin1());
        connect(JK,&QNetworkReply::finished,this,[=](){
            if(JK->error()==QNetworkReply::NoError){
                QByteArray J = JK->readAll();
                QJsonDocument doc =QJsonDocument::fromJson(J);
                QJsonObject json=doc.object();
                int type = json.value("type").toInt();
                if(type==200){
                    singletoninfouser * set =singletoninfouser::get_setinfouser();
                    set->setinfouser(ui->lineEdit->text(),json["id"].toInt(),json["cookie"].toString(),IP,PORT);
                    if(ui->checkBox->isChecked()){
                        //登录为记录&正确登
                    }
                    Login L{json["cookie"].toString(),
                            "flase",
                            ui->lineEdit->text()};
                    QLOG_WARN()<<"登录成功 "<<type<<ui->lineEdit->text();
                    //登录成功
                    this->JSON->set_Login(&L);
                    this->hide();
                    this->log_main_= new log_main;
                    this->log_main_->show();
                    delete(JK);

                }else if(type==203 ){
                    delete(JK);
                    QLOG_WARN()<<"cookie 过期 "<<203;
                    secondary_login(ARR);
                }else{
                    delete(JK);
                    QLOG_WARN()<<"cookie 过期 "<<type<<ui->lineEdit->text();
                    QMessageBox::warning(this,tr("204·"),tr("登录失败"));
                }
                //会写新窗口
            }else{
             QLOG_WARN()<<"服务器未响应 "<<301;
             QMessageBox::warning(this,tr("301"),tr("服务器未响应"));
            delete(JK);
            }
        });
        delete(L);
        delete(W);
    }
}
//服务器按钮
void login::on_toolButton_6_clicked()
{
    if(!init_QV_obj(ui->lineEdit_9->text(),this->QV_IP_REG)||
        !init_QV_obj(ui->lineEdit_10->text(),this->QV_PORT_REG)){
         QMessageBox::warning(this,tr("服务器配置"),tr("输入错误"));
    }else{
        //服务器设置
        Web_server IP_PORT{ui->lineEdit_9->text(),ui->lineEdit_10->text()};
        this->JSON->set_Web_server(&IP_PORT);
        ui->stackedWidget->setCurrentWidget(ui->long_page);
        this->network_information->set_post(ui->lineEdit_9->text(),ui->lineEdit_10->text());
        singletoninfouser * p =singletoninfouser::get_setinfouser();
        p->setiport(ui->lineEdit_9->text(),ui->lineEdit_10->text());
    }
}

