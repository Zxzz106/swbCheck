#ifndef MYSQL_OP_H
#define MYSQL_OP_H
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
class MYSQL_OP
{
private:
    QSqlDatabase db;
    int UID;
    QString AquireStem();
    QString AquireChoices();
    QString AquireAnalysis_NoImg();
    QString AquireAnalysis();
public:
    MYSQL_OP();
    void Connect();
    void Aquire(int, int);
};

#endif // MYSQL_OP_H
