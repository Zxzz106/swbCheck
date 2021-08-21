#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->S_InputUID->setValidator(new QIntValidator(ui->S_InputUID));
    ID=new QVector<int>;
    StatusBarMessage = new QLabel;
    StatusBarMessage -> setMinimumSize(StatusBarMessage -> sizeHint());
    StatusBarMessage -> setAlignment(Qt::AlignHCenter);
    connect(ui->S_Check,&QPushButton::clicked,this,&MainWindow::CheckS);
    connect(ui->S_InputUID, &QLineEdit::returnPressed, this, &MainWindow::CheckS);
    connect(ui->M_Check, &QPushButton::clicked, this, &MainWindow::CheckM);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendStatusBar(QString str) {
    StatusBarMessage->setText(str);
    w->statusBar() -> addWidget(StatusBarMessage);
    w->statusBar() -> setStyleSheet(QString("QStatusBar::item{border: 0px}"));
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

void MainWindow::CheckSingle(int UID, MainWindow* w, MYSQL_OP* db, Proceed_Image* proi)
{
    w->SetS_Question(proi->Proceed(db->Aquire(UID,3),7,290));
    w->SetS_Analysis(proi->Proceed(db->Aquire(UID,4),7,420));
    SendStatusBar("查询完成");
}

void MainWindow::CheckS() {
    int UID=ui->S_InputUID->text().toInt();
    CheckSingle(UID,w,db,proi);
    if(db->Exists()) {
        QString str=db->AquireVideo();
        if(str==(QString)"") {
            ui->S_PlayVideo->setEnabled(false);
            return;
        }
        ui->S_PlayVideo->setEnabled(true);
    }
    else ui->S_PlayVideo->setEnabled(false);
}

void MainWindow::CheckMultiple(QVector<int>* ID, int type, MainWindow* w, MYSQL_OP* db, Proceed_Image* proi) {
    for(int i=0; i<ID->length(); i++) {
        int UID=ID->at(i);
        w->SetM_Analysis("("+QString::number(UID)+")<br/>"+proi->Proceed(db->Aquire(UID,type),type,420));
        SendStatusBar("已查询"+QString::number(i+1)+"/"+QString::number(ID->length())+"个");
    }
    SendStatusBar("查询完成");
}

void MainWindow::CheckM() {
    ui->M_Analysis->clear();
    QTextDocument* Doc;
    Doc=ui->M_InputUID->document();
    for(QTextBlock it=Doc->begin(); it!=Doc->end(); it=it.next())
        ID->push_back(it.text().toInt());
    int type=0;
    if(ui->checkBox_Stem->isChecked()) type+=1;
    if(ui->checkBox_Choice->isChecked()) type+=2;
    if(ui->checkBox_Analysis->isChecked()) type+=4;
    if(ui->checkBox_Image->isChecked()) type+=8;
    CheckMultiple(ID,type,w,db,proi);
}
