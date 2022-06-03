#include "connectioncontroller.h"
#include "Connection/tcpclient.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

ConnectionController::ConnectionController(QObject *parent) : QObject(parent)
{
    qDebug() << "ConnectionController::ConnectionController is initialized";

    startClient();

}

void ConnectionController::startClient()
{
    m_client = new ClientTCP(QStringLiteral("ws://") + m_defaultAdress + ":" + QString::number(m_defaultPort));
    connect(m_client, &IClient::receivedDataChanged, this, &ConnectionController::onDataReceived);
}

void ConnectionController::onDataReceived()
{
    qDebug() << "ConnectionController::onDataReceived :: signal emmited";
    QJsonDocument receivedDoc = m_client->receiveData();
}

void ConnectionController::processData(QJsonDocument &doc)
{
    QJsonObject received = doc.object();
    ConnType dataType = static_cast<ConnType>(received.value("Type").toInt());
    switch(dataType){
    case ConnType::Init:

    case ConnType::CreateComponent:
    case ConnType::CreateRoom:
    case ConnType::EditRoom:
    case ConnType::EditComponent:
        qDebug() << "ConnectionController::processData :: nothing to do with this type on client side" << dataType;
        return;
    case ConnType::Journal:
        journalReceived(doc);
        return;
    case ConnType::Disconnect:
        return;

    default:
        return;
    }
}

void ConnectionController::addComponent(Component &comp)
{
    QJsonDocument doc = Component::toDoc(comp);
    m_client->sendData(doc);
}
