#include "log_navigation.h"
#include "ui_log_navigation.h"

log_navigation::log_navigation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::log_navigation)
{

    ui->setupUi(this);
    this->type=true;
    connect(ui->toolButton_3,&QToolButton::clicked,this,[=]{
        emit closelog();
    });

    connect(ui->toolButton_4,&QToolButton::clicked,this,[=]{
        emit set_ui(1);
    });
    connect(ui->toolButton_5,&QToolButton::clicked,this,[=]{
        emit set_ui(2);
    });
    connect(ui->toolButton_6,&QToolButton::clicked,this,[=]{
        emit set_ui(3);
    });
    connect(ui->toolButton_7,&QToolButton::clicked,this,[=]{
        emit set_ui(4);
    });
    connect(ui->toolButton_8,&QToolButton::clicked,this,[=]{
        emit set_ui(5);
    });
    connect(ui->toolButton_9,&QToolButton::clicked,this,[=]{
        emit set_ui(6);
    });
    _parent=parent;
    this->min=this->size();
}

log_navigation::~log_navigation()
{
    delete ui;
}

void log_navigation::on_toolButton_clicked()
{
    _parent->showMinimized();
}
void log_navigation::mouseMoveEvent(QMouseEvent *event)
{
    //锁定鼠标左事件
    // 当前窗口=鼠标-查
    if(event->buttons() & Qt::LeftButton){
        this->_parent->move(event->globalPos()-this->mous_x_y);
    }
}
void log_navigation::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        this->mous_x_y=ev->globalPos()- this->_parent->pos();
    }

}

void log_navigation::on_toolButton_2_clicked()
{
    if(this->type){
        //最大化
        this->type=false;
        _parent->showMaximized();
    }else{
        this->type=true;
        _parent->showNormal();
    }
}



