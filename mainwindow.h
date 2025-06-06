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
#include "warningwindow.h"

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
    void deviceUpdate();
    void criticalWindow();
    void addDatabase();
    void on_testButton2_pressed();
    void randData();
    void apiPost();
    void windowTime();

private:
    Ui::MainWindow *ui;
    DBDatabase db;
    ApiClient client;
    QTimer *apiTimer;
    QTimer *criticalWindowTimer;
    QTimer *windowTimer;
    WarningWindow *messageBox;
    QUrl url;
    void setLED(QLabel* Label,int color,int size);
};
#endif // MAINWINDOW_H
