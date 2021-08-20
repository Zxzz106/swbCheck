#include "mainwindow.h"

#include <QApplication>
#include "mysql_op.h"
#include "statusbar_op.h"
#include "proceed_image.h"
#include <iostream>

void CheckSingle(int UID, MainWindow& w, MYSQL_OP& db,StatusBar_OP& statusbar)
{
    Proceed_Image proi;
    QString Res=proi.Proceed(db.Aquire(UID,3));
    w.SetS_Question(Res);
    Res=proi.Proceed(db.Aquire(UID,12));
    qDebug().noquote()<<Res;
    w.SetS_Analysis(Res);
    statusbar.Send("查询完成",w);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MYSQL_OP db;
    db.Connect();
    StatusBar_OP statusbar;
    statusbar.Send("数据库连接成功",w);
//    w.test();
    CheckSingle(11415,w,db,statusbar);
    return a.exec();
}
