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

public:
    explicit RoomController(ConnectionController* connController, QObject* parent = nullptr);

public:
    int selectedRoom() {return m_selectedRoom;}
    void setSelectedRoom(int roomIndex);

    Q_INVOKABLE void addRoom(QString name);
    Q_INVOKABLE void requestNewDevices();


    QList<RoomGroup> rooms() {return m_lastPage.m_rooms;}

signals:
    void roomsChanged();
    void selectedRoomChanged();
public slots:
    void onJournalReceived(QJsonDocument& doc);
    void onFullJournalReceived(QJsonDocument& doc);

private:
    void testRooms();

    int m_selectedRoom = 0;

    JournalPage m_lastPage;
    QList<JournalPage> m_fullJournal;
    ConnectionController* m_connController;

};
