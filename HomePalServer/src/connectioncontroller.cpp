#include "connectioncontroller.h"
#include "Connection/tcpserver.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QWebSocket>

ConnectionController::ConnectionController(QObject *parent) : QObject(parent)
{
    qDebug() << "ConnectionController::ConnectionController is initialized";

    startServer();

}

void ConnectionController::startServer()
{
    m_server = new ServerTCP(1488, true, this);
    connect(m_server, &IServer::receivedData, this, &ConnectionController::onDataReceived);
    connect(this, &ConnectionController::dataProcessed, m_server, &IServer::sendData);
}

void ConnectionController::onDataReceived(QJsonDocument doc, QWebSocket* socket)
{
    qDebug() << "ConnectionController::onDataReceived :: signal emmited";
    processData(doc, socket);
}

void ConnectionController::processData(QJsonDocument &doc, QWebSocket* socket)
{
    QJsonObject received = doc.object();
    ConnType dataType = static_cast<ConnType>(received.value("type").toInt());
    switch(dataType){
    case ConnType::Init:

    case ConnType::ComponentList:
        return;
    case ConnType::CreateComponent:
    case ConnType::CreateRoom:
    case ConnType::EditRoom:
    case ConnType::EditComponent:
        qDebug() << "ConnectionController::processData :: nothing to do with this type of data on client side" << dataType;
        return;
    case ConnType::Journal:
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

void ConnectionController::disconnectClient(QWebSocket* socket)
{
    m_server->disconnectClient(socket);
}

void ConnectionController::processInitialization(QJsonDocument &data, QWebSocket *socket)
{

}

void ConnectionController::addComponent(QJsonDocument& data)
{
}

void ConnectionController::addRoom(QJsonDocument& data)
{

}

void ConnectionController::editComponent(QJsonDocument& data)
{

}

void ConnectionController::editRoom(QJsonDocument& data)
{

}

void ConnectionController::sendJournal(QWebSocket* socket)
{

}

void ConnectionController::sendRooms(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::RoomList;
    QJsonArray roomArr;
    for(auto &room : m_rooms){
        QJsonObject roomData;
        roomData["index"] = room.index();
        roomData["name"] = room.name();
        roomArr.append(roomData);
    }
    objToSend["list"] = roomArr;
    QJsonDocument doc = QJsonDocument(objToSend);
    Q_EMIT dataProcessed(doc, socket);
}

void ConnectionController::sendComponents(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::ComponentList;
    QJsonArray componentArr;
    for(auto &component : m_components){
        QJsonObject componentsData;
        componentsData["index"] = component.index();
        componentsData["name"] = component.name();
        componentsData["roomIndex"] = component.roomIndex();
        componentsData["lowPoint"] = component.lowPoint();
        componentsData["highPoint"] = component.highPoint();
        componentsData["delta"] = component.delta();
        componentsData["type"] = component.type();
        QJsonArray infoArray;
        for(auto& info : component.info()){
            infoArray.append(info);
        }
        componentsData["info"] = infoArray;
        componentArr.append(componentsData);
    }
    objToSend["list"] = componentArr;
    QJsonDocument doc = QJsonDocument(objToSend);
    Q_EMIT dataProcessed(doc, socket);
}
