#include "navigation_wg.h"
#include "ui_navigation_wg.h"
navigation_wg::navigation_wg(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::navigation_wg)
{
    ui->setupUi(this);
    //设置long图片 以及大小
    ui->log->setPixmap(QPixmap(":/qrc/logs.png").scaled(35,35));
    this->_parent=parent;
    connect(ui->set_up,&QToolButton::clicked,[=](){
        emit showsetWG();
    });
    connect(ui->close_b,&QToolButton::clicked,[=](){
        emit closewg();
    });
    connect(ui->reduce,&QToolButton::clicked,[=](){
        this->_parent->showMinimized();
    });
}

navigation_wg::~navigation_wg()
{
    delete ui;
}

void navigation_wg::mouseMoveEvent(QMouseEvent *event)
{
    //锁定鼠标左事件
    // 当前窗口=鼠标-查
    if(event->buttons() & Qt::LeftButton){
        this->_parent->move(event->globalPos()-this->mous_x_y);
    }
}

void navigation_wg::mousePressEvent(QMouseEvent *ev)
{
    //计算  当前鼠标离窗口的差
    if(ev->button() == Qt::LeftButton){
        this->mous_x_y=ev->globalPos()- this->_parent->pos();
    }
}


