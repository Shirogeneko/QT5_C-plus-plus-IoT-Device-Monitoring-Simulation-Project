#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.initDatabase();

    apiTimer = new QTimer(this);
    connect(apiTimer, SIGNAL(timeout()), this, SLOT(ApiPost()));
    connect(apiTimer, SIGNAL(timeout()), this, SLOT(DeviceUpdate()));
    connect(apiTimer, SIGNAL(timeout()), this, SLOT(AddDatabase()));
    //connect(apiTime, SIGNAL(timeout()), this, SLOT(randData()));
    apiTimer->start(5*1000);
    ApiPost();
    DeviceUpdate();

    criticalWindowTimer = new QTimer(this);
    connect(criticalWindowTimer, SIGNAL(timeout()), this, SLOT(CriticalWindow()));
    criticalWindowTimer->start(5*1000);
}

MainWindow::~MainWindow()
{
    apiTimer->stop();
    criticalWindowTimer->stop();
    db.closeDatabase();
    delete ui;
}

void MainWindow::DeviceUpdate()
{
    QList<QLabel *> uiLabelList = ui->centralwidget->findChildren<QLabel *>();
    QDateTime  time = QDateTime::currentDateTime();
    uiLabelList.at(0)->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    //QList<QLabel *> uiObjectList = ui->gridLayoutWidget->findChildren<QLabel *>();
    //更新UI資料
    QObjectList uiObjectList = ui->gridLayoutWidget->children();
    for (int i = 0; i < uiObjectList.size(); i++)
    {
        QString objectName = uiObjectList[i]->objectName();
        QString arrayID = objectName.at(objectName.size()-1);

        //qDebug()<<"objectName:"<< objectName;
        //qDebug()<<"arrayID:"<< arrayID;
        if(objectName.contains("deviceName", Qt::CaseSensitive))
        {
            qobject_cast<QLabel*>(uiObjectList[i])->setText(client.data.name.at(arrayID.toInt()-1));
        }
        else if(objectName.contains("deviceState", Qt::CaseSensitive))
        {
            qobject_cast<QLabel*>(uiObjectList[i])->setText(client.data.state.at(arrayID.toInt()-1));
        }
        else if(objectName.contains("LED", Qt::CaseSensitive))
        {
            int temp = client.data.temp.at(arrayID.toInt()-1).toInt();
            int rh = client.data.rh.at(arrayID.toInt()-1).toInt();
            if(client.data.temp.at(arrayID.toInt()-1) == ""||
               client.data.rh.at(arrayID.toInt()-1) == "")
            {
                SetLED(qobject_cast<QLabel*>(uiObjectList[i]),0,20);
            }
            else if(temp<=0 || temp >=50 || rh<=25 || rh >=100)
            {
                SetLED(qobject_cast<QLabel*>(uiObjectList[i]),1,20);
            }
            else
            {
                SetLED(qobject_cast<QLabel*>(uiObjectList[i]),2,20);
            }
        }
        else if(objectName.contains("deviceTemp", Qt::CaseSensitive))
        {
            qobject_cast<QLCDNumber*>(uiObjectList[i])->display(client.data.temp.at(arrayID.toInt()-1));
        }
        else if(objectName.contains("deviceRH", Qt::CaseSensitive))
        {
            qobject_cast<QLCDNumber*>(uiObjectList[i])->display(client.data.rh.at(arrayID.toInt()-1));
        }
    }
}

void MainWindow::AddDatabase()
{
    int arraySize = client.data.name.size();
    //寫資料到資料庫
    for(int i = 0; i < arraySize; i++)
    {
        if(client.data.temp[i] != ""||
           client.data.rh[i] != "")
        {
            db.addDatabase(client.data.name[i],
                           client.data.temp[i],
                           client.data.rh[i],
                           client.data.state[i],
                           client.data.date_time[i]);
        }
    }

}

//UI連線狀況設計
void MainWindow::SetLED(QLabel* Label,int color,int size)
{
    QString min_width = QString("min-width: %1px;").arg(size*2);
    QString min_height = QString("min-height: %1px;").arg(size);
    QString max_width = QString("max-width: %1px;").arg(size*2);
    QString max_height = QString("max-height: %1px;").arg(size);
    QString border_radius = QString("border-radius: %1px;").arg(size/2);
    QString border = QString("border:1px solid black;");
    QString background = QString("background-color:");

    switch (color)
    {

    case 0:
        Label->setText("未連線");
        background+= "rgb(190, 190, 190)";
        break;
    case 1:
        Label->setText("異常");
        background+= "rgb(255, 0, 0)";
        break;
    case 2:
        Label->setText("正常");
        background+= "rgb(0, 255, 0)";
        break;
    case 3:
        Label->setText("警示");
        background+= "rgb(255, 255, 0)";
        break;

    default:
        break;

    }
    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    Label->setStyleSheet(SheetStyle);
}

//隨機更新設備狀況
void MainWindow::RandData()
{
    int nameID = QRandomGenerator::global()->bounded(4);
    int temp = QRandomGenerator::global()->bounded(-10,100);
    int rh = QRandomGenerator::global()->bounded(0,100);

    QDateTime  time = QDateTime::currentDateTime();
    QJsonObject obj;

    obj.insert("name", "device" + QString::number(nameID));
    obj.insert("temp", QString::number(temp));
    obj.insert("rh", QString::number(rh));
    obj.insert("state", "test");
    obj.insert("date_time", time.toString("yyyy-MM-dd HH:mm:ss"));
    QByteArray byteArray = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    client.Put("http://127.0.0.1:5000/test/put",byteArray);
}

//警示視窗
void MainWindow::CriticalWindow()
{
    QObjectList cs = ui->gridLayoutWidget->children();
    QString message = "";
    for (int i = 0; i < cs.size(); i++)
    {
        QString objectName = cs[i]->objectName();
        QString arrayID = objectName.at(objectName.size()-1);

        //qDebug()<<"objectName:"<< objectName;
        //qDebug()<<"arrayID:"<< arrayID;
        if(objectName.contains("deviceName", Qt::CaseSensitive))
        {
            int temp = client.data.temp.at(arrayID.toInt()-1).toInt();
            int rh = client.data.rh.at(arrayID.toInt()-1).toInt();
            if(temp<=0 || temp >=50 || rh<=25 || rh >=100)
            {
                message.append(client.data.name.at(arrayID.toInt()-1).toUtf8() + "裝置異常\n");

            }
        }
    }
    messageBox = new QMessageBox(QMessageBox::Critical,
                                  "異常弹窗",
                                  message,
                                  QMessageBox::Ok);
    messageBox->setModal(false);
    messageBox->setAttribute(Qt::WA_DeleteOnClose);
    messageBox->show();
    //messageBox.exec();
}

void MainWindow::on_testButton1_pressed()
{

}

void MainWindow::on_testButton2_pressed()
{
    RandData();
    DeviceUpdate();
}

void MainWindow::ApiPost()
{
    QJsonObject obj;
    obj.insert("name", "all");
    client.Post("http://127.0.0.1:5000/test/post",
                QJsonDocument(obj).toJson(QJsonDocument::Compact));
}
