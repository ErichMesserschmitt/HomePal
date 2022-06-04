#pragma once
#include "component.h"
#include <QObject>
#include <iostream>
#include <vector>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>




class RoomGroup : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(int index READ index NOTIFY indexChanged)
public:
    RoomGroup(QObject* parent = nullptr);
    RoomGroup(const RoomGroup& other):
        QObject(other.parent())
      , m_index(other.m_index)
      , m_name(other.m_name)
    {
    }
    RoomGroup& operator=(const RoomGroup& other){
        return *this;
    }
public:
    void setIndex(int index);
    void setName(QString& name);

    static QJsonDocument toDoc(RoomGroup& room);
    static RoomGroup fromDoc(QJsonDocument& doc);

    QString name() {
        return m_name;
    }
    int index() {
        return m_index;
    }
signals:
    void nameChanged();
    void indexChanged();
private:
    int m_index = 0;
    QString m_name = "Default Room " + QString::number(m_index);
};
