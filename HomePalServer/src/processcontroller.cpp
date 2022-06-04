#include "processcontroller.h"
#include "Connection/tcpserver.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QWebSocket>

ProcessController::ProcessController(QObject *parent) : QObject(parent)
{
    qDebug() << "ConnectionController::ConnectionController is initialized";

    startServer();

}

void ProcessController::startServer()
{
    m_server = new ServerTCP(1488, true, this);
    connect(m_server, &IServer::receivedData, this, &ProcessController::onDataReceived);
    connect(this, &ProcessController::dataProcessed, m_server, &IServer::sendData);
    m_lastPageUpdater = new QTimer(this);
    m_lastPageUpdater->setInterval(60000);
    m_journalUpdater = new QTimer();
    m_journalUpdater->setInterval(1800000);
    connect(m_lastPageUpdater, &QTimer::timeout, this, &ProcessController::updateLastPage);
    connect(m_journalUpdater, &QTimer::timeout, this, &ProcessController::updateJournal);
    updateLastPage();
    updateJournal();
}

void ProcessController::onDataReceived(QJsonDocument doc, QWebSocket* socket)
{
    qDebug() << "ConnectionController::onDataReceived :: signal emmited";
    processData(doc, socket);
}

void ProcessController::processData(QJsonDocument &doc, QWebSocket* socket)
{
    QJsonObject received = doc.object();
    ConnType dataType = static_cast<ConnType>(received.value("type").toInt());
    switch(dataType){
    case ConnType::Init:
        return;
    case ConnType::ComponentList:
        sendComponents(socket);
        return;
    case ConnType::CreateComponent:
        addComponent(doc);
        return;
    case ConnType::CreateRoom:
        addRoom(doc);
        return;
    case ConnType::EditRoom:
        editRoom(doc);
        return;
    case ConnType::EditComponent:
        editComponent(doc);
        return;
    case ConnType::Journal:
        sendJournal(socket);
        return;
    case ConnType::LastPage:
        sendLastPage(socket);
        return;
    case ConnType::Disconnect:
        qDebug() << "ConnectionController::processData :: client preparing for disconnect";
        if(socket){
            socket->disconnect(this);
        }
        return;

    default:
        return;

    }
}

void ProcessController::disconnectClient(QWebSocket* socket)
{
    m_server->disconnectClient(socket);
}

void ProcessController::processInitialization(QJsonDocument &data, QWebSocket *socket)
{

}

void ProcessController::addComponent(QJsonDocument& data)
{
    Component comp = Component::fromDoc(data);
    for(auto& c : m_pendingComponents){
        if(c.index() == comp.index()){
            auto copy = c;
            c = comp;
            c.setType(copy.type());
            c.setLowPoint(copy.lowPoint());
            c.setHighPoint(copy.highPoint());
            c.setDelta(copy.delta());

            //updateJournal();
        }
    }
}

void ProcessController::addRoom(QJsonDocument& data)
{
    RoomGroup room = RoomGroup::fromDoc(data);
    m_rooms.append(room);
}

void ProcessController::editComponent(QJsonDocument& data)
{
    Component comp = Component::fromDoc(data);
    for(auto& c : m_connectedComponents){
        if(c.index() == comp.index()){
            auto copy = c;
            c = comp;
            c.setType(copy.type());
            c.setLowPoint(copy.lowPoint());
            c.setHighPoint(copy.highPoint());
            c.setDelta(copy.delta());
            //updateJournal();
        }
    }
}

void ProcessController::editRoom(QJsonDocument& data)
{
    RoomGroup room = RoomGroup::fromDoc(data);
    for(auto& r : m_rooms) {
        if(r.index() == room.index()){
            r.name() = room.name();
        }
    }
    //updateJournal();
}

void ProcessController::sendJournal(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::Journal;
    QJsonArray pageArray;

    for(auto& page : m_fullJournal){
        QJsonObject pageObj;

        QJsonArray roomArr;
        for(auto &room : page.m_rooms){
            roomArr.append(RoomGroup::toDoc(*room).object());
        }
        QJsonArray compArr;
        for(auto &comp : page.m_components){
            roomArr.append(Component::toDoc(*comp).object());
        }
        QJsonArray infoArr;
        for(auto &inf : page.m_shortInfo){
            infoArr.append(QJsonValue(inf));
        }
        pageObj["rooms"] = roomArr;
        pageObj["components"] = compArr;
        pageObj["info"] = infoArr;
        pageArray.append(pageObj);
    }
    objToSend["list"] = pageArray;
    QJsonDocument doc = QJsonDocument(objToSend);
    Q_EMIT dataProcessed(doc, socket);
}

void ProcessController::sendLastPage(QWebSocket *socket)
{
    QJsonObject pageObj;
    pageObj["type"] = ConnType::LastPage;
    QJsonArray roomArr;
    for(auto &room : m_lastPage.m_rooms){
        roomArr.append(RoomGroup::toDoc(*room).object());
    }
    QJsonArray compArr;
    for(auto &comp : m_lastPage.m_components){
        roomArr.append(Component::toDoc(*comp).object());
    }
    QJsonArray infoArr;
    for(auto &inf : m_lastPage.m_shortInfo){
        infoArr.append(QJsonValue(inf));
    }
    pageObj["rooms"] = roomArr;
    pageObj["components"] = compArr;
    pageObj["info"] = infoArr;
    QJsonDocument doc = QJsonDocument(pageObj);
    Q_EMIT dataProcessed(doc, socket);
}



void ProcessController::sendComponents(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::ComponentList;
    QJsonArray componentArr;
    for(auto &component : m_pendingComponents){
        componentArr.append(Component::toDoc(component).object());
    }
    objToSend["list"] = componentArr;
    QJsonDocument doc = QJsonDocument(objToSend);
    Q_EMIT dataProcessed(doc, socket);
}

void ProcessController::updateJournal()
{
    JournalPage page;
    for(auto& c:m_connectedComponents){
        page.m_components.emplaceBack(c);
    }
    for(auto& c:m_rooms){
        page.m_rooms.emplaceBack(c);
    }
    QString info = "Time " + QDateTime::currentDateTime().toString(Qt::DateFormat::TextDate) + ". Generated at simulation";
    page.m_shortInfo = info;

    m_fullJournal.append(page);
}

void ProcessController::updateLastPage()
{
    JournalPage page;
    for(auto& c:m_connectedComponents){
        page.m_components.emplaceBack(c);
    }
    for(auto& c:m_rooms){
        page.m_rooms.emplaceBack(c);
    }
    QString info = "Time " + QDateTime::currentDateTime().toString(Qt::DateFormat::TextDate) + ". Generated at simulation";
    page.m_shortInfo = info;
    m_lastPage = page;
}
