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

protected:
    virtual void setReceivedData(QJsonDocument& doc) = 0;
    QJsonDocument m_receivedData;
    int m_passcode;
    QUrl m_url;
    bool m_debug;
};

#endif
