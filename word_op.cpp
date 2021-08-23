#include "word_op.h"

Word_OP::Word_OP() {
}

QString Word_OP::SaveHtml(QString html) {
    QFile f(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/print.html");
    RETRY:;
    if(f.exists() && !f.remove()) {
        int OP=QMessageBox::critical(NULL,QString("文件操作失败"),QString("请关闭相关Word文档(Print.html)"),QString("详细信息"),QString("重试"),QString("取消"),1);
        switch(OP) {
        case 0:{
            QMessageBox::information(NULL,QString("详细信息"),"Cannot delete Print.doc");
            goto RETRY;
            break;
        }
        case 1:{
            goto RETRY;
            break;
        }
        case 2:{
            return "";
            break;
        }
        default:{
            assert(0);
            break;
        }
        }
    }
    f.open(QIODevice::WriteOnly|QIODevice::Append);
    QTextStream ts(&f);
    ts<<html<<Qt::endl;
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/print.html";
}
