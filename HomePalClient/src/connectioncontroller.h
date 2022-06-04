#pragma once

#include "Connection/connection.h"
#include "Connection/tcpclient.h"
#include "DataClasses/component.h"
#include "DataClasses/room.h"
#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QTimer>
class RoomController;
class ClientTCP;

class ConnectionController : public QObject {
    Q_OBJECT
public:

public:
    explicit ConnectionController(QObject* parent = nullptr);

public:
    Q_INVOKABLE void startClient();
    Q_INVOKABLE void startClient(QString adress, int port = 1488);
    Q_INVOKABLE void stopClient();

    void requestComponent();
    void addComponent(Component& comp);
    void addRoom(RoomGroup& room);
    void editComponent(Component& comp);
    void editRoom(RoomGroup& room);

public slots:
    void onDataReceived();
public:
signals:
    void journalReceived(QJsonDocument& doc);
    void componentListReceived(QJsonDocument& doc);
private:
    void processData(QJsonDocument& doc);
    IClient* m_client;
    QString m_defaultAdress = QStringLiteral("127.0.0.1");
    int m_defaultPort = 1488;
};
