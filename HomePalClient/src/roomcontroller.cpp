#include "roomcontroller.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>

#include "DataClasses/room.h"
#include "connectioncontroller.h"

RoomController::RoomController(ConnectionController *connController, QObject *parent) :
    QObject(parent),
    m_connController(connController)
{

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
    RoomGroup r;
    r.setName(name);
    m_connController->addRoom(r);
}

void RoomController::requestNewDevices()
{
    m_connController->requestComponent();
}

void RoomController::selectComponent(QString customName, int index, int roomIndex)
{
    Component comp;
    for(auto c : m_pendingComponents){
        if(c.index() == index){
            comp = c;
            break;
        }
    }
    if(comp.index() != index){
        return;
    }
    if(!customName.isEmpty()){
        comp.setName(customName);
    }
    if(roomIndex > 0) {
        comp.setRoomIndex(roomIndex);
    }
    m_connController->addComponent(comp);
}

void RoomController::onJournalReceived(QJsonDocument &doc)
{
    qDebug() << "RoomController::onJournalReceived :: received last journal page";
    JournalPage p;
    QJsonObject d = doc.object();
    QJsonArray roomArr = d.value("rooms").toArray();
    QJsonArray compArr = d.value("components").toArray();
    m_lastPage.m_rooms.clear();
    m_lastPage.m_components.clear();
    for(auto r : roomArr) {
        QJsonDocument room = QJsonDocument(r.toObject());
        m_lastPage.m_rooms.append(RoomGroup::fromDoc(room));
    }
    for(auto c : compArr) {
        QJsonDocument room = QJsonDocument(c.toObject());
        m_lastPage.m_components.append(Component::fromDoc(room));
    }
    m_lastPage.m_shortInfo = d.value("info").toString();
}

void RoomController::onFullJournalReceived(QJsonDocument &doc)
{
    qDebug() << "RoomController::onFullJournalReceived :: received full journal";
    JournalPage p;
    QJsonObject d = doc.object();
    QJsonArray pageArray = d.value("pages").toArray();
    m_fullJournal.clear();
    for(auto page : pageArray){
        QJsonArray roomArr = page.toObject().value("rooms").toArray();
        QJsonArray compArr = page.toObject().value("components").toArray();
        JournalPage currentPage;
        for(auto r : roomArr) {
            QJsonDocument room = QJsonDocument(r.toObject());
            currentPage.m_rooms.append(RoomGroup::fromDoc(room));
        }
        for(auto c : compArr) {
            QJsonDocument room = QJsonDocument(c.toObject());
            currentPage.m_components.append(Component::fromDoc(room));
        }
        currentPage.m_shortInfo = page.toObject().value("info").toString();
        m_fullJournal.append(currentPage);
    }
    qDebug() << "RoomController::onFullJournalReceived :: received" << m_fullJournal.size() << "pages";
}

void RoomController::onComponentsListReceived(QJsonDocument &doc)
{
    QJsonObject d = doc.object();
    QJsonArray compArray = d.value("components").toArray();
    m_pendingComponents.clear();
    for(auto comp : compArray){
        QJsonDocument tdoc(comp.toObject());
        m_pendingComponents.append(Component::fromDoc(tdoc));
    }
    Q_EMIT pendingComponentsChanged();
}

void RoomController::testRooms()
{
    for(int i =0; i<2; ++i){
        RoomGroup room;
        room.setIndex(i + 1);
        QString name = "Room N" + QString::number(i + 1);
        room.setName(name);
        m_lastPage.m_rooms.append(new RoomGroup(this));
    }
    Q_EMIT roomsChanged();
}




