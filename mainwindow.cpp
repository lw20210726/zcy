#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#include <qfile.h>
#include <QMessageBox>
#include <QList>
#include <QTimer>
#include <QProcessEnvironment>
#define PATH_MAX_LEN 256

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setStyleSheet("QMaindWindow {background:url(:img/bj.png)}");
    setFixedSize(1700,900);
    //    cmd2 = new QProcess(this);
    process = new QProcess ;
    cmd = new QProcess(this);
    cmd2 = new QProcess(this);
    //    QProcess *pProc = new QProcess(this);
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
    //connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
    connect(cmd2 , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput2()));

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ZqzxSrsepc()));
    timer->start(2000);
    QTimer *timerEnb = new QTimer(this);
    connect(timerEnb,SIGNAL(timeout()),this,SLOT(ZqzxSrsenb()));
    timerEnb->start(2000);

}

MainWindow::~MainWindow()
{
    qDebug()<<"exit system!";
}

void MainWindow::closeEvent(QCloseEvent *event){
    this->close();
}

void MainWindow::on_pushButton_clicked()
{
    //    system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsenb'dist &");  /*//chmod a+x /home/xx/my.sh;*/
    //    system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsenb'&");  /*//chmod a+x /home/xx/my.sh;*/
    system("ps | grep srsenb |grep -v grep || echo 123456 | sudo -S sudo srsenb &");

}

void MainWindow::on_pushButton_2_clicked()
{
    system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsepc'&");
}

void MainWindow::on_pushButton_3_clicked()
{
        system("gnome-terminal -- bash -c 'echo 123456 | sudo -S sudo srsenb'&");
}

void MainWindow::on_pushButton_4_clicked()
{

    QProcess p(0); //进程会很快crash掉
    p.start("bash");
    p.waitForStarted();
    p.write("echo 123456 | sudo -S sudo srsenb\n");
   p.closeWriteChannel();
    p.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(p.readAllStandardOutput());
    qDebug()<<QProcess::NotRunning<<"Not running";
    qDebug()<<QProcess::Starting<<"starting";
    qDebug()<<QProcess::Running<<"Running";
    if(p.state()==QProcess::Starting)
    {
        setLED(ui->label_3,0,16);
    }
    if(p.state()==QProcess::Running)
    {
        setLED(ui->label_3,2,16);
    }
    if(p.state()==QProcess::NotRunning){
        setLED(ui->label_3,1,16);
    }

    else{
        setLED(ui->label_3,3,16);
    }

     if(p.state()==QProcess::FailedToStart){
         qDebug()<<"进程启动失败";
}
     if(p.state()==QProcess::Crashed){
         qDebug()<<"进程启动后崩溃";
}

}

void MainWindow::on_pushButton_5_clicked()
{


//    if(cmd->Running){
//        //cmd->kill();
//        cmd->write("q");
//        cmd->waitForStarted();
//    }
//     else{
//        ui->pushButton_5->setText("开启基站");
//        cmd->write("echo 123456 | sudo -S sudo srsenb\n");
//        cmd->waitForStarted();
//
    if(checkProcessRunnin("srsenb")==true)
    {
//        cmd->kill();     system("ps | grep srsenb |grep -v grep || echo 123456 | sudo -S sudo srsenb &");
        system("echo 123456 |sudo -S sudo killall -9 srsenb &");

    }
    else if(checkProcessRunnin("srsenb")==false)
    {

        cmd->start("bash"); //启动终端(Windows下改为cmd)

        cmd->waitForStarted(); //等待启动完成

        cmd->write("echo 123456 | sudo -S sudo srsenb\n"); //向终端写入“ls”命令，注意尾部的“\n”不可省略
    }


}


void MainWindow::on_readoutput()
{
    ui->textEdit->append(cmd->readAllStandardOutput().data());   //将输出信息读取到编辑框
}

//void MainWindow::on_readerror()
//{
//    QMessageBox::information(0, "Error", cmd2->readAllStandardError().data());    //弹出信息框提示错误信息
//}

void MainWindow::on_pushButton_6_clicked()
{

    if(checkProcessRunnin("srsepc")==false){

    cmd2->start("bash"); //启动终端(Windows下改为cmd)
    cmd2->waitForStarted(); //等待启动完成
    //    cmd->write("ls\n"); //向终端写入“ls”命令，注意尾部的“\n”不可省略
    cmd2->write("echo 123456 | sudo -S  srsepc\n"); //向终端写入“ls”命令，注意尾部的“\n”不可省略

} else{
        system("echo 123456 |sudo -S sudo killall -9 srsepc &");
    }


}

void MainWindow::on_readoutput2()
{
    ui->textEdit_2->append(cmd2->readAllStandardOutput().data());   //将输出信息读取到编辑框

}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    page_index=1;
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    page_index=0;
}
void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    page_index=2;
  }


// 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
// color 0:grey 1:red 2:green 3:yellow
// size  单位是像素
void MainWindow::setLED(QLabel* label, int color, int size)
{
    // 将label中的文字清空
    label->setText("");
    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}


/**
    * @brief 检测制定的进程是否正在运行
    *
    * @param processName 进程名称
    * @param listProcessId 正在运行的进程的Id
    * @return 如果有进程正在运行返回true,否则返回false
*/
bool MainWindow::checkProcessRunning(const QString &processName,
    QList<quint64> &listProcessId)
{
#ifdef Q_OS_WIN
    bool res = false;
    HANDLE    hToolHelp32Snapshot;
    hToolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32    pe = { sizeof(PROCESSENTRY32) };
    BOOL  isSuccess = Process32First(hToolHelp32Snapshot, &pe);
    while (isSuccess)
    {
        size_t len = WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, wcslen(pe.szExeFile), NULL, 0, NULL, NULL);
        char *des = (char *)malloc(sizeof(char) * (len + 1));
        WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, wcslen(pe.szExeFile), des, len, NULL, NULL);
        des[len] = '\0';
        if (!strcmp(des, processName.toStdString().c_str()))
        {
            listProcessId.append(pe.th32ProcessID);
            res = true;
        }
        free(des);
        isSuccess = Process32Next(hToolHelp32Snapshot, &pe);
    }
    CloseHandle(hToolHelp32Snapshot);
    return res;
#else
    bool res(false);
    QString strCommand = "ps -ef|grep " + processName + " |grep -v grep |awk '{print $2}'";
    QByteArray ba_str=strCommand.toUtf8();
    char *strFind_ComName=ba_str.data();
    //const char* strFind_ComName = convertQString2char(strCommand);
    FILE * pPipe = popen(strFind_ComName, "r");
    if (pPipe)
    {
        std::string com;
        char name[PATH_MAX_LEN];
        memset(name, 0, sizeof(PATH_MAX_LEN));
        while (fgets(name, sizeof(name), pPipe) != NULL)
        {
            int nLen = strlen(name);
            if (nLen > 0
                && name[nLen - 1] == '\n')
                //&& name[0] == '/')
            {
                name[nLen - 1] = '\0';
                listProcessId.append(atoi(name));
                res = true;
                //break;
            }
        }
        pclose(pPipe);
    }
    return res;
#endif
}



/**
    * @brief 检测制定的进程是否正在运行
    *
    * @param processName 进程名称
    * @param listProcessId 正在运行的进程的Id
    * @return 如果有进程正在运行返回true,否则返回false
*/
bool MainWindow::checkProcessRunnin(const QString &srsenb)
{
#ifdef Q_OS_WIN
    bool res = false;
    HANDLE    hToolHelp32Snapshot;
    hToolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32    pe = { sizeof(PROCESSENTRY32) };
    BOOL  isSuccess = Process32First(hToolHelp32Snapshot, &pe);
    while (isSuccess)
    {
        size_t len = WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, wcslen(pe.szExeFile), NULL, 0, NULL, NULL);
        char *des = (char *)malloc(sizeof(char) * (len + 1));
        WideCharToMultiByte(CP_ACP, 0, pe.szExeFile, wcslen(pe.szExeFile), des, len, NULL, NULL);
        des[len] = '\0';
        if (!strcmp(des, processName.toStdString().c_str()))
        {
            listProcessId.append(pe.th32ProcessID);
            res = true;
        }
        free(des);
        isSuccess = Process32Next(hToolHelp32Snapshot, &pe);
    }
    CloseHandle(hToolHelp32Snapshot);
    return res;
#else
    bool res(false);
    QString strCommand = "ps -ef|grep " + srsenb + " |grep -v grep |awk '{print $2}'";
    QByteArray ba_str=strCommand.toUtf8();
    char *strFind_ComName=ba_str.data();
    //const char* strFind_ComName = convertQString2char(strCommand);
    FILE * pPipe = popen(strFind_ComName, "r");
    if (pPipe)
    {
        std::string com;
        char name[PATH_MAX_LEN];
        memset(name, 0, sizeof(PATH_MAX_LEN));
        while (fgets(name, sizeof(name), pPipe) != NULL)
        {
//            int nLen = strlen(name);
//            if (nLen > 0
//                && name[nLen - 1] == '\n')
                //&& name[0] == '/')
//            {
//                name[nLen - 1] = '\0';
//                listProcessId.append(atoi(name));
//                res = true;
//                //break;
//            }
            res = true;

        }
        pclose(pPipe);
    }
    return res;
#endif
}


void MainWindow::ZqzxSrsepc(){
    qDebug() << checkProcessRunnin("srsepc");
    if(checkProcessRunnin("srsepc")==true)
    {
        setLED(ui->label_led1,2,16);
        ui->label->setText("核心网运行中。。");
        ui->pushButton_6->setText("停止核心网");
    }
    else if(checkProcessRunnin("srsepc")==false)
    {
        setLED(ui->label_led1,1,16);
        ui->label->setText("核心网已停止..");
        ui->pushButton_6->setText("开启核心网");
    }
}

void MainWindow::ZqzxSrsenb(){
    qDebug() << checkProcessRunnin("srsenb");
    if(checkProcessRunnin("srsenb")==true)
    {
        setLED(ui->label_led2,2,16);
        ui->label_2->setText("基站运行中。。");
        ui->pushButton_5->setText("停止基站");

    }
    else if(checkProcessRunnin("srsenb")==false)
    {
        setLED(ui->label_led2,1,16);
        ui->label_2->setText("基站已停止..");
         ui->pushButton_5->setText("开启基站");
    }
}






//bool MainWindow::KillProcess(const QString &ProcessName)
//{
// bool result = false;
// QString str1;

// HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0) ;
// PROCESSENTRY32 pInfo;
// pInfo.dwSize = sizeof(pInfo);

// Process32First(hSnapShot, &pInfo);
// do
// {
//  str1 = (QString::fromUtf16(reinterpret_cast<const unsigned short *>(pInfo.szExeFile)));
//  if (str1 == ProcessName)
//  {
//   result = true;
//   QString cmd;
//   cmd = QString("taskkill /F /PID %1 /T").arg(pInfo.th32ProcessID);

//   system(cmd.toAscii());
//  }
// } while(Process32Next(hSnapShot, &pInfo) );
// return result;
//}



