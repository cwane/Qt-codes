#include "dialog.h"
#include "ui_dialog.h"
#include"QMessageBox"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    MainWindow conn;
    if(!conn.connOpen())
    {
        ui->label->setText("Failed to open the database");

    }
    else
        ui->label->setText("Connected");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    MainWindow conn;
    QString id,name,password;
    id=ui->lineEdit->text();
    name=ui->lineEdit_2->text();
    password=ui->lineEdit_3->text();
    if (!conn.connOpen())
    {
        qDebug()<<"Failed to open the Database";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into demo (ID,Name,Password) values ('"+id+"','"+name+"','"+password+"')");
    if(qry.exec())
    {
      QMessageBox::critical(this,tr("Save data"),tr("Data is saved"));
      conn.connClose();

    }
    else
        QMessageBox::warning(this,tr("Save data"),tr("Data is not saved"));

}
