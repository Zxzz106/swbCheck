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
    void SetS_Question(const QString&);
    void SetS_Analysis(const QString&);
    void SetM_Analysis(const QString&);
    void ClearM();
private:
    Ui::MainWindow *ui;
private slots:
    void CheckS();
    void CheckM();
};
#endif // MAINWINDOW_H
