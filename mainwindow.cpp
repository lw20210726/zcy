#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <qfile.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    process = new QProcess ;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsenb'dist &");  /*//chmod a+x /home/xx/my.sh;*/
    system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsenb'&");  /*//chmod a+x /home/xx/my.sh;*/

}


void MainWindow::on_pushButton_2_clicked()
{
  system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsepc'&");
}







void MainWindow::on_pushButton_4_clicked()
{

    if (process->state()==QProcess::Running)
    {
        process->kill();
       process->waitForFinished();
    }
//    process->start("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsepc'&");

      process->start("notepad");
}

