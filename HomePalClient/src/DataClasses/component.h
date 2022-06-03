#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QTimer>
#include <QDateTime>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

enum ComponentType {
    _minid = 0,
    Switcher = 1,
    Slider,
    Room,
    _maxid
};

class Component : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name         READ name       NOTIFY nameChanged)
    Q_PROPERTY(int index            READ index      NOTIFY indexChanged)
    Q_PROPERTY(float lowPoint       READ lowPoint   NOTIFY lowPointChanged)
    Q_PROPERTY(float highPoint      READ highPoint  NOTIFY highPointChanged)
    Q_PROPERTY(float delta          READ delta      NOTIFY deltaChanged)
    Q_PROPERTY(QList<QString> info    READ info       NOTIFY infoChanged)
    Q_PROPERTY(QList<QDateTime> enableAt READ enableAt  NOTIFY enableChanged)
    Q_PROPERTY(QList<QDateTime> disableAt READ disableAt NOTIFY disableChanged)
    Q_PROPERTY(int type             READ type       NOTIFY typeChanged)
    Q_PROPERTY(int roomIndex        READ roomIndex  NOTIFY roomIndexChanged)
    Q_PROPERTY(bool isAuto          READ isAuto     NOTIFY isAutoChanged)

public:
    explicit Component(QObject* parent = nullptr);
    Component(const Component& other):
        QObject(other.parent())
    {
    }
    Component& operator=(const Component& other){
        return *this;
    }

    static QJsonDocument toDoc(Component& comp);
    static Component fromDoc(QJsonDocument& doc);

    int index() {return m_index;}
    QString name() {return m_name;}
    float lowPoint() {return m_lowPoint;}
    float highPoint() {return m_highPoint;}
    float delta() {return m_pointDelta;}
    QList<QString> info() {return m_info;}
    ComponentType type() {return m_type;}
    int roomIndex() {return m_roomIndex;}
    QList<QDateTime> enableAt() {return m_enableAt;}
    QList<QDateTime> disableAt() {return m_disableAt;}
    bool isAuto() {return m_auto;}

    void setIndex(int index);
    void setName(QString& name);
    void setLowPoint(float p);
    void setHighPoint(float p);
    void setDelta(float d);
    void setInfo(QList<QString> info);
    void setType(ComponentType type);
    void setEnableAt(QList<QDateTime> d);
    void setDisableAt(QList<QDateTime> d);
    void setRoomIndex(int index);
    void setIsAuto(bool v);


signals:
    void nameChanged();
    void indexChanged();
    void lowPointChanged();
    void highPointChanged();
    void deltaChanged();
    void infoChanged();
    void typeChanged();
    void enableChanged();
    void disableChanged();
    void roomIndexChanged();
    void isAutoChanged();
private:
    int m_index = 0;
    int m_roomIndex = 0;
    QString m_name = "Default Room " + QString::number(m_roomIndex);
    ComponentType m_type = ComponentType::Switcher;
    float m_lowPoint = 0;
    float m_highPoint = 0;
    float m_pointDelta = 0.1;
    QList<QDateTime> m_enableAt;
    QList<QDateTime> m_disableAt;
    bool m_auto = false;
    QList<QString> m_info;
};
