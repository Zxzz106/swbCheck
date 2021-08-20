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
    if(!db.open()){ //数据库打开失败
        int OP=QMessageBox::critical(NULL,QString("数据库连接失败"),QString("请检查您的网络链接"),QString("详细信息"),QString("重试"),QString("退出"),1);
        switch(OP) {
        case 0:{
            QMessageBox::information(NULL,QString("详细信息"),db.lastError().text());
            goto RETRY;
        }
        case 1:{
            goto RETRY;
        }
        case 2:{
            exit(0);
        }
        default:{
            assert(0);
        }
        }
        return;
    }
}

void MYSQL_OP::Aquire(int UID, int type) {
    QString TypeString;
    switch (type) {
    case 1:{TypeString="stem";}
    case 2:{TypeString="answers";}
    case 3:{TypeString="stem,answers";}
    case 4:{TypeString="analysis_noimg";}
    case 5:{TypeString="stem,analysis_noimg";}
    case 6:{TypeString="answers,analysis_noimg";}
    case 7:{TypeString="stem,answers,analysis_noimg";}
    case 8:{TypeString="analysis";}
    case 9:{TypeString="stem,analysis";}
    case 10:{TypeString="answers,analysis";}
    case 11:{TypeString="stem,answers,analysis";}
    case 12:{TypeString="analysis";}
    case 13:{TypeString="stem,analysis";}
    case 14:{TypeString="answers,analysis";}
    case 15:{TypeString="stem,answers,analysis";}
    }
    QString QueryString=QString("SELECT ")+TypeString+QString(" FROM swb WHERE UID = ");
    QSqlQuery query(QueryString+QString::number(UID)+QString(";"),db);
    QSqlRecord rec=query.record();
}
