#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendStatusBar(QLabel* StatusBarMessage) {
    statusBar() -> addWidget(StatusBarMessage);
}

void MainWindow::SetS_Question(QString str) {
    ui->S_Question->setText(str);
}

void MainWindow::SetS_Analysis(QString str) {
    ui->S_Analysis->setText(str);
//    str=QString("错。当U形管的两侧液面不再变化时，液面高的一侧浓度高。<br/>【想一想答案】如图，h液柱会产生液体压强而产生向下的压力，但液面却是静止的，原因就在于另外有一个力，会促使水分子向A侧渗透，这两个力是相等的，所以A侧浓度高。<img src=\"http://qiniu.yongyuanqiang.com/012120071034p.png\" alt=\"\" style=\"width:300;\" /><br/>");
//    ui->S_Analysis->setText(str);
//    ui->S_Analysis->insertHtml(QString("<img src=\"http://qiniu.yongyuanqiang.com/01310001172p1.jpg\" alt=\"\" style=\"width:300;\" />"));
}

void MainWindow::SetM_Analysis(QString str) {
    ui->M_Analysis->setText(str);
}

