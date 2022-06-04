#pragma once

#include "Connection/connection.h"
#include "Connection/tcpserver.h"
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
class ServerTCP;

class ConnectionController : public QObject {
    Q_OBJECT
public:

public:
    explicit ConnectionController(QObject* parent = nullptr);

public:
    void startServer();
    void stopClient();
    void sendData(QJsonDocument& doc);
signals:
    void dataProcessed(QJsonDocument& doc, QWebSocket* socket = nullptr);
public slots:
    void onDataReceived(QJsonDocument doc, QWebSocket* socket);
private:
    void processData(QJsonDocument& doc, QWebSocket* socket = nullptr);
    void disconnectClient(QWebSocket* socket);

    void processInitialization(QJsonDocument& data, QWebSocket* socket);

    void addComponent(QJsonDocument& data);
    void addRoom(QJsonDocument& data);
    void editComponent(QJsonDocument& data);
    void editRoom(QJsonDocument& data);

    void sendJournal(QWebSocket* socket);
    void sendRooms(QWebSocket* socket);
    void sendComponents(QWebSocket* socket);


    IServer* m_client;
    ServerTCP* m_server;
    QVector<Component> m_components;
    QVector<RoomGroup> m_rooms;
    QString m_defaultAdress = QStringLiteral("127.0.0.1");
    int m_defaultPort = 1488;
};
