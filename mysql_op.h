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
    QString AquireAnalysis();
    void AquireKeyFromStem(QString,QVector<int>&);
    void AquireKeyFromChoices(QString,QVector<int>&);
    void AquireKeyFromAnalysis(QString,QVector<int>&);
public:
    MYSQL_OP();
    void Connect();
    bool Exists();
    QString Aquire(int, int);
    QString AquireVideo();
    QString AquireKey(QString,int);
};

#endif // MYSQL_OP_H
