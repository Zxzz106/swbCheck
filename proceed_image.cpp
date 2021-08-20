#include "proceed_image.h"

Proceed_Image::Proceed_Image()
{
    ptr=0;
}

void Proceed_Image::GetFile(QString url,QTemporaryFile& f) {
    qDebug().noquote()<<url<<Qt::endl;
    QUrl URL(url);
    QNetworkRequest Req(URL);
    QNetworkAccessManager NAM;
    QNetworkReply *reply=NAM.get(Req);
    qDebug()<<reply->error();
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray data_bytes = reply->readAll();
        qDebug()<<data_bytes<<Qt::endl;
        QPixmap* cur_pictrue =new QPixmap();
        cur_pictrue->loadFromData(data_bytes);
        cur_pictrue->save("D:\\Code\\Qt\\data\\cur_night_picture.png");
    }
    reply->deleteLater();
}

QString Proceed_Image::Proceed(QString ostr) {
    str.clear();
    bool b=0;
    for(int i=0; i<ostr.length(); i++) {
        if(ostr[i]=='<' && ostr[i+1]!='b') {
            url.clear();
            b=1;
            continue;
        }
        if(ostr[i]=='>'&&b==1) {
            GetFile(url,File[ptr]);
            str+=QString("<img src=\"")+File[ptr].fileName()+QString("\" alt=\"\" width=300\" />");
            ptr++;
            b=0;
            continue;
        }
        if(b==1) {
            url+=ostr[i];
        } else {
            str+=ostr[i];
        }
    }
    return str;
}

QString Proceed_Image::Proceed_NoImage(QString ostr) {
    str.clear();
    bool b=0;
    for(int i=0; i<ostr.length(); i++) {
        if(ostr[i]=='<' && ostr[i+1]!='b') {
            url.clear();
            b=1;
            continue;
        }
        if(ostr[i]=='>'&&b==1) {
            b=0;
            continue;
        }
        if(b==0) {
            str+=ostr[i];
        }
    }
    return str;
}
