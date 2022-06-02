#include "connectioncontroller.h"
#include "Connection/tcpclient.h"
#include <QJsonObject>

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
        addComponent();
        return;
    case ConnType::CreateRoom:
        addRoom();
        return;
    case ConnType::EditRoom:
        editRoom();
        return;
    case ConnType::EditComponent:
        editComponent();
        return;
    case ConnType::Journal:
        sendJournal();
        return;
    case ConnType::Disconnect:
        disconnectClient();
        return;

    default:
        return;
    }
}
