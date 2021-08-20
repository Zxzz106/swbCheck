#ifndef MYSQL_OP_H
#define MYSQL_OP_H
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class MYSQL_OP
{
private:
    QSqlDatabase db;
public:
    MYSQL_OP();
    void Connect();
    void Aquire(int, int);
};

#endif // MYSQL_OP_H
