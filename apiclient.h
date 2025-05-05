#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QtNetwork>

class ApiClient : public QObject
{
    Q_OBJECT
    struct ReplyData {
        QStringList name;
        QStringList temp;
        QStringList rh;
        QStringList state;
        QStringList date_time;
    };

public:
    explicit ApiClient(QObject *parent = nullptr);

    void Get(const QString &url);
    void Get(const QUrl &url);
    bool Post(const QString &url, const QByteArray& jsonObj);
    void Post(const QUrl &url, const QByteArray& jsonObj);
    bool Put(const QString &url, const QByteArray& jsonObj);
    void Put(const QUrl &url, const QByteArray& jsonObj);
    void Delete(const QString &url);
    void Delete(const QUrl &url);
    ReplyData data;



private slots:


private:

    QNetworkAccessManager *networkManager;
    QNetworkRequest request;
    QJsonParseError json_error;
    QJsonDocument doucment;

};

#endif // APICLIENT_H
