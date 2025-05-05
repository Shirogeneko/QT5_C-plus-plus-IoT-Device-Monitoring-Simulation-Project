#ifndef DBDATABASE_H
#define DBDATABASE_H

#include <QObject>
#include <QtSql>

class DBDatabase : public QObject
{
    Q_OBJECT
public:
    explicit DBDatabase(QObject *parent = nullptr);
    bool initDatabase();
    void closeDatabase();
    bool addDatabase(QString name, QString temp, QString rh, QString state, QString date_time);
    bool selectDatabase(QString fieldStr);
    bool updateDatabase(int ID,QString name, QString temp, QString rh, QString state, QString date_time);
    bool delteDatabase(int ID);


private:
    QSqlDatabase db;
signals:

};

#endif // DBDATABASE_H
