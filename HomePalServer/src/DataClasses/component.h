#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
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
    Q_PROPERTY(QList<QString> enableAt  READ enableAt  NOTIFY enableChanged)
    Q_PROPERTY(QList<QString> disableAt READ disableAt NOTIFY disableChanged)
    Q_PROPERTY(int type             READ type       NOTIFY typeChanged)
    Q_PROPERTY(int roomIndex        READ roomIndex  NOTIFY roomIndexChanged)
    Q_PROPERTY(bool isAuto          READ isAuto     NOTIFY isAutoChanged)
    Q_PROPERTY(bool enabled         READ enabled    NOTIFY enabledChanged)
    Q_PROPERTY(QDateTime nearestEnable READ nearestEnable NOTIFY nearestEnableChanged)
    Q_PROPERTY(QDateTime nearestDisable READ nearestDisable NOTIFY nearestDisableChanged)

public:
    explicit Component(QObject* parent = nullptr);
    Component(const Component& other):
        QObject(other.parent())
      , m_index(other.m_index)
      , m_name(other.m_name)
      , m_lowPoint(other.m_lowPoint)
      , m_highPoint(other.m_highPoint)
      , m_pointDelta(other.m_pointDelta)
      , m_info(other.m_info)
      , m_type(other.m_type)
      , m_roomIndex(other.m_roomIndex)
      , m_enableAt(other.m_enableAt)
      , m_disableAt(other.m_disableAt)
      , m_auto(other.m_auto)
      , m_enabled(other.m_enabled)
    {
        QTime disableTime = QTime::currentTime();
        QTime enableTime = QTime::currentTime();
        for(auto& e : m_enableAt){
            QTime t = e.time();
            if(t.hour() < QTime::currentTime().hour() && t.hour() > enableTime.hour()){
                enableTime = t;
            }
        }
        m_nearestEnable = QDateTime(QDate::currentDate(), enableTime);
        for(auto& e : m_disableAt){
            QTime t = e.time();
            if(t.hour() > QTime::currentTime().hour() && t.hour() < disableTime.hour()){
                disableTime = t;
            }
        }
        m_nearestDisable = QDateTime(QDate::currentDate(), disableTime);
        Q_EMIT nearestEnableChanged();
        Q_EMIT nearestDisableChanged();
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
    float value() {return m_value;}
    QList<QString> enableAt();
    QList<QString> disableAt();

    QList<QDateTime> enableAtQ() {return m_enableAt;};
    QList<QDateTime> disableAtQ() {return m_disableAt;};

    QDateTime nearestEnable() {return m_nearestEnable;};
    QDateTime nearestDisable(){return m_nearestDisable;};

    bool isAuto() {return m_auto;}
    bool enabled() {return m_enabled;}

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
    void setEnabled(bool v);
    void setValue(float val) {m_value = val; Q_EMIT valueChanged();}


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
    void enabledChanged();
    void nearestEnableChanged();
    void nearestDisableChanged();
    void valueChanged();
private:
    int m_index = 0;
    int m_roomIndex = 0;
    QString m_name = "Default Room " + QString::number(m_roomIndex);
    ComponentType m_type = ComponentType::Switcher;
    float m_lowPoint = 0;
    float m_highPoint = 0;
    float m_pointDelta = 0.1;
    float m_value = 0;
    QList<QDateTime> m_enableAt;
    QList<QDateTime> m_disableAt;
    QDateTime m_nearestEnable;
    QDateTime m_nearestDisable;
    bool m_auto = false;
    bool m_enabled = false;
    QList<QString> m_info;
};
