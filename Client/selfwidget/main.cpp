#include <QApplication>
#include"login.h"
#include"log_main.h"
#include"QsLog/include/QsLog.h"
#include"QsLog/include/QsLogDest.h"
using namespace QsLogging;
#include "log_main.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    //log_main w;
    w.show();
    return a.exec();
}
