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
class EchoServer;

class ConnectionController : public QObject {
    Q_OBJECT
public:

public:
    explicit ConnectionController(QObject* parent = nullptr);

public:
    void startClient();
    void stopClient();
    void sendElement(QJsonDocument& doc);
public slots:
    void onDataReceived();
public:
signals:
    void journalReceived(QJsonDocument& doc);

private:
    void processData(QJsonDocument& doc);
    void addComponent(Component& comp);
    void addRoom(Room& room);
    void editComponent(Component& comp);
    void editRoom(Room& room);


    IClient* m_client;
    EchoServer* m_server;
    QString m_defaultAdress = QStringLiteral("127.0.0.1");
    int m_defaultPort = 1488;
};
