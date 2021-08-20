#include "statusbar_op.h"
StatusBar_OP::StatusBar_OP()
{
    StatusBarMessage = new QLabel;
    StatusBarMessage -> setMinimumSize(StatusBarMessage -> sizeHint());
    StatusBarMessage -> setAlignment(Qt::AlignHCenter);
}

void StatusBar_OP::Send(QString str, MainWindow &w)
{
    StatusBarMessage->setText(str);
    w.statusBar() -> addWidget(StatusBarMessage);
    w.statusBar() -> setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}
