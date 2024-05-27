#ifndef LOG_NAVIGATION_H
#define LOG_NAVIGATION_H

#include <QWidget>
#include<QPushButton>
#include<QMouseEvent>
namespace Ui {
class log_navigation;
}

class log_navigation : public QWidget
{
    Q_OBJECT

public:
    explicit log_navigation(QWidget *parent = nullptr);
    ~log_navigation();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

protected:
    //鼠标移动 重写
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标按下重写
    void mousePressEvent(QMouseEvent *ev);

private:
    Ui::log_navigation *ui;
    QWidget * _parent;
    QPoint mous_x_y;
    QSize min;
    bool type;
signals:
    //关闭
    void closelog();
    //切换页面
    void set_ui(int i);
};

#endif // LOG_NAVIGATION_H
