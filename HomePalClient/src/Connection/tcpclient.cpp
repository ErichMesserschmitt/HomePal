/****************************************************************************
**
** Copyright (C) 2016 Kurt Pattyn <pattyn.kurt@gmail.com>.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebSockets module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "tcpclient.h"
#include "connection.h"
#include <QtCore/QDebug>
#include <QJsonObject>

QT_USE_NAMESPACE

ClientTCP::~ClientTCP()
{

}

ClientTCP::ClientTCP(const QUrl &url, bool debug, QObject *parent) : IClient(url, debug, parent)
{
    m_debug = false;
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    m_pingTimer = new QTimer();
    m_pingTimer->setInterval(10000);
    m_waitTimer = new QTimer();
    m_waitTimer->setInterval(7000);
    m_waitTimer->setSingleShot(true);
    connect(&m_webSocket, &QWebSocket::connected, this, &ClientTCP::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ClientTCP::closed);
    connect(m_waitTimer, &QTimer::timeout, this, &ClientTCP::connectionLost);
    connect(m_waitTimer, &QTimer::timeout, this, &ClientTCP::onConnectionLost);

    connect(&m_webSocket, &QWebSocket::pong, this, &ClientTCP::onPingReceived);
    connect(m_pingTimer, &QTimer::timeout, this, &ClientTCP::prepareSendPing);
    m_webSocket.open(url);
}

int ClientTCP::sendData(QJsonDocument &doc)
{
    QByteArray data = doc.toJson();
    return m_webSocket.sendBinaryMessage(data);
}


void ClientTCP::onConnected()
{
    if (m_debug)
        qDebug() << "ClientTCP::onConnected client succesfully connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ClientTCP::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &ClientTCP::onDataReceived);

    m_pingTimer->start();
    QJsonObject initRequest;
    initRequest["ConnType"] = ConnType::Init;
    initRequest["Word"] = m_passcode;
    QByteArray initRequestByte = QJsonDocument(initRequest).toJson();
    m_webSocket.sendBinaryMessage(initRequestByte);
    Q_EMIT connected();
}


void ClientTCP::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
}

void ClientTCP::onDataReceived(QByteArray data)
{
    if(m_debug){
        qDebug() << "Data received, length" << data.length();
        qDebug() << "JSON data" << QJsonDocument::fromJson(data);
    }
    if(data.isEmpty()){
        qWarning() << "ClientTCP::onDataReceived :: data is empty";
        return;
    }
    QJsonDocument receivedDoc;
    receivedDoc = QJsonDocument::fromJson(data);
    setReceivedData(receivedDoc);
}

void ClientTCP::onPingSent()
{
    qDebug() << "ClientTCP::onPingSent ping sent";
    m_waitTimer->start();
}

void ClientTCP::onConnectionLost()
{
    qDebug() << "ClientTCP::onConnectionLost stop timers";

    m_pingTimer->stop();
    m_waitTimer->stop();
}

void ClientTCP::onPingReceived(quint64 elapsedTime,const QByteArray &payload)
{
    qDebug() << "ClientTCP::onPingReceived ping received" << elapsedTime << payload;
    m_waitTimer->stop();
    m_waitTimer->setInterval(7000);
}

void ClientTCP::prepareSendPing()
{
    qDebug() << "ClientTCP::prepareSendPing seinding ping";
    m_webSocket.ping(QByteArray("testping"));
    onPingSent();
}

void ClientTCP::setReceivedData(QJsonDocument &doc)
{
    if(doc != m_receivedData){
        m_receivedData = doc;
        Q_EMIT receivedDataChanged();
    }
}
