#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QProcess>
#include <QObject>
#include <QDebug>
#include <qlabel.h>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QStyle>
#include <QStylePainter>
#include <QTabBar>
#include<iostream>
#include <QApplication>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_5_clicked();
    void on_readoutput();
//    void on_readerror();


    void on_pushButton_6_clicked();
    void on_readoutput2();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void setLED(QLabel* label, int color, int size);
    void on_pushButton_9_clicked();

    void ZqzxSrsepc();
    void ZqzxSrsenb();



    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *process;
    QProcess *cmd;
    QProcess *cmd2;
    unsigned page_index;
    bool checkProcessRunning(const QString &processName,QList<quint64> &listProcessId);
    bool IsProcessExist(const QString &processName);
    bool checkProcessRunnin(const QString &srsenb);
    bool KillProcess(const QString &ProcessName);


 };
#endif // MAINWINDOW_H
