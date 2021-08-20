#ifndef PROCEED_IMAGE_H
#define PROCEED_IMAGE_H
#include <QVector>
#include <QTemporaryFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class Proceed_Image
{
private:
    QTemporaryFile File[200];
    QString str,url;
    int ptr;
//    QTemporaryFile *tempfile;
public:
    Proceed_Image();
    void GetFile(QString, QTemporaryFile&);
    QString Proceed(QString);
    QString Proceed_NoImage(QString);
};

#endif // PROCEED_IMAGE_H
