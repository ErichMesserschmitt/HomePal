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

public:
    explicit GUI_Controller(QObject* parent = nullptr);


    bool isInitialized() { return m_isInitialized; }

signals:
    void isInitializedChanged();


private slots:
    void initializationFinished();
    void onClosed();

private:
    bool m_isInitialized = false;
    QTimer m_initStartTimer;
    QQmlApplicationEngine *m_engine;
    RoomController *m_roomController;
    ConnectionController *m_connController;
};
