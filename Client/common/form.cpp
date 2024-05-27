#include"form.h"
Form::Form(QWidget *parent, int Row, int Col, QStringList& Header,int a)
{
    info=singletoninfouser::get_setinfouser();
    QVBoxLayout *layout = new QVBoxLayout(parent);

    // 创建表格
    tableWidget = new QTableWidget(Row, Col); // 5行3列
    tableWidget->setHorizontalHeaderLabels(Header);

    QList<User_Flse_List>p=*(info->get_FileList());
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int row=0;
    for(auto & i : p){
        QTableWidgetItem *newItem1 = new QTableWidgetItem(QString(" %1").arg(i.filename));
        QTableWidgetItem *newItem2 = new QTableWidgetItem(QString(" %1").arg(i.createtime));
        QTableWidgetItem *newItem3 = new QTableWidgetItem(QString(" %1").arg(i.shared_status));
        QTableWidgetItem *newItem4 = new QTableWidgetItem(QString(" %1").arg(i.pv));
        tableWidget->setItem(row, 0, newItem1);
        tableWidget->setItem(row, 1, newItem2);
        tableWidget->setItem(row, 2, newItem3);
        tableWidget->setItem(row, 3, newItem4);
        row++;
    }
    layout->addWidget(tableWidget);

    // 创建删除按钮
    deleteButton = new QPushButton("删除行");
    connect(deleteButton, &QPushButton::clicked, this, &Form::onDeleteRow);
    layout->addWidget(deleteButton);

    // 设置布局边距和间距
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    // 假设 ui->page_2 是一个 QWidget 或其他容器控件，并且它有一个布局
    // 你需要将 centralWidget 添加到 ui->page_2 的布局中
    // 这里假设 ui->page_2->layout() 返回的是 ui->page_2 的布局指针
    parent->setLayout(layout);
}
void Form::onDeleteRow() {
    int currentRow = tableWidget->currentRow(); // 获取当前选中的行
    if (currentRow >= 0) {
        tableWidget->removeRow(currentRow); // 删除选中的行
        QList<int>p;
    } else {
        qDebug() << "没有行被选中";
        // 可以在这里添加额外的逻辑，比如显示一个消息框提示用户没有行被选中
    }
}
Form::~Form()
{

}
