#pragma once

#include "Connection/connection.h"
#include "Connection/tcpserver.h"
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
private:
    void processData(QJsonDocument& doc);
    void disconnectClient();
    void addComponent();
    void addRoom();
    void editComponent();
    void editRoom();
    void sendJournal();


    IClient* m_client;
    EchoServer* m_server;
    QString m_defaultAdress = QStringLiteral("127.0.0.1");
    int m_defaultPort = 1488;
};
