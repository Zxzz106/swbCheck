#ifndef WORD_OP_H
#define WORD_OP_H

#include <QObject>
#include <QFile>
#include <QCoreApplication>
#include <QMessageBox>
#include <QStandardPaths>

class Word_OP : public QObject
{
    Q_OBJECT
public:
    Word_OP();
    QString SaveHtml(QString);
private:
};

#endif // WORD_OP_H
