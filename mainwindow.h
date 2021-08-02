#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include<QSqlQuery>
#include"dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void connClose()
    {
        myfile.close();
        myfile.removeDatabase(QSqlDatabase::defaultConnection);

    }
    bool connOpen()
    {
        myfile=QSqlDatabase::addDatabase("QSQLITE");
        myfile.setDatabaseName("C:/database/database files/sqlite.db");
        if(!myfile.open())
        {
            qDebug()<<("Failed to open the database");
            return false;

        }
        else
        {
            qDebug()<<("Connected");
            return true;
        }
    }
    QSqlDatabase myfile;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
