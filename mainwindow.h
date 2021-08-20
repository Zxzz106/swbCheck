#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SendStatusBar(QLabel*);
    void SetS_Question(QString);
    void SetS_Analysis(QString);
    void SetM_Analysis(QString);
    void test(QString);
    void test();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
