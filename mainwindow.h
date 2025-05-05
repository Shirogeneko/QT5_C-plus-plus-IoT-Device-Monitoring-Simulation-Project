#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtSql>
#include <QtNetwork>
#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>
#include "apiclient.h"
#include "dbdatabase.h"

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
    void DeviceUpdate();
    void CriticalWindow();
    void AddDatabase();
    void on_testButton1_pressed();
    void on_testButton2_pressed();
    void RandData();
    void ApiPost();

private:
    Ui::MainWindow *ui;
    DBDatabase db;
    ApiClient client;
    QTimer *apiTimer;
    QTimer *criticalWindowTimer;
    QMessageBox *messageBox;
    void SetLED(QLabel* Label,int color,int size);
};
#endif // MAINWINDOW_H
