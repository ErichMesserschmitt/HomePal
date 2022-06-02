#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QTimer>

enum ComponentType {
    _minid = 0,
    Switcher = 1,
    Slider,
    _maxid
};

class Component : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
public:
    explicit Component(QObject* parent = nullptr);
    Component(const Component& other):
        QObject(other.parent())
    {
    }
    Component& operator=(const Component& other){
        return *this;
    }

    int index() {return m_index;}
    QString name() {return m_name;}

signals:
    void nameChanged();
private:
    int m_index = 0;
    int m_roomIndex = 0;
    QString m_name = "Default Room " + QString::number(m_roomIndex);
    ComponentType m_type = ComponentType::Switcher;
    float m_lowPoint = 0;
    float m_highPoint = 0;
    float m_pointDelta = 0.1;
    QList<QString> m_info;
};
