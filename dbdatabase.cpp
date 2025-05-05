#include "dbdatabase.h"

DBDatabase::DBDatabase(QObject *parent) : QObject(parent)
{

}

bool DBDatabase::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE"); //設定資料庫類型
    db.setDatabaseName("D:\\QT_C++_Project\\IoT-Device-Monitoring-Simulation\\test.db"); //資料庫名稱
    if(db.open()) //檢查開啟資料庫
    {
        qDebug()<<"資料庫打開";
        return db.open();
    }
    else
    {
        qDebug()<<"資料庫打開失敗："<<db.lastError().text();
        return false;
    }
}

void DBDatabase::closeDatabase(){
   db.close();
}

/**
 * @brief MainWindow::addDatabase
 * @param name
 * @param temp
 * @param rh
 * @param state
 */
bool DBDatabase::addDatabase
(QString name, QString temp, QString rh, QString state, QString date_time)
{
    QSqlQuery query; //新增
    query.prepare("INSERT INTO QT5(NAME,TEMP,RH,STATE,DATE_TIME)"
                  "VALUES(:NAME, :TEMP, :RH, :STATE, :DATE_TIME)");
    query.bindValue(":NAME", name);
    query.bindValue(":TEMP", temp);
    query.bindValue(":RH", rh);
    query.bindValue(":STATE", state);
    query.bindValue(":DATE_TIME", date_time);
    if(query.exec())
    {
        qDebug()<<"新增成功";
        return true;
    }
    else
    {
        qDebug()<<"新增失敗："<<query.lastError().text();
        return false;
    }
}

/**
 * @brief MainWindow::selectDatabase
 * @param fieldStr
 */
bool DBDatabase::selectDatabase(QString fieldStr)
{
    QSqlQuery query("SELECT *, NAME FROM QT5"); //查詢
    int fieldNo = query.record().indexOf(fieldStr);
    if(query.isActive())
    {
        while (query.next())
        {
            QString str  = query.value(fieldNo).toString();
            qDebug() <<"資料內容：" << str;
        }
        return true;
    }
    else
    {
        qDebug()<<"查詢失敗："<<query.lastError().text();
        return false;
    }
}

/**
 * @brief MainWindow::updateDatabase
 * @param ID
 * @param name
 * @param temp
 * @param rh
 * @param state
 */
bool DBDatabase::updateDatabase
(int ID,QString name, QString temp, QString rh, QString state, QString date_time)
{
    QSqlQuery query; //修改
    query.prepare("UPDATE QT5 SET NAME=:NAME, TEMP=:TEMP, "
                  "RH=:RH, STATE=:STATE DATE_TIME=:DATE_TIME WHERE ID=:ID");
    query.bindValue(":ID", ID);
    query.bindValue(":NAME", name);
    query.bindValue(":TEMP", temp);
    query.bindValue(":RH", rh);
    query.bindValue(":STATE", state);
    query.bindValue(":DATE_TIME", date_time);
    if(query.exec())
    {
        qDebug()<<"修改成功";
        return true;
    }
    else
    {
        qDebug()<<"修改失敗："<<query.lastError().text();
        return false;
    }
}

/**
 * @brief MainWindow::delteDatabase
 * @param ID
 */
bool DBDatabase::delteDatabase(int ID)
{
    QSqlQuery query; //刪除
    query.prepare("DELETE FROM QT5 WHERE ID = :ID");
    query.bindValue(":ID", ID);
    if(query.exec())
    {
        qDebug()<<"刪除成功";
        return true;
    }
    else
    {
        qDebug()<<"刪除失敗："<<query.lastError().text();
        return false;
    }
}
