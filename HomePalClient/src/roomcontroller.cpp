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
   // testRooms();
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
    Component* comp;
    for(auto c : m_pendingComponents){
        if(c->index() == index){
            comp = new Component(c);
            break;
        }
    }
    if(comp->index() != index){
        return;
    }
    if(!customName.isEmpty()){
        comp->setName(customName);
    }
    if(roomIndex > 0) {
        comp->setRoomIndex(roomIndex);
    }
    m_connController->addComponent(*comp);
}



int RoomController::roomComponentsCount()
{
    if(m_selectedRoom == 0){
        return m_lastPage.m_components.length();
    }
    int c = 0;
    for(auto& cmp : m_lastPage.m_components){
        if(cmp->roomIndex() == m_selectedRoom){
            ++c;
        }
    }
    return c;
}

void RoomController::editRoom(int index)
{
    RoomGroup* room;
    for(auto& r : m_lastPage.m_rooms){
        if(r->index() == index){
            room = new RoomGroup(*r);
        }
    }
    m_editableRoom = new RoomGroup(*room);
    Q_EMIT editableRoomChanged();
}

void RoomController::editComponent(int index)
{
    Component* component;
    for(auto& r : m_lastPage.m_components){
        if(r->index() == index){
            component = new Component(*r);
            break;
        }
    }
    m_editableComponent = new Component(*component);
    Q_EMIT editableComponentChanged();
}

void RoomController::saveEditRoom()
{
    if(m_editableRoom != nullptr){
        m_connController->editRoom(*m_editableRoom);
    }
}

void RoomController::saveEditComponent()
{
    if(m_editableComponent != nullptr){
        m_connController->editComponent(*m_editableComponent);
    }
}

void RoomController::removeRoom(int index)
{
    RoomGroup* room;
    for(auto& r : m_lastPage.m_rooms){
        if(r->index() == index){
            room = new RoomGroup(*r);
        }
    }
    m_connController->deleteRoom(*room);
}

void RoomController::removeComponent(int index)
{
    Component* component;
    for(auto& r : m_lastPage.m_components){
        if(r->index() == index){
            component = new Component(r);
        }
    }
    m_connController->deleteComponent(*component);
}


void RoomController::onJournalReceived(QJsonDocument &doc)
{
    qDebug() << "RoomController::onJournalReceived :: received last journal page";
    JournalPage p;
    QJsonObject d = doc.object();
    QJsonArray roomArr = d.value("rooms").toArray();
    QJsonArray compArr = d.value("components").toArray();
    qDeleteAll(m_lastPage.m_rooms);
    m_lastPage.m_rooms.clear();
    qDeleteAll(m_lastPage.m_components);
    m_lastPage.m_components.clear();
    for(auto r : roomArr) {
        QJsonDocument room = QJsonDocument(r.toObject());
        m_lastPage.m_rooms.push_back(new RoomGroup(RoomGroup::fromDoc(room)));
    }
    for(auto c : compArr) {
        QJsonDocument room = QJsonDocument(c.toObject());
        m_lastPage.m_components.push_back(new Component(Component::fromDoc(room)));
    }
    m_lastPage.m_shortInfo = d.value("info").toString();
    Q_EMIT lastPageChanged();
}

void RoomController::onFullJournalReceived(QJsonDocument &doc)
{
    qDebug() << "RoomController::onFullJournalReceived :: received full journal";
    JournalPage p;
    QJsonObject d = doc.object();
    QJsonArray pageArray = d.value("list").toArray();
    m_fullJournal.clear();
    for(auto page : pageArray){
        QJsonArray roomArr = page.toObject().value("rooms").toArray();
        QJsonArray compArr = page.toObject().value("components").toArray();
        JournalPage currentPage;
        for(auto r : roomArr) {
            QJsonDocument room = QJsonDocument(r.toObject());
            currentPage.m_rooms.push_back(new RoomGroup(RoomGroup::fromDoc(room)));
        }
        for(auto c : compArr) {
            QJsonDocument room = QJsonDocument(c.toObject());
            currentPage.m_components.push_back(new Component(Component::fromDoc(room)));
        }
        currentPage.m_shortInfo = page.toObject().value("info").toString();
        m_fullJournal.append(currentPage);
    }
    qDebug() << "RoomController::onFullJournalReceived :: received" << m_fullJournal.size() << "pages";
}

void RoomController::onComponentsListReceived(QJsonDocument &doc)
{
    QJsonObject d = doc.object();
    QJsonArray compArray = d.value("list").toArray();
    qDeleteAll(m_pendingComponents);
    m_pendingComponents.clear();
    for(auto comp : compArray){
        QJsonDocument tdoc(comp.toObject());
        m_pendingComponents.push_back(new Component(Component::fromDoc(tdoc)));
    }
    Q_EMIT pendingComponentsChanged();
}

void RoomController::testRooms()
{
    for(int i =0; i<2; ++i){
        RoomGroup room;
        room.setIndex(i);
        QString name = i == 0 ? "Home" : "Room N" + QString::number(i);
        room.setName(name);
        m_lastPage.m_rooms.push_back(new RoomGroup(room));
    }
    for(int i =0; i<8; ++i){
        Component c;
        QString name = "Component " + QString::number(i + 1);
        c.setName(name);
        c.setIndex(i);
        c.setRoomIndex((i%2) + 1);
        c.setDelta(0.1);
        c.setLowPoint(-1.0);
        c.setHighPoint(1.0);
        QList<QString> infoList;
        for(int k=0; k<5; ++k){
            infoList.append("test info " + QString::number(k+1));
        }
        c.setInfo(infoList);
        QDateTime enableDate(QDate::currentDate(), QTime(1, 22, 0, 0));
        QDateTime disableDate(QDate::currentDate(), QTime(5, 22, 0, 0));

        c.setEnableAt({enableDate});
        c.setDisableAt({disableDate});
        c.setType(i%2 ? ComponentType::Slider : ComponentType::Switcher);
        c.setIsAuto(i%2);
        c.setEnabled(true);
        m_lastPage.m_components.push_back(new Component(c));
    }
    Q_EMIT lastPageChanged();

}




