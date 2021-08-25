#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/fdroid.png"));
    ui->S_InputUID->setFocus();
    ui->S_InputUID->setValidator(new QIntValidator(ui->S_InputUID));
    ID=new QVector<int>;
    StatusBarMessage = new QLabel;
    temp= new QTextBrowser;
    Printer=new Word_OP;
    StatusBarMessage -> setMinimumSize(StatusBarMessage -> sizeHint());
    StatusBarMessage -> setAlignment(Qt::AlignHCenter);
    connect(ui->S_Check,&QPushButton::clicked,this,&MainWindow::CheckS);
    connect(ui->S_InputUID, &QLineEdit::returnPressed, this, &MainWindow::CheckS);
    connect(ui->M_Check, &QPushButton::clicked, this, &MainWindow::CheckM);
    ui->M_Check->setShortcut(Qt::Key_F5);
    connect(ui->S_CopyStem,&QPushButton::clicked,this,&MainWindow::CopyStem);
    connect(ui->S_CopyChoice,&QPushButton::clicked,this,&MainWindow::CopyChoice);
    connect(ui->S_CopyBoth,&QPushButton::clicked,this,&MainWindow::CopyBoth);
    connect(ui->S_CopyAnalysis,&QPushButton::clicked,this,&MainWindow::CopyAnalysis);
    connect(ui->M_Copy,&QPushButton::clicked,this,&MainWindow::CopyM);
    connect(ui->K_Question,&QPushButton::clicked,this,&MainWindow::Check_K_Question);
    connect(ui->K_Analysis,&QPushButton::clicked,this,&MainWindow::Check_K_Analysis);
    connect(ui->K_QA,&QPushButton::clicked,this,&MainWindow::Check_K_QA);
    connect(ui->K_Input,&QLineEdit::returnPressed, this, &MainWindow::Check_K_Question);
    connect(ui->K_GotoM,&QPushButton::clicked,this,&MainWindow::GotoM);
    connect(ui->S_InputUID,&QLineEdit::textEdited,this,&MainWindow::SetS_Input_Color);
    connect(ui->M_InputUID,&QPlainTextEdit::textChanged,this,&MainWindow::SetM_Input_Color);
    connect(ui->S_Print,&QPushButton::clicked,this,&MainWindow::PrintS);
    connect(ui->M_Print,&QPushButton::clicked,this,&MainWindow::PrintM);
    Shortcut=new QAction;
    Shortcut->setShortcut(tr("Ctrl+P"));
    this->addAction(Shortcut);
    connect(Shortcut,&QAction::triggered,this,&MainWindow::Print);
    ui->S_InputUID->setStyleSheet("color:#a9a9a9");
    ui->S_InputUID->setPlaceholderText("12345");
    ui->M_InputUID->setStyleSheet("color:#a9a9a9");
    ui->M_InputUID->setPlaceholderText("12345\n12346\n12356\n12456\n13456\n23456");

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

void MainWindow::SetM_Result(const QString& str) {
    ui->M_Result->insertHtml(str);
}

void MainWindow::SetK_Result(const QString& str) {
    ui->K_Result->setText(str);
}

void MainWindow::CheckSingle(MainWindow* w, MYSQL_OP* db, Proceed_Image* proi)
{
    w->SetS_Question(proi->Proceed(db->Aquire(UID,3),7,280));
    w->SetS_Analysis(proi->Proceed(db->Aquire(UID,4),7,390));
    SendStatusBar("查询完成");
}

void MainWindow::PlayVideo() {
    QDesktopServices::openUrl(VideoURL);
}

void MainWindow::CheckS() {
    ui->S_Check->setCheckable(false);
    ui->S_Check->setEnabled(false);
    disconnect(ui->S_InputUID, &QLineEdit::returnPressed, this, &MainWindow::CheckS);
    SendStatusBar("正在查询");
    UID=ui->S_InputUID->text().toInt();
    CheckSingle(w,db,proi);
    if(db->Exists()) {
        QString str=db->AquireVideo();
        if(str==(QString)"")
            ui->S_PlayVideo->setEnabled(false);
        else {
            ui->S_PlayVideo->setEnabled(true);
            VideoURL=QUrl(str);
            connect(ui->S_PlayVideo,&QPushButton::clicked,this,&MainWindow::PlayVideo);
        }
    }
    else ui->S_PlayVideo->setEnabled(false);
    connect(ui->S_InputUID, &QLineEdit::returnPressed, this, &MainWindow::CheckS);
    ui->S_Check->setEnabled(true);
    ui->S_Check->setCheckable(true);
}

void MainWindow::CheckMultiple(QVector<int>* ID, int type, MainWindow* w, MYSQL_OP* db, Proceed_Image* proi) {
    for(int i=0; i<ID->length(); i++) {
        int UID=ID->at(i);
        if(i==0) w->SetM_Result("<b><font color=\"red\">("+QString::number(UID)+")</font></b><br/>"+proi->Proceed(db->Aquire(UID,type),type,390));
        else w->SetM_Result("<br/><b><font color=\"red\">("+QString::number(UID)+")</font></b><br/>"+proi->Proceed(db->Aquire(UID,type),type,390));
        SendStatusBar("已查询"+QString::number(i+1)+"/"+QString::number(ID->length())+"个");
    }
    SendStatusBar("查询完成");
}

void MainWindow::CheckM() {
    ui->M_Check->setCheckable(false);
    ui->M_Check->setEnabled(false);
    ui->M_Result->clear();
    ID->clear();
    QTextDocument* Doc;
    Doc=ui->M_InputUID->document();
    for(QTextBlock it=Doc->begin(); it!=Doc->end(); it=it.next()) {
        ID->push_back(it.text().toInt());
        if(ID->back()==0) ID->pop_back();
    }
    int type=0;
    if(ui->checkBox_Stem->isChecked()) type+=1;
    if(ui->checkBox_Choice->isChecked()) type+=2;
    if(ui->checkBox_Analysis->isChecked()) type+=4;
    if(ui->checkBox_Image->isChecked()) type+=8;
    CheckMultiple(ID,type,w,db,proi);
    ui->M_Check->setEnabled(true);
    ui->M_Check->setCheckable(true);
}

void MainWindow::CopyStem() {
    temp->setText(proi->Proceed(db->Aquire(UID,1),7,280));
    temp->selectAll();
    temp->copy();
    ui->S_InputUID->setFocus();
    SendStatusBar("复制成功(题干)");
}

void MainWindow::CopyChoice() {
    temp->setText(proi->Proceed(db->Aquire(UID,2),7,280));
    temp->selectAll();
    temp->copy();
    ui->S_InputUID->setFocus();
    SendStatusBar("复制成功(选项)");
}

void MainWindow::CopyBoth() {
    ui->S_Question->selectAll();
    ui->S_Question->copy();
    QTextCursor cursor=ui->S_Question->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->S_Question->setTextCursor(cursor);
    ui->S_InputUID->setFocus();
    ui->S_InputUID->setFocus();
    SendStatusBar("复制成功(题面)");
}

void MainWindow::CopyAnalysis() {
    ui->S_Analysis->selectAll();
    ui->S_Analysis->copy();
    QTextCursor cursor=ui->S_Analysis->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->S_Analysis->setTextCursor(cursor);
    ui->S_InputUID->setFocus();
    SendStatusBar("复制成功(解析)");
}

void MainWindow::CopyM() {
    ui->M_Result->selectAll();
    ui->M_Result->copy();
    ui->M_InputUID->setFocus();
    SendStatusBar("复制成功(查询结果)");
}

void MainWindow::Check_K_Question() {
    SetK_Result(db->AquireKey(ui->K_Input->text(),1+(ui->K_IncludeChoice->isChecked()?2:0)));
    SendStatusBar("查询完成");
}

void MainWindow::Check_K_Analysis() {
    SetK_Result(db->AquireKey(ui->K_Input->text(),4));
    SendStatusBar("查询完成");
}

void MainWindow::Check_K_QA() {
    SetK_Result(db->AquireKey(ui->K_Input->text(),7));
    SendStatusBar("查询完成");
}

void MainWindow::GotoM() {
    ui->M_InputUID->setPlainText(ui->K_Result->toPlainText());
    ui->Tabs->setCurrentIndex(1);
}

void MainWindow::SetS_Input_Color() {
    ui->S_InputUID->setStyleSheet("color:#000000");
    ui->S_InputUID->setPlaceholderText("");
}

void MainWindow::SetM_Input_Color() {
    ui->M_InputUID->setStyleSheet("color:#000000");
    ui->M_InputUID->setPlaceholderText("");
}

QString MainWindow::GetPrinthtml(QString html) {
    QString res;
    bool b=0;
    for(int i=0; i<html.length(); i++) {
        if(html[i]=='w' && html[i+1]=='i' &&  html[i+2]=='d') {
            i+=6;
            b=1;
            continue;
        }
        if(b) {
            if(html[i]=='"') {
                b=0;
                continue;
            }
            else continue;
        }
        if(html[i]=='#' && html[i+1]=='f' && html[i+2]=='f' && html[i+3]=='0' && html[i+4]=='0' && html[i+5]=='0' && html[i+6]=='0') {
            html[i+1]='a';
            html[i+2]='b';
            html[i+3]='a';
            html[i+4]='d';
            html[i+5]='f';
            html[i+6]='c';
        }
        res+=html[i];
    }
    qDebug()<<res;
    return res;
}

void MainWindow::PrintS() {
    SendStatusBar("尝试打印");
    QString html=GetPrinthtml(ui->S_Analysis->toHtml());
    QString FileName=Printer->SaveHtml(html);
    if(FileName==QString("")) {
        SendStatusBar("打印失败");
        return;
    }
    QStringList args;
    args<<"\t"<<FileName;
    cli.start("C:/Program Files (x86)/Microsoft Office/root/Office16/WINWORD.EXE",args);
    cli.waitForFinished(500);
}

void MainWindow::PrintM() {
    SendStatusBar("尝试打印");
    QString html=GetPrinthtml(ui->M_Result->toHtml());
    QString FileName=Printer->SaveHtml(html);
    if(FileName==QString("")) {
        SendStatusBar("打印失败");
        return;
    }
    QStringList args;
    args<<"\t"<<FileName;
    cli.start("C:/Program Files (x86)/Microsoft Office/root/Office16/WINWORD.EXE",args);
    cli.waitForFinished(500);
}

void MainWindow::Print() {
    qDebug("Printing");
    switch(ui->Tabs->currentIndex()) {
    case 0: {
        PrintS();
        break;
    }
    case 1: {
        PrintM();
        break;
    }
    case 2: {
        QMessageBox::information(NULL,QString("打印失败"),"无可用打印内容");
        break;
    }
    default: {
        assert(0);
        break;
    }
    }
}
