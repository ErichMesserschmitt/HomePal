#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QTimer>
class RoomController;
class ConnectionController;


class GUI_Controller : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(bool isInitialized READ isInitialized NOTIFY isInitializedChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)


public:
    explicit GUI_Controller(QObject* parent = nullptr);


    bool isInitialized() { return m_isInitialized; }
    Q_INVOKABLE void restartClient();
    QString status() {return m_connectionStatus;}


signals:
    void isInitializedChanged();
    void statusChanged();


private slots:
    void initializationFinished();
    void onClosed();
    void onConnected();
    void onDisconnected();

private:
    bool m_isInitialized = false;
    QTimer m_initStartTimer;
    QQmlApplicationEngine *m_engine;
    QString m_connectionStatus = "Не з'єднано";
    RoomController *m_roomController;
    ConnectionController *m_connController;
};
