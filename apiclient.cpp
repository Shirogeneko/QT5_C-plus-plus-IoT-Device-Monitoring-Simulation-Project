#include "apiclient.h"

ApiClient::ApiClient(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    for(int i=0;i<5;i++)
    {
        data.name << "";
        data.temp << "";
        data.rh << "";
        data.state << "";
        data.date_time << "";
    }
}

void ApiClient::Get(const QString &url)
{
    request = QNetworkRequest(QUrl(url));
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));
    //get

    QNetworkReply* reply = networkManager->get(request);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
    }
    auto replyStr = reply->readAll();
    reply->deleteLater();

    qDebug()<<"message:"<<replyStr ;
}

void ApiClient::Get(const QUrl &url)
{
    request = QNetworkRequest(url);
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));
    //get

    QNetworkReply* reply = networkManager->get(request);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
    }
    auto replyStr = reply->readAll();
    reply->deleteLater();

    qDebug()<<"message:"<<replyStr ;
}

bool ApiClient::Post(const QString &url, const QByteArray &jsonObj)
{
    request = QNetworkRequest(QUrl(url));
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));
    //post

    QNetworkReply* reply = networkManager->post(request, jsonObj);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();

        data.name.clear();
        data.temp.clear();
        data.rh.clear();
        data.state.clear();
        data.date_time.clear();
        for(int i=0;i<5;i++)
        {
            data.name << "";
            data.temp << "";
            data.rh << "";
            data.state << "";
            data.date_time << "";
        }
        return false;
    }
    auto jsonStr = reply->readAll();
    reply->deleteLater();
    if (jsonStr.size() == 0)
        return false;
    doucment = QJsonDocument::fromJson(jsonStr, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) { //單一對象（Object）
            const QJsonObject obj = doucment.object();

            //qDebug()<<"QJsonObject:"<<obj ;
            if (obj.contains("device"))
            {
                QJsonValue value = obj.value("device");

                data.name.clear();
                data.temp.clear();
                data.rh.clear();
                data.state.clear();
                data.date_time.clear();
                //qDebug()<<"value:"<<value ;
                if(value.isObject())
                {
                    const QJsonObject obj = value.toObject();
                    if (obj.contains("name")) {
                        data.name << obj.value("name").toString();
                    }

                    if (obj.contains("temp")) {
                        data.temp << obj.value("temp").toString();
                    }

                    if (obj.contains("rh")) {
                        data.rh << obj.value("rh").toString();
                    }

                    if (obj.contains("state")) {
                        data.state << obj.value("state").toString();
                    }

                    if (obj.contains("date_time")) {
                        data.date_time << obj.value("date_time").toString();
                    }
                    qDebug() << "name：" << data.name
                                << "temp：" << data.temp
                                << "rh：" << data.rh
                                << "state：" << data.state
                                << "date_time：" << data.date_time;
                }
                else //數組（Array）
                {
                    const QJsonArray  jsonArr = value.toArray();
                    qDebug() << "多筆資料："<<jsonArr.count();
                    for(int i=0;i<jsonArr.count();i++)
                    {
                        const QJsonObject obj = jsonArr.at(i).toObject();

                        if (obj.contains("name")) {
                            data.name << obj.value("name").toString();
                        }

                        if (obj.contains("temp")) {
                            data.temp << obj.value("temp").toString();
                        }

                        if (obj.contains("rh")) {
                            data.rh << obj.value("rh").toString();
                        }

                        if (obj.contains("state")) {
                            data.state << obj.value("state").toString();
                        }

                        if (obj.contains("date_time")) {
                            data.date_time << obj.value("date_time").toString();
                        }

                        qDebug() << "name：" << data.name[i]
                                    << "temp：" << data.temp[i]
                                    << "rh：" << data.rh[i]
                                    << "state：" << data.state[i]
                                    << "date_time：" << data.date_time[i];
                    }
                }
                return true;
            }
        }
        else //數組（Array）
        {
            /*
            const QJsonArray  jsonArr = doucment.array();
            qDebug() << "處理："<<jsonArr.count();
            for(int i=0;i<jsonArr.count();i++)
            {
                const QJsonObject obj = jsonArr.at(i).toObject();

                if (obj.contains("name")) {
                    data.name << obj.value("name").toString();
                }

                if (obj.contains("temp")) {
                    data.temp << obj.value("temp").toString();
                }

                if (obj.contains("rh")) {
                    data.rh << obj.value("rh").toString();
                }

                if (obj.contains("state")) {
                    data.state << obj.value("state").toString();
                }

                if (obj.contains("date_time")) {
                    data.date_time << obj.value("date_time").toString();
                }

                qDebug() << "name：" << data.name[i]
                            << "temp：" << data.temp[i]
                            << "rh：" << data.rh[i]
                            << "state：" << data.state[i]
                            << "date_time：" << data.date_time[i];
            }
            return true;
            */
        }
    }
    else
    {
        qDebug() << "Json解析失敗：";
    }
    return false;
}

bool ApiClient::Post(const QUrl &url, const QByteArray &jsonObj)
{
    request = QNetworkRequest(url);
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));
    //post

    QNetworkReply* reply = networkManager->post(request, jsonObj);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();

        data.name.clear();
        data.temp.clear();
        data.rh.clear();
        data.state.clear();
        data.date_time.clear();
        for(int i=0;i<5;i++)
        {
            data.name << "";
            data.temp << "";
            data.rh << "";
            data.state << "";
            data.date_time << "";
        }
        return false;
    }
    auto jsonStr = reply->readAll();
    reply->deleteLater();
    if (jsonStr.size() == 0)
        return false;
    doucment = QJsonDocument::fromJson(jsonStr, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) { //單一對象（Object）
            const QJsonObject obj = doucment.object();

            //qDebug()<<"QJsonObject:"<<obj ;
            if (obj.contains("device"))
            {
                QJsonValue value = obj.value("device");

                data.name.clear();
                data.temp.clear();
                data.rh.clear();
                data.state.clear();
                data.date_time.clear();
                //qDebug()<<"value:"<<value ;
                if(value.isObject())
                {
                    const QJsonObject obj = value.toObject();
                    if (obj.contains("name")) {
                        data.name << obj.value("name").toString();
                    }

                    if (obj.contains("temp")) {
                        data.temp << obj.value("temp").toString();
                    }

                    if (obj.contains("rh")) {
                        data.rh << obj.value("rh").toString();
                    }

                    if (obj.contains("state")) {
                        data.state << obj.value("state").toString();
                    }

                    if (obj.contains("date_time")) {
                        data.date_time << obj.value("date_time").toString();
                    }
                    qDebug() << "name：" << data.name
                                << "temp：" << data.temp
                                << "rh：" << data.rh
                                << "state：" << data.state
                                << "date_time：" << data.date_time;
                }
                else //數組（Array）
                {
                    const QJsonArray  jsonArr = value.toArray();
                    qDebug() << "多筆資料："<<jsonArr.count();
                    for(int i=0;i<jsonArr.count();i++)
                    {
                        const QJsonObject obj = jsonArr.at(i).toObject();

                        if (obj.contains("name")) {
                            data.name << obj.value("name").toString();
                        }

                        if (obj.contains("temp")) {
                            data.temp << obj.value("temp").toString();
                        }

                        if (obj.contains("rh")) {
                            data.rh << obj.value("rh").toString();
                        }

                        if (obj.contains("state")) {
                            data.state << obj.value("state").toString();
                        }

                        if (obj.contains("date_time")) {
                            data.date_time << obj.value("date_time").toString();
                        }

                        qDebug() << "name：" << data.name[i]
                                    << "temp：" << data.temp[i]
                                    << "rh：" << data.rh[i]
                                    << "state：" << data.state[i]
                                    << "date_time：" << data.date_time[i];
                    }
                }
                return true;
            }
        }
        else
        {
            qDebug() << "Json解析失敗：";
            return false;
        }
    }
    else
    {
        qDebug() << "Json解析失敗：";
    }
    return false;
}

bool ApiClient::Put(const QString &url, const QByteArray &jsonObj)
{
    request = QNetworkRequest(QUrl(url));
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));
    //put
    //networkManager->put(request,jsonObj);

    QNetworkReply* reply = networkManager->put(request, jsonObj);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
        return false;
    }
    auto jsonStr = reply->readAll();
    reply->deleteLater();
    if (jsonStr.size() == 0)
        return false;
    doucment = QJsonDocument::fromJson(jsonStr, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) {
            const QJsonObject obj = doucment.object();

            if (obj.contains("name")) {
                data.name << obj.value("name").toString();
            }

            if (obj.contains("temp")) {
                data.temp << obj.value("temp").toString();
            }

            if (obj.contains("rh")) {
                data.rh << obj.value("rh").toString();
            }

            if (obj.contains("state")) {
                data.state << obj.value("state").toString();
            }

            if (obj.contains("date_time")) {
                data.date_time << obj.value("date_time").toString();
            }

            qDebug() << "name：" << data.name
                        << "temp：" << data.temp
                        << "rh：" << data.rh
                        << "state：" << data.state
                        << "date_time：" << data.date_time;
            return true;
        }
        else
        {
            const QJsonArray  jsonArr = doucment.array();
            for(int i=0;i<jsonArr.count();i++)
            {
                const QJsonObject obj = jsonArr.at(i).toObject();

                if (obj.contains("name")) {
                    data.name << obj.value("name").toString();
                }

                if (obj.contains("temp")) {
                    data.temp << obj.value("temp").toString();
                }

                if (obj.contains("rh")) {
                    data.rh << obj.value("rh").toString();
                }

                if (obj.contains("state")) {
                    data.state << obj.value("state").toString();
                }

                if (obj.contains("date_time")) {
                    data.date_time << obj.value("date_time").toString();
                }

                qDebug() << "name：" << data.name
                            << "temp：" << data.temp
                            << "rh：" << data.rh
                            << "state：" << data.state
                            << "date_time：" << data.date_time;
            }
            return true;
        }
    }
    else
    {
        qDebug() << "Json解析失敗：";
    }
    return false;
}

bool ApiClient::Put(const QUrl &url, const QByteArray &jsonObj)
{
    request = QNetworkRequest(url);
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));

    QNetworkReply* reply = networkManager->put(request, jsonObj);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
        return false;
    }
    auto jsonStr = reply->readAll();
    reply->deleteLater();
    if (jsonStr.size() == 0)
        return false;
    doucment = QJsonDocument::fromJson(jsonStr, &json_error);
    if (json_error.error == QJsonParseError::NoError) {
        if (doucment.isObject()) {
            const QJsonObject obj = doucment.object();

            if (obj.contains("name")) {
                data.name << obj.value("name").toString();
            }

            if (obj.contains("temp")) {
                data.temp << obj.value("temp").toString();
            }

            if (obj.contains("rh")) {
                data.rh << obj.value("rh").toString();
            }

            if (obj.contains("state")) {
                data.state << obj.value("state").toString();
            }

            if (obj.contains("date_time")) {
                data.date_time << obj.value("date_time").toString();
            }

            qDebug() << "name：" << data.name
                        << "temp：" << data.temp
                        << "rh：" << data.rh
                        << "state：" << data.state
                        << "date_time：" << data.date_time;
            return true;
        }
        else
        {
            const QJsonArray  jsonArr = doucment.array();
            for(int i=0;i<jsonArr.count();i++)
            {
                const QJsonObject obj = jsonArr.at(i).toObject();

                if (obj.contains("name")) {
                    data.name << obj.value("name").toString();
                }

                if (obj.contains("temp")) {
                    data.temp << obj.value("temp").toString();
                }

                if (obj.contains("rh")) {
                    data.rh << obj.value("rh").toString();
                }

                if (obj.contains("state")) {
                    data.state << obj.value("state").toString();
                }

                if (obj.contains("date_time")) {
                    data.date_time << obj.value("date_time").toString();
                }

                qDebug() << "name：" << data.name
                            << "temp：" << data.temp
                            << "rh：" << data.rh
                            << "state：" << data.state
                            << "date_time：" << data.date_time;
            }
            return true;
        }
    }
    else
    {
        qDebug() << "Json解析失敗：";
    }
    return false;
}

void ApiClient::Delete(const QString &url)
{
    request = QNetworkRequest(url);
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));

    QNetworkReply* reply = networkManager->deleteResource(request);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
    }
    auto replyStr = reply->readAll();
    reply->deleteLater();

    qDebug()<<"message:"<<replyStr ;
}

void ApiClient::Delete(const QUrl &url)
{
    request = QNetworkRequest(url);
    //QNetworkRequest解析的已知HTTP 類型
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, QVariant("application/json"));

    QNetworkReply* reply = networkManager->deleteResource(request);
    QEventLoop eloop;
    QObject::connect(reply, &QNetworkReply::finished, &eloop, &QEventLoop::quit);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eloop, &QEventLoop::quit);
    eloop.exec();

    if(reply->error() != QNetworkReply::NoError)
    {
        auto errorString  = reply->errorString();
        qDebug()<<"Error:"<<errorString ;
        reply->deleteLater();
    }
    auto replyStr = reply->readAll();
    reply->deleteLater();

    qDebug()<<"message:"<<replyStr ;
}
