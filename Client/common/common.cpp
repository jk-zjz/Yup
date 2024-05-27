#include "common.h"


MY_JSON::MY_JSON(const QString *file_name)
{
    this->file_name=*file_name;
    if(!file_data.size()){
        QFile file;
        file.setFileName(*file_name);
        file.open(QIODeviceBase::ReadOnly);
        QByteArray  f_data =file.readAll();
        file_data = QString(f_data);
        file.close();
    }
    this->md5=new QCryptographicHash(QCryptographicHash::Md5);
    this->doucment = QJsonDocument::fromJson(this->file_data.toLatin1(), &jsonError);
}

MY_JSON::~MY_JSON()
{
    delete(this->md5);
}

QJsonObject MY_JSON::get_obj_login()
{
    QJsonObject V;
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        QJsonObject object = doucment.object();
        QJsonValue value = object.value("login");
        V =value.toObject();
        return V;
    }
    return V;

}

Login *MY_JSON::init_Login()
{


    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        QJsonObject object = doucment.object();
        QJsonValue value = object.value("login");
        QJsonObject V =value.toObject();
        Login* L =new Login{V.value("pwd").toString(),V.value("remember").toString(),V.value("user").toString()};
        return L;
    }
    return NULL;
}

Type_path *MY_JSON::init_Type_path()
{
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {

        QJsonObject object = doucment.object();
        QJsonValue value = object.value("type_path");
        QJsonObject V =value.toObject();
        Type_path *T =new Type_path{V.value("path").toString()};
        return T;
    }
    return NULL;
}

Web_server* MY_JSON::init_Web_server()
{
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {
        QJsonObject object = doucment.object();
        QJsonValue value = object.value("web_server");
        QJsonObject V =value.toObject();
        Web_server* W =new Web_server{V.value("ip").toString(),V.value("port").toString()};
        return W;
    }
    return NULL;
}

void MY_JSON::set_Login(Login *L)
{
    QJsonDocument J = QJsonDocument::fromJson(this->file_data.toLatin1());
    QJsonObject J_ = J.object();
    QJsonObject V = J_.value("login").toObject();
    V["pwd"]=L->pwd;
    V["remember"]=L->remember;
    V["user"]=L->user;
    J_["login"]=V;
    QJsonDocument JK(J_);
    this->file_data =(QString)JK.toJson();
    this->doucment=JK;
    set_file_json();
}

void MY_JSON::set_Type_path(Type_path *T)
{
    QJsonDocument J = QJsonDocument::fromJson(this->file_data.toLatin1());
    QJsonObject J_ = J.object();
    QJsonObject V = J_.value("type_path").toObject();
    V["path"]=T->path;
    J_["type_path"]=V;
    QJsonDocument JK(J_);
    this->file_data =(QString)JK.toJson();
    this->doucment=JK;
    set_file_json();
}

void MY_JSON::set_Web_server(Web_server *W)
{
    QJsonDocument J = QJsonDocument::fromJson(this->file_data.toLatin1());
    QJsonObject J_ = J.object();
    QJsonObject V = J_.value("web_server").toObject();
    V["ip"]=W->ip;
    V["port"]=W->port;
    J_["web_server"]=V;
    QJsonDocument JK(J_);
    this->doucment=JK;
    this->file_data =(QString)JK.toJson();
    set_file_json();
}

void MY_JSON::show_Login(Login *L)
{

    qDebug()<<L->pwd<<"  "<<L->remember<<" "<<L->user;
}

void MY_JSON::set_file_json()
{
    QFile file_;
    file_.setFileName(this->file_name);
    file_.open(QIODeviceBase::WriteOnly);
    file_.write(this->file_data.toLatin1());
    file_.close();
}
QString MY_JSON::file_data=NULL;

NetWorkSocket::NetWorkSocket(MY_JSON* J) {

    QString Ulr("http://");
    this->Agent=R"(Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36 Edg/122.0.0.0)";

    Web_server * W = J->init_Web_server();

    QString  login_Ulr=Ulr + W->ip+CLILOGIN;
    this->login_url=QUrl(login_Ulr);
    this->login=QNetworkRequest(login_url);

    QString  register_Ulr =Ulr +W->ip+REGISTER;
    this->register_url=QUrl(register_Ulr);
    this->registe=QNetworkRequest(register_url);

    this->login.setHeader(QNetworkRequest::UserAgentHeader,this->Agent);
    this->login.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    this->registe.setHeader(QNetworkRequest::UserAgentHeader,this->Agent);
    this->registe.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
}


QByteArray MY_JSON::register_Json(USER_register *user)
{
    QJsonObject  A;
    A.insert("accout",user->user_account);
    A.insert("password",user->user_ac_passwrod);
    A.insert("name",user->user_name);
    A.insert("phone",user->user_phone);
    A.insert("em",user->user_EM);

    QJsonDocument B(A);
    return B.toJson();
}


NetWorkSocket::~NetWorkSocket() {}

void NetWorkSocket::set_post(QString ip, QString prot)
{

    this->login_url="http://"+ip+":"+prot+CLILOGIN;
    this->login.setUrl(this->login_url);

    this->register_url="http://"+ip+":"+prot+REGISTER;
    this->registe.setUrl(this->register_url);
}

void NetWorkSocket::set_key(QNetworkCookieJar *cookieJar,Login *L)
{

    QNetworkCookie cookie("name",L->pwd.toLatin1());
    cookieJar->insertCookie(cookie);
    this->login.setHeader(QNetworkRequest::CookieHeader,QVariant(L->pwd));
}


























