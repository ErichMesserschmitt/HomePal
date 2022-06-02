#pragma once
#include "component.h"
#include <QObject>
#include <iostream>
#include <vector>
#include <QTimer>



class Room : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    Room(QObject* parent = nullptr);
    Room(const Room& other):
        QObject(other.parent())
    {
    }
    Room& operator=(const Room& other){
        return *this;
    }

public:
    void setIndex(int index);
    void setName(QString& name);
    void addComponent(Component& component);

    QString name() {
        return m_name;
    }

signals:
    void nameChanged();
private:
    bool checkIndex(int index);

    int m_roomIndex = 0;
    QString m_name = "Default Room " + QString::number(m_roomIndex);
    QVector<Component> m_components;
};
