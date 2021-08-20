#ifndef STATUSBAR_OP_H
#define STATUSBAR_OP_H
#include <QLabel>
#include <QStatusBar>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include "mainwindow.h"
class StatusBar_OP
{
private:
    QAction *OP;
    QLabel *StatusBarMessage;
public:
    StatusBar_OP();
    void Send(QString,MainWindow&);
};

#endif // STATUSBAR_OP_H
