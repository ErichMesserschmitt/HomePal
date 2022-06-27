#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QStandardPaths>
#include <QDir>
#include <QJsonDocument>
#include <QTimer>

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

class IClient : public QObject {
    Q_OBJECT
public:
    IClient(QObject* parent = nullptr) : QObject(parent) {};
    IClient(const QUrl &url, bool debug = false, QObject *parent = nullptr) : QObject(parent) {
        m_url = url;
        m_debug = debug;
    }
    ~IClient() override = default;

    virtual QJsonDocument& receiveData() = 0;
    virtual int sendData(QJsonDocument& data) = 0;

signals:
    void receivedDataChanged();
    void connectionLost();
    void connected();

protected:
    virtual void setReceivedData(QJsonDocument& doc) = 0;
    QJsonDocument m_receivedData;
    QTimer* m_pingTimer;
    QTimer* m_waitTimer;

    int m_passcode;
    QUrl m_url;
    bool m_debug;
};

#endif
