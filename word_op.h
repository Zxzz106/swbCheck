#ifndef WORD_OP_H
#define WORD_OP_H

#include <QObject>

class Word_OP : public QObject
{
    Q_OBJECT
public:
    explicit Word_OP(QObject *parent=0);
private:
    QString K_FileName;
};

#endif // WORD_OP_H
