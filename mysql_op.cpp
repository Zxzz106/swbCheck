#include "mysql_op.h"

MYSQL_OP::MYSQL_OP()
{
}

void MYSQL_OP::Connect()
{

    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("rm-2ze0r60aa9cu13b13ho.mysql.rds.aliyuncs.com");
    db.setPort(3306);
    db.setUserName("swb");
    db.setPassword("LWH_774190");
    db.setDatabaseName("swb");
RETRY:;
    if(!db.open()){
        int OP=QMessageBox::critical(NULL,QString("数据库连接失败"),QString("请检查您的网络链接"),QString("详细信息"),QString("重试"),QString("退出"),1);
        switch(OP) {
        case 0:{
            QMessageBox::information(NULL,QString("详细信息"),db.lastError().text());
            goto RETRY;
            break;
        }
        case 1:{
            goto RETRY;
            break;
        }
        case 2:{
            exit(0);
            break;
        }
        default:{
            assert(0);
            break;
        }
        }
        return;
    }
}
bool MYSQL_OP::Exists() {
    QSqlQuery Query(QString("SELECT UID FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
    return Query.isValid();
}
QString MYSQL_OP::AquireStem() {
    QSqlQuery Query(QString("SELECT stem FROM swb WHERE UID = ")+QString::number(UID)+QString(";"),db);
    Query.next();
//    qDebug()<<"AquireStem";
    return Query.value("stem").toString()+"<br/>";
}
QString MYSQL_OP::AquireChoices() {
    QSqlQuery Query(QString("SELECT answers FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
//    qDebug()<<"AquireChoices";
    return Query.value("answers").toString();
}
QString MYSQL_OP::AquireAnalysis() {
    QSqlQuery Query(QString("SELECT analysis FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
//    qDebug()<<"AquireAnalysis";
    return Query.value("analysis").toString()+"<br/>";
}
QString MYSQL_OP::AquireVideo() {
    QSqlQuery Query(QString("SELECT videoUrl FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
//    qDebug()<<"AquireVideo";
//    qDebug()<<Query.value("videoUrl").toString();
    return Query.value("videoUrl").toString();
}
QString MYSQL_OP::Aquire(int ID, int type) {
    UID=ID;
    QString Res;
    if(!Exists()) return "无数据";
    if(type&1) Res+=AquireStem();
    if(type&2) Res+=AquireChoices();
    if(type&4) Res+=AquireAnalysis();
    return Res;
}
