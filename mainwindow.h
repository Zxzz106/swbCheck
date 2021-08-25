#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QIntValidator>
#include <QTextBlock>
#include <QDesktopServices>
#include <QClipboard>
#include <QTextBrowser>
#include <QProcess>
#include <QAction>
#include "mysql_op.h"
#include "proceed_image.h"
#include "word_op.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow* w;
    MYSQL_OP* db;
    Proceed_Image* proi;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SendStatusBar(QString);
    void SetS_Question(const QString&);
    void SetS_Analysis(const QString&);
    void SetM_Result(const QString&);
    void SetK_Result(const QString&);
private:
    Ui::MainWindow *ui;
    QLabel *StatusBarMessage;
    QVector<int>* ID;
    QTextBrowser *temp;
    QUrl VideoURL;
    Word_OP* Printer;
    QAction* Shortcut;
    QProcess cli;
    int UID;
    void CheckSingle(MainWindow*, MYSQL_OP*, Proceed_Image*);
    void CheckMultiple(QVector<int>*, int, MainWindow*, MYSQL_OP*, Proceed_Image*);
    QString GetPrinthtml(QString);
private slots:
    void CheckS();
    void CheckM();
    void CopyStem();
    void CopyChoice();
    void CopyBoth();
    void CopyAnalysis();
    void CopyM();
    void PlayVideo();
    void Check_K_Question();
    void Check_K_Analysis();
    void Check_K_QA();
    void GotoM();
    void SetS_Input_Color();
    void SetM_Input_Color();
    void PrintS();
    void PrintM();
    void Print();
};
#endif // MAINWINDOW_H
