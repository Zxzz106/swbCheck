#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QIntValidator>
#include <QTextBlock>
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SendStatusBar(QString);
    void SetS_Question(const QString&);
    void SetS_Analysis(const QString&);
    void SetM_Analysis(const QString&);
private:
    Ui::MainWindow *ui;
    QLabel *StatusBarMessage;
    void CheckSingle(int, MainWindow*, MYSQL_OP*, Proceed_Image*);
    void CheckMultiple(QVector<int>*, int, MainWindow*, MYSQL_OP*, Proceed_Image*);
private slots:
    void CheckS();
    void CheckM();
};
#endif // MAINWINDOW_H
