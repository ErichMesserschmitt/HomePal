#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "DataClasses/component.h"
#include "DataClasses/room.h"

class RoomGroup;
class Component;
class ConnectionController;

struct JournalPage {
    JournalPage() {
    }
    JournalPage(QList<RoomGroup> r, QList<Component> c, QString info = "") {
        m_rooms = r;
        m_components = c;
        m_shortInfo = info;
    }
    QList<RoomGroup> m_rooms;
    QList<Component> m_components;
    QString m_shortInfo = "";
};

class RoomController : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QList<RoomGroup> rooms READ rooms NOTIFY roomsChanged)
    Q_PROPERTY(int selectedRoom READ selectedRoom WRITE setSelectedRoom NOTIFY selectedRoomChanged)
    Q_PROPERTY(QList<Component> pendingComponents READ pendingComponents NOTIFY pendingComponentsChanged)

public:
    explicit RoomController(ConnectionController* connController, QObject* parent = nullptr);

public:
    int selectedRoom() {return m_selectedRoom;}
    void setSelectedRoom(int roomIndex);

    Q_INVOKABLE void addRoom(QString name);
    Q_INVOKABLE void requestNewDevices();
    Q_INVOKABLE void selectComponent(QString customName, int index, int roomIndex);


    QList<RoomGroup> rooms() {return m_lastPage.m_rooms;}
    QList<Component> pendingComponents() {return m_pendingComponents;}

signals:
    void roomsChanged();
    void selectedRoomChanged();
    void pendingComponentsChanged();

public slots:
    void onJournalReceived(QJsonDocument& doc);
    void onFullJournalReceived(QJsonDocument& doc);
    void onComponentsListReceived(QJsonDocument& doc);

private:
    void testRooms();

    int m_selectedRoom = 0;

    JournalPage m_lastPage;
    QList<JournalPage> m_fullJournal;
    ConnectionController* m_connController;
    QList<Component> m_pendingComponents;

};
