#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    ui->Knopka->setEnabled(false);
    DB_Connection = QSqlDatabase::addDatabase("QSQLITE");
    DB_Connection.setDatabaseName(QCoreApplication::applicationDirPath() + "/data/MyDB.db");
    //DB_Connection.setDatabaseName("C:/Users/isage/Documents/databases/MyDB.db");

    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000);
    updateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    QString a = "Time: ";
    QTime time = QTime::currentTime();
    a.append(time.toString());
    ui->label_3->setText(a);

}

void MainWindow::printA()
{
    QTextStream qt(stdout);

    QString a = " Test";
    a.append(" Apex\n"); //end
    a.prepend("Test"); //start
    qt << a.toUpper();
}

void MainWindow::on_Knopka_clicked()
{
    if(state)
    {
        printA();
    }
    QString password = ui->lineEdit->text();
    QString login= ui->lineEdit_2->text();

    if(DB_Connection.open())
    {
        QSqlQuery query(DB_Connection);
        query.prepare("SELECT * FROM ApexLogin WHERE login = :login AND password = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", password);
        if(query.exec())
        {
            if(query.next())
            {
                ui->label_2->setText("loggined in");
            }
            else
            {
                ui->label_2->setText("invalid login or password");
            }
        }
        else
        {
            ui->label_2->setText("cannot load dataBase :(");
        }
        qDebug() << "connected to DB!";
    }
    else
    {
        qDebug() << "cannot open the DB";
        ui->label_2->setText("cannot load dataBase :(");

    }
    DB_Connection.close();

}
void MainWindow::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    state = !state;
    if(!state)
    {
        ui->label_2->setText("please, accept the rules.");
        ui->Knopka->setEnabled(false);
        cout << "Permission denied" << endl;
    }
    if(state)
    {
        ui->Knopka->setEnabled(true);
        ui->label_2->setText(" ");
        cout << "Permission accessed" << endl;
    }
}

void MainWindow::on_label_2_linkActivated(const QString &link)
{}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    //ui->lineEdit_2->setText(" ");
    logState = !logState;
    if(logState)
    {
        ui->lineEdit_2->blockSignals(true);
        ui->lineEdit_2->setText("");
        //ui->lineEdit_2->blockSignals(false);
    }

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    //QString password;
    pasState = !pasState;
    if(pasState)
    {
        ui->lineEdit->blockSignals(true);
        ui->lineEdit->setText("");
        ui->lineEdit->setEchoMode(QLineEdit::Password);
        //ui->lineEdit_2->blockSignals(false);
    }

}

void MainWindow::on_Knopka_toggled(bool checked)
{}

void MainWindow::on_lineEdit_2_returnPressed()
{}

void MainWindow::on_reg1_textChanged(const QString &arg1)
{
    bool regstate = false;
    regstate = !regstate;
    if(regstate)
    {
        ui->reg1->blockSignals(true);
        ui->reg1->setText("");
        //ui->lineEdit_2->blockSignals(false);
    }
}

void MainWindow::on_reg2_textChanged(const QString &arg1)
{
    bool regstate2 = false;
    regstate2 = !regstate2;
    if(regstate2)
    {
        ui->reg2->blockSignals(true);
        ui->reg2->setText("");
        //ui->lineEdit_2->blockSignals(false);
    }
}
//Register
void MainWindow::on_register_2_clicked()
{
    QString loginp = ui->reg1->text();
    QString registerp = ui->reg2->text();

    DB_Connection.open();
    QSqlDatabase::database().transaction();
    QSqlQuery Query_Insert_Data(DB_Connection);

    Query_Insert_Data.prepare("INSERT INTO ApexLogin(login, password) VALUES(:loginp,:registerp)");
    Query_Insert_Data.bindValue(":loginp", loginp);
    Query_Insert_Data.bindValue(":registerp", registerp);
    Query_Insert_Data.exec();
    QSqlDatabase::database().commit();
    DB_Connection.close();
}

void MainWindow::on_label_3_linkActivated(const QString &link)
{}

//restore password
void MainWindow::on_forgot_clicked()
{
    QString login = ui->lineEdit_3->text();
    if (DB_Connection.open())
    {
        QSqlQuery Query_Get_Data(DB_Connection);
        Query_Get_Data.prepare("SELECT password FROM ApexLogin WHERE login = :log");
        Query_Get_Data.bindValue(":log", login);

        if(Query_Get_Data.exec())
        {
            if(Query_Get_Data.next())
            {
                QString password = Query_Get_Data.value("password").toString();
                QString p = "PASSWORD: ";
                p.append(password);
                ui->label_4->setText(p);
            }
            else
            {
                ui->label_4->setText("Password not found");
            }
        }
        else
        {
            ui->label_4->setText("Query execution failed");
            qDebug() << "Query error: " << Query_Get_Data.lastError().text();
        }
        DB_Connection.close();
    }
    else
    {
        ui->label_4->setText("Failed to open database");
        qDebug() << "Database connection error: " << DB_Connection.lastError().text();
    }
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    bool regstate2 = false;
    regstate2 = !regstate2;
    if(regstate2)
    {
        ui->lineEdit_3->blockSignals(true);
        ui->lineEdit_3->setText("");
        //ui->lineEdit_2->blockSignals(false);
    }

    ui->forgot->setText("Restore Password");
}

void MainWindow::on_label_4_linkActivated(const QString &link)
{}
void MainWindow::on_pushButton_clicked()
{}

void MainWindow::on_ban_clicked()
{
    QString login = ui->lineEdit_4->text();
    qDebug() << "Login to delete:" << login;

    DB_Connection.open();

    QSqlDatabase::database().transaction();
    QSqlQuery Query_Delete_Data(DB_Connection);
    Query_Delete_Data.prepare("DELETE FROM ApexLogin WHERE login = :log");
    Query_Delete_Data.bindValue(":log", login);

    qDebug() << "Prepared query:" << Query_Delete_Data.executedQuery();

    if (Query_Delete_Data.exec())
    {
        QString ac = "Account ";
        ac.append(login);
        ac.append(" banned successfully");
        QSqlDatabase::database().commit();
        //qDebug() << "account banned successfully.";
        ui->label_5->setText(ac);
    }
    DB_Connection.close();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    bool regstate2 = false;
    regstate2 = !regstate2;
    if(regstate2)
    {
        ui->lineEdit_4->blockSignals(true);
        ui->lineEdit_4->setText("");
        //ui->lineEdit_2->blockSignals(false);
    }
}
