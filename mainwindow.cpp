#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!connOpen())
    {
        ui->label->setText("Failed to open the database");

    }
    else
        ui->label->setText("Connected");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    QString name,password;

    name=ui->lineEdit->text();
    password=ui->lineEdit_2->text();
    if (!connOpen())
    {
        qDebug()<<"Failed to open the Database";
        return;
    }


//    QSqlQuery qry;
//    if(qry.exec("SELECT name FROM admins WHERE name=\'"+name+"\'"))
//    {
//        if(qry.next())
//        {
//            ui->label->setText("Correct");
//            QString msg="name= "+qry.value(0).toString();
//        }
//        else
//            ui->label->setText("Wrong");
//    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT Name FROM demo WHERE Name='"+name+"' and Password='"+password+"'");
    if(qry.exec())
    {

        ui->label->setText("opened");
        int count=0;
        while(qry.next())
        {
            count++;
        }
        if (count==1)
        {
            ui->label->setText("username and password are correct");
            Dialog dialog;
            hide();
            dialog.setModal(true);
            dialog.exec();
            connClose();

        }

        if (count<1)
        {
            ui->label->setText("username and password is not correct");
        }

    }
}
