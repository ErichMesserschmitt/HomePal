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

struct JournalPage {
    JournalPage() {
    }
    QList<RoomGroup*> m_rooms;
    QList<Component*> m_components;
    QString m_shortInfo = "";
};

class ProcessController : public QObject {
    Q_OBJECT
public:

public:
    explicit ProcessController(QObject* parent = nullptr);

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
    void sendLastPage(QWebSocket* socket);
    void sendComponents(QWebSocket* socket);
private slots:
    void updateJournal();
    void updateLastPage();

private:
    QList<JournalPage> m_fullJournal;
    JournalPage m_lastPage;
    QList<Component> m_pendingComponents;
    QList<Component> m_connectedComponents;
    QList<RoomGroup> m_rooms;

    IServer* m_server;
    QString m_defaultAdress = QStringLiteral("127.0.0.1");

    QTimer* m_lastPageUpdater;
    QTimer* m_journalUpdater;
    int m_defaultPort = 1488;
};
