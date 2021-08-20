#include "mainwindow.h"

#include <QApplication>
#include "mysql_op.h"
#include "statusbar_op.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MYSQL_OP db;
    db.Connect();
//    StatusBar_OP::Send("数据库连接成功");
    db.Aquire(12345,15);
    return a.exec();
}
