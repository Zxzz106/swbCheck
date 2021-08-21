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

void MainWindow::SetS_Question(const QString& str) {
    ui->S_Question->setText(str);
}

void MainWindow::SetS_Analysis(const QString& str) {
    ui->S_Analysis->setText(str);
}

void MainWindow::SetM_Analysis(const QString& str) {
    ui->M_Analysis->insertHtml(str);
}

void MainWindow::ClearM() {
    ui->M_Analysis->clear();
}

void MainWindow::CheckS() {

}

void MainWindow::CheckM() {

}
