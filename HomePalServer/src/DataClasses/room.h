#pragma once
#include "component.h"
#include <QObject>
#include <iostream>
#include <vector>
#include <QTimer>



class RoomGroup : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    RoomGroup(QObject* parent = nullptr);
    RoomGroup(const RoomGroup& other):
        QObject(other.parent())
    {
    }
    RoomGroup& operator=(const RoomGroup& other){
        return *this;
    }

public:
    void setIndex(int index);
    void setName(QString& name);
    void addComponent(Component& component);

    int index() {return m_index;}

    QString name() {
        return m_name;
    }

signals:
    void nameChanged();
private:
    bool checkIndex(int index);

    int m_index = 0;
    QString m_name = "Default Room " + QString::number(m_index);
    QVector<Component> m_components;
};
