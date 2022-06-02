#include "roomcontroller.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>

#include "DataClasses/room.h"

RoomController::RoomController(QObject *parent) : QObject(parent)
{
    testRooms();
}

void RoomController::setSelectedRoom(int roomIndex)
{
    if(roomIndex != m_selectedRoom){
        m_selectedRoom = roomIndex;
        Q_EMIT selectedRoomChanged();
    }
}

void RoomController::addRoom(QString name)
{
    Room room;
    QString l_name = name + " " + QString::number(m_rooms.length());
    room.setIndex(m_rooms.length());
    m_rooms.append(&room);
    Q_EMIT roomsChanged();
}

void RoomController::testRooms()
{
    for(int i =0; i<2; ++i){
        Room room;
        room.setIndex(i + 1);
        QString name = "Room N" + QString::number(i + 1);
        room.setName(name);
        m_rooms.append(new Room(this));
    }
    Q_EMIT roomsChanged();
}




