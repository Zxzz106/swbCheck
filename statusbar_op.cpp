#include "statusbar_OP.h"

StatusBar_OP::StatusBar_OP()
{
    StatusBarMessage = new QLabel;
    StatusBarMessage -> setMinimumSize(StatusBarMessage -> sizeHint());
    StatusBarMessage -> setAlignment(Qt::AlignHCenter);
//    QStatusBar::addWidget(StatusBarMessage);
}
void StatusBar_OP::Send()
{

}
