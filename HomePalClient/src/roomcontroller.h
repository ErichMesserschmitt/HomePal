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
    QList<RoomGroup*> m_rooms;
    QList<Component*> m_components;
    QString m_shortInfo = "";
};

class RoomController : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QList<RoomGroup*> rooms READ rooms NOTIFY lastPageChanged)
    Q_PROPERTY(QList<Component*> components READ components NOTIFY lastPageChanged)
    Q_PROPERTY(int selectedRoom READ selectedRoom WRITE setSelectedRoom NOTIFY selectedRoomChanged)
    Q_PROPERTY(QList<Component*> pendingComponents READ pendingComponents NOTIFY pendingComponentsChanged)
    Q_PROPERTY(int roomComponentsCount READ roomComponentsCount NOTIFY selectedRoomChanged)
    Q_PROPERTY(RoomGroup* editableRoom READ editableRoom NOTIFY editableRoomChanged)
    Q_PROPERTY(Component* editableComponent READ editableComponent NOTIFY editableComponentChanged)

public:
    explicit RoomController(ConnectionController* connController, QObject* parent = nullptr);

public:
    int selectedRoom() {return m_selectedRoom;}
    void setSelectedRoom(int roomIndex);

    Q_INVOKABLE void addRoom(QString name);
    Q_INVOKABLE void requestNewDevices();
    Q_INVOKABLE void selectComponent(QString customName, int index, int roomIndex);
    int roomComponentsCount();

    Q_INVOKABLE void editRoom(int index);
    Q_INVOKABLE void editComponent(int index);
    Q_INVOKABLE void saveEditRoom();
    Q_INVOKABLE void saveEditComponent();

    Q_INVOKABLE void removeRoom(int index);
    Q_INVOKABLE void removeComponent(int index);

    QList<RoomGroup*> rooms() {
        return m_lastPage.m_rooms;
    }
    QList<Component*> components() {
        return m_lastPage.m_components;
    }

    QList<Component*> pendingComponents() {return m_pendingComponents;}

    Component* editableComponent() {return m_editableComponent; }
    RoomGroup* editableRoom() {return m_editableRoom;}

signals:
    void selectedRoomChanged();
    void pendingComponentsChanged();
    void lastPageChanged();
    void editableRoomChanged();
    void editableComponentChanged();
public slots:
    void onJournalReceived(QJsonDocument& doc);
    void onFullJournalReceived(QJsonDocument& doc);
    void onComponentsListReceived(QJsonDocument& doc);

private:
    int m_selectedRoom = 0;

    RoomGroup* m_editableRoom;
    Component* m_editableComponent = nullptr;

    JournalPage m_lastPage;
    QList<JournalPage> m_fullJournal;
    ConnectionController* m_connController;
    QList<Component*> m_pendingComponents;

};
