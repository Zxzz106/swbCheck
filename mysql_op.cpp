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
QString MYSQL_OP::AquireStem() {
    QSqlQuery Query(QString("SELECT stem FROM swb WHERE UID = ")+QString::number(UID)+QString(";"),db);
    Query.next();
    return Query.value("stem").toString()+"<br/>";
}
QString MYSQL_OP::AquireChoices() {
    QSqlQuery Query(QString("SELECT answers FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
    return Query.value("answers").toString()+"<br/>";
}
QString MYSQL_OP::AquireAnalysis_NoImg() {
    QSqlQuery Query(QString("SELECT analysis_noimg FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
    return Query.value("analysis_noimg").toString()+"<br/>";
}
QString MYSQL_OP::AquireAnalysis() {
    QSqlQuery Query(QString("SELECT analysis FROM swb WHERE UID = ")+QString::number(UID),db);
    Query.next();
    return Query.value("analysis").toString()+"<br/>";
}
void MYSQL_OP::Aquire(int ID, int type) {
    UID=ID;
    QString Res="("+QString::number(UID)+")<br/>";
    switch (type) {
    case 1:{Res+=AquireStem(); break;}
    case 2:{Res+=AquireChoices(); break;}
    case 3:{Res+=AquireStem()+AquireChoices(); break;}
    case 4:{Res+=AquireAnalysis_NoImg(); break;}
    case 5:{Res+=AquireStem()+AquireAnalysis_NoImg(); break;}
    case 6:{Res+=AquireChoices()+AquireAnalysis_NoImg(); break;}
    case 7:{Res+=AquireStem()+AquireChoices()+AquireAnalysis_NoImg(); break;}
    case 8:{Res+=AquireAnalysis(); break;}
    case 9:{Res+=AquireStem()+AquireAnalysis(); break;}
    case 10:{Res+=AquireChoices()+AquireAnalysis(); break;}
    case 11:{Res+=AquireStem()+AquireChoices()+AquireAnalysis(); break;}
    case 12:{Res+=AquireAnalysis(); break;}
    case 13:{Res+=AquireStem()+AquireAnalysis(); break;}
    case 14:{Res+=AquireChoices()+AquireAnalysis(); break;}
    case 15:{Res+=AquireStem()+AquireChoices()+AquireAnalysis(); break;}
    default:{assert(0); break;}
    }
    qDebug()<<Res<<Qt::endl;
}
