#ifndef MYSQL_OP_H
#define MYSQL_OP_H
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QObject>
class MYSQL_OP
{
private:
    QSqlDatabase db;
    int UID;
    QString AquireStem();
    QString AquireChoices();
    QString AquireAnalysis_NoImg();
    QString AquireAnalysis();
    QString AquireVideo();
public:
    MYSQL_OP();
    void Connect();
    QString Aquire(int, int);
};

#endif // MYSQL_OP_H
