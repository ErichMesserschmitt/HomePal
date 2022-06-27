#pragma once

#include <QObject>
#include <iostream>
#include <vector>
#include <QProcess>
#include <QTimer>
#include <QDateTime>
#include <QTime>

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

struct TimePlan {
    QTime enableAt;
    QTime disableAt;
};

class Component : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString name         READ name  NOTIFY nameChanged)
    Q_PROPERTY(int index            READ index      NOTIFY indexChanged)
    Q_PROPERTY(float lowPoint       READ lowPoint   NOTIFY lowPointChanged)
    Q_PROPERTY(float highPoint      READ highPoint  NOTIFY highPointChanged)
    Q_PROPERTY(float delta          READ delta      NOTIFY deltaChanged)
    Q_PROPERTY(float value          READ value  WRITE setValue    NOTIFY valueChanged)
    Q_PROPERTY(QString valueName    READ valueName  NOTIFY valueNameChanged)
    Q_PROPERTY(QList<QString> info    READ info       NOTIFY infoChanged)
    Q_PROPERTY(QList<QString> enableAt  READ enableAt  NOTIFY enableChanged)
    Q_PROPERTY(QList<QString> disableAt READ disableAt NOTIFY disableChanged)
    Q_PROPERTY(QString enStr        READ enStr NOTIFY enableChanged)
    Q_PROPERTY(QString disStr        READ disStr NOTIFY disableChanged)
    Q_PROPERTY(int type             READ type       NOTIFY typeChanged)
    Q_PROPERTY(int roomIndex        READ roomIndex  NOTIFY roomIndexChanged)
    Q_PROPERTY(bool isAuto          READ isAuto  NOTIFY isAutoChanged)
    Q_PROPERTY(bool enabled         READ enabled NOTIFY enabledChanged)

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
      , m_timePlan(other.m_timePlan)
      , m_auto(other.m_auto)
      , m_enabled(other.m_enabled)
      , m_value(other.m_value)
      , m_valueName(other.m_valueName)
      , m_enStr(other.m_enStr)
      , m_disStr(other.m_disStr)
    {

    }
    Component(const Component* other):
        QObject(other->parent())
      , m_index(other->m_index)
      , m_name(other->m_name)
      , m_lowPoint(other->m_lowPoint)
      , m_highPoint(other->m_highPoint)
      , m_pointDelta(other->m_pointDelta)
      , m_info(other->m_info)
      , m_type(other->m_type)
      , m_roomIndex(other->m_roomIndex)
      , m_timePlan(other->m_timePlan)
      , m_auto(other->m_auto)
      , m_enabled(other->m_enabled)
      , m_value(other->m_value)
      , m_valueName(other->m_valueName)
      , m_enStr(other->m_enStr)
      , m_disStr(other->m_disStr)
    {

    }
    Component& operator=(const Component* other){
        return *this;
    }
    Component& operator=(const Component& other){
        return *this;
    }

    Q_INVOKABLE void switchEnabled();
    Q_INVOKABLE void switchAuto();
    Q_INVOKABLE void addTimePlan(int hourEn, int minEn, int hourDi, int minDi);
    Q_INVOKABLE void editTimePlan(int index, int hourEn, int minEn, int hourDi, int minDi);
    Q_INVOKABLE void deleteTimePlan(int index);


    static QJsonDocument toDoc(Component& comp);
    static Component fromDoc(QJsonDocument& doc);

    int index() {return m_index;}
    QString name() {return m_name;}
    QString enStr() {return m_enStr;}
    QString disStr() {return m_disStr;}
    float lowPoint() {return m_lowPoint;}
    float highPoint() {return m_highPoint;}
    float delta() {return m_pointDelta;}
    QList<QString> info() {return m_info;}
    ComponentType type() {return m_type;}
    int roomIndex() {return m_roomIndex;}
    QList<QString> enableAt();
    QList<QString> disableAt();

    QList<TimePlan> timePlan() {return m_timePlan;};


    QString valueName() {return m_valueName;};
    float value() {return m_value;}

    bool isAuto() {return m_auto;}
    bool enabled() {return m_enabled;}

    void setIndex(int index);
    void setName(QString& name);
    void setLowPoint(float p);
    void setHighPoint(float p);
    void setDelta(float d);
    void setInfo(QList<QString> info);
    void setType(ComponentType type);
    void setTimePlan(QList<TimePlan> plan);
    void setRoomIndex(int index);
    void setIsAuto(bool v);
    void setEnabled(bool v);
    void setValue(float v);
    void setValueName(QString v);


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
    void timePlanChanged();

    void valueChanged();
    void valueNameChanged();
private:
    int m_index = 0;
    int m_roomIndex = 0;
    QString m_name = "Default Room " + QString::number(m_roomIndex);
    ComponentType m_type = ComponentType::Switcher;
    float m_lowPoint = 0;
    float m_highPoint = 0;
    float m_pointDelta = 0.1;
    float m_value = 0;
    QString m_valueName = "";
    QString m_enStr;
    QString m_disStr;
    QList<TimePlan> m_timePlan;
    bool m_auto = false;
    bool m_enabled = false;
    QList<QString> m_info;
};
