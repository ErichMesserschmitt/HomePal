#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>

enum ConnType {
    _minId = 0,
    Init,
    CreateRoom,
    CreateComponent,
    ComponentList,
    EditRoom,
    EditComponent,
    DeleteComponent,
    DeleteRoom,
    Journal,
    LastPage,
    RequestComponents,
    Disconnect,
    _maxId
};

class QWebSocket;

class IServer : public QObject {
    Q_OBJECT
public:
    IServer(QObject* parent = nullptr) : QObject(parent) {};
    IServer(const QUrl &url, bool debug = false, QObject *parent = nullptr) : QObject(parent) {
        m_url = url;
        m_debug = debug;
    }
    IServer(quint16 port, bool debug = false, QObject *parent = nullptr) : QObject(parent) {
        Q_UNUSED(port);
        Q_UNUSED(debug);
    }
    ~IServer() override = default;

    virtual int sendData(QJsonDocument& data) = 0;
    virtual void disconnectClient(QWebSocket* socket) = 0;

signals:
    void receivedData(QJsonDocument arr, QWebSocket* socket);
public slots:
    void socketDisconnected() {qDebug() << "Socket disconnected";};

protected:
    int m_passcode;
    QUrl m_url;
    bool m_debug;
};



#endif
