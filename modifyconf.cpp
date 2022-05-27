#include "modifyconf.h"
#include "ui_modifyconf.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QAction>
ModifyConf::ModifyConf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModifyConf)
{
    ui->setupUi(this);
}

ModifyConf::~ModifyConf()
{
    delete ui;
}

void ModifyConf::on_pushButton_clicked()
{
    QString filename("/etc/srsran/epc.conf");
    QFile file(filename);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString s; //用于接受数据
//        m_textEdit = new QTextEdit(this);
//        m_textEdit->setReadOnly(true);  //将文本设置为只读
        while(!stream.atEnd()){
           s+=stream.readLine();
           s+="\n";
        }
        ui->textEdit->setText(s);        //将数据显示到文本框中
//        m_layout->addWidget(m_textEdit,0,0);
        //参数:子窗口,横坐标,纵坐标.
        //如果没有上面这条语句,那么显示只会在一个小框框里
        file.close();
    }else{
       QMessageBox::information(this,"提示","文件打开失败！");
    }
}

void ModifyConf::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("提示");
    msgBox.setInformativeText("确实要保存核心网配置吗?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){

    //      QString filename = QFileDialog::getSaveFileName(this, " 另存为 " , "/etc/srsran/epc.conf","*.conf" );
        QString filename("/etc/srsran/epc.conf");
        QFile file(filename);//创建文件对象
        bool tag = file.open(QIODevice::WriteOnly);//写内容到文件中
        if(!tag)
        {
            return;
        }
        QString text = ui->textEdit->toPlainText();//文本框中的内容
        file.write(text.toUtf8());//将text内容转化为字节数组

        file.close();
        QMessageBox::information(this,"提示","文件保存成功！");
    }    else{
            return;
        }


}

void ModifyConf::on_pushButton_3_clicked()
{
    QString filename("/etc/srsran/enb.conf");
    QFile file(filename);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString s; //用于接受数据
//        m_textEdit = new QTextEdit(this);
//        m_textEdit->setReadOnly(true);  //将文本设置为只读
        while(!stream.atEnd()){
           s+=stream.readLine();
           s+="\n";
        }
        ui->textEdit->setText(s);        //将数据显示到文本框中
//        m_layout->addWidget(m_textEdit,0,0);
        //参数:子窗口,横坐标,纵坐标.
        //如果没有上面这条语句,那么显示只会在一个小框框里
        file.close();
    }
    else{
       QMessageBox::information(this,"提示","文件打开失败！");
    }
}

void ModifyConf::on_pushButton_4_clicked()
{

    // QString filename = QFileDialog::getSaveFileName(this, " 另存为 " , "/root/.config/srsran/enb.conf","*.conf" );

    QMessageBox msgBox;
    msgBox.setText("提示");
    msgBox.setInformativeText("确实要保存基站配置吗?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        QString filename("/etc/srsran/enb.conf");
        QFile file(filename);//创建文件对象
        bool tag = file.open(QIODevice::WriteOnly);//写内容到文件中
        if(!tag)
        {
            return;
        }
        QString text = ui->textEdit->toPlainText();//文本框中的内容
        file.write(text.toUtf8());//将text内容转化为字节数组
        file.close();
        QMessageBox::information(this,"提示","文件保存成功！");
    }
    else{
        return;
    }

}

