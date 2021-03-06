#include "proceed_image.h"

Proceed_Image::Proceed_Image()
{
    ptr=0;
    NAM=new QNetworkAccessManager(this);
}
void Proceed_Image::Request(QUrl* URL) {
    QTimer timer;
    QEventLoop eventloop;
    delete NAM;
    NAM=new QNetworkAccessManager(this);
    bool res;
    connect(&timer, &QTimer::timeout, [&eventloop, &res] {eventloop.quit(); res=0;});
    connect(NAM, &QNetworkAccessManager::finished, [&eventloop, &res](QNetworkReply*){eventloop.quit(); res=1;});
    QNetworkReply* Reply=NAM->get(QNetworkRequest(*URL));
    timer.start(3000);
    eventloop.exec();
    if(res) {
        if(Reply->error() == QNetworkReply::NoError) {
            QByteArray Bytes = Reply->readAll();
            QPixmap Img;
            Img.loadFromData(Bytes);
            File[ptr].open();
            Img.save(&File[ptr],"png");
        } else {
            //网络错误
        }
    } else {
        //连接超时
    }
    Reply->deleteLater();
}
void Proceed_Image::GetFile(QString url) {
    Request(new QUrl(url));
}

QString Proceed_Image::Proceed_WithImage(QString ostr, int width) {
    str.clear();
    bool b=0;
    for(int i=0; i<ostr.length(); i++) {
        if(ostr[i]=='<' && ostr[i+1]!='b') {
            url.clear();
            b=1;
            continue;
        }
        if(ostr[i]=='>'&&b==1) {
            GetFile(url);
            str+=QString("<br/><img src=\"")+File[ptr].fileName()+QString("\" alt=\"\" width="+QString::number(width)+" />");
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

QString Proceed_Image::Proceed(QString ostr, int type, int width=0) {
    if(type&8) return Proceed_NoImage(ostr);
    else return Proceed_WithImage(ostr,width);
}
