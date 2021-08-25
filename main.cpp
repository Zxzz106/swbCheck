#include "mainwindow.h"

#include <QApplication>
#include "mysql_op.h"
#include "proceed_image.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MYSQL_OP db;
    Proceed_Image proi;
    w.db=&db;
    w.proi=&proi;
    w.w=&w;
    w.SendStatusBar("正在连接数据库");
    db.Connect();
    w.SendStatusBar("数据库连接成功");
    return a.exec();
}
