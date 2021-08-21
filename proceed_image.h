#ifndef PROCEED_IMAGE_H
#define PROCEED_IMAGE_H
#include <QVector>
#include <QTemporaryFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>
#include <QAction>
#include <QDialog>
#include <QEventLoop>
#include <QTimer>

class Proceed_Image : public QObject
{
    Q_OBJECT
private:
    QTemporaryFile File[200];
    QString str,url;
    int ptr;
    QNetworkAccessManager* NAM;
    void GetFile(QString);
    void Request(QUrl*);
public:
    Proceed_Image();
    QString Proceed_WithImage(QString, int);
    QString Proceed_NoImage(QString);
    QString Proceed(QString, int, int);
private slots:
//    void Save(QNetworkReply *);
};

#endif // PROCEED_IMAGE_H
