#include "mainwindow.h"

#include <QApplication>
#include "mysql_op.h"
#include "statusbar_op.h"
#include "proceed_image.h"
#include <iostream>

void CheckSingle(int UID, MainWindow& w, MYSQL_OP& db,StatusBar_OP& statusbar)
{
    Proceed_Image proi;
    w.SetS_Question(proi.Proceed(db.Aquire(UID,3),7,290));
    w.SetS_Analysis(proi.Proceed(db.Aquire(UID,4),7,420));
    statusbar.Send("查询完成",w);
}

void CheckMultiple(QVector<int>& ID, MainWindow& w, MYSQL_OP& db,StatusBar_OP& statusbar,Proceed_Image& proi) {
    int type=13;
    w.ClearM();
    for(int i=0; i<ID.length(); i++) {
        int UID=ID[i];
        w.SetM_Analysis("("+QString::number(UID)+")<br/>"+proi.Proceed(db.Aquire(UID,type),type,420));
        statusbar.Send("已查询"+QString::number(i+1)+"/"+QString::number(ID.length())+"个",w);
    }
    statusbar.Send("查询完成",w);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    MYSQL_OP db;
    Proceed_Image proi;
    StatusBar_OP statusbar;
    db.Connect();
    statusbar.Send("数据库连接成功",w);
    QVector<int>ID;
    ID.push_back(11446);
    ID.push_back(11448);
    ID.push_back(11479);
    CheckMultiple(ID,w,db,statusbar,proi);
    return a.exec();
}
