#ifndef MODIFYCONF_H
#define MODIFYCONF_H
#include <QMenu>
#include <QWidget>

namespace Ui {
class ModifyConf;
}

class ModifyConf : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyConf(QWidget *parent = nullptr);
    ~ModifyConf();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ModifyConf *ui;
    QString FilePath;
};

#endif // MODIFYCONF_H
