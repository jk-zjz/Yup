#ifndef NAVIGATION_WG_H
#define NAVIGATION_WG_H

#include <QMouseEvent>
#include <QWidget>
#include <QObject>
#include <QEvent>
namespace Ui {
class navigation_wg;
}

class navigation_wg : public QWidget
{
    Q_OBJECT

public:
    explicit navigation_wg(QWidget *parent = nullptr);
    ~navigation_wg();
private:
    Ui::navigation_wg *ui;
    //父
    QWidget * _parent;
    //鼠标差
    QPoint mous_x_y;
protected:
    //鼠标移动 重写
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标按下重写
    void mousePressEvent(QMouseEvent *ev);
signals:
    void showsetWG();
    void closewg();
};

#endif // NAVIGATION_WG_H
