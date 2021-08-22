#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QIntValidator>
#include <QTextBlock>
#include <QDesktopServices>
#include <QClipboard>
#include <QTextBrowser>
#include "mysql_op.h"
#include "proceed_image.h"

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
    QVector<int>* ID;
    QClipboard* clip;
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
    QTextBrowser *temp;
    QUrl VideoURL;
    int UID;
    void CheckSingle(MainWindow*, MYSQL_OP*, Proceed_Image*);
    void CheckMultiple(QVector<int>*, int, MainWindow*, MYSQL_OP*, Proceed_Image*);
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
};
#endif // MAINWINDOW_H
