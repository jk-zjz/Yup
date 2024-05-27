#ifndef FORM_H
#define FORM_H
#include<QTableWidget>
#include<QWidget>
#include<QScrollArea>
#include<QVBoxLayout>
#include<QMainWindow>
#include<QPushButton>
#include<QWidget>
#include <QScrollArea> // 引入 std::bind 所需的头文件
#include<singletoninfouser.h>
class Form : public QMainWindow
{
    Q_OBJECT
public:
    Form(QWidget * parent,int Row,int Col,QStringList & Header,int a);
    ~Form();
    void addRowWithData(QTableWidget *table, int row, const QStringList &data);
private slots:
    void onDeleteRow();

private:
    QTableWidget *tableWidget;
    QPushButton *deleteButton;
    singletoninfouser * info;
};

#endif // FORM_H
