#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>

#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printA();
    void updateTime();

    bool state = false;
    bool logState = false;
    bool pasState = false;
private slots:
    void on_Knopka_clicked();

    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_label_2_linkActivated(const QString &link);

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_Knopka_toggled(bool checked);

    void on_reg1_textChanged(const QString &arg1);

    void on_reg2_textChanged(const QString &arg1);

    void on_register_2_clicked();

    void on_label_3_linkActivated(const QString &link);

    void on_forgot_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_label_4_linkActivated(const QString &link);

    void on_pushButton_clicked();

    void on_ban_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase DB_Connection;
    QTimer *timer;
};
#endif // MAINWINDOW_H
