#include "component.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>


Component::Component(QObject *parent) : QObject(parent)
{


}

void Component::switchEnabled()
{
    setEnabled(!m_enabled);
}

void Component::switchAuto()
{
    setIsAuto(!m_auto);
}

void Component::addTimePlan(int hourEn, int minEn, int hourDi, int minDi)
{
    m_timePlan.append(TimePlan{QTime(hourEn, minEn, 0, 0), QTime(hourDi, minDi, 0, 0)});
    Q_EMIT enableChanged();
    Q_EMIT disableChanged();
}

void Component::editTimePlan(int index, int hourEn, int minEn, int hourDi, int minDi)
{
    if(index >= 0 && index < m_timePlan.size()){
        m_timePlan[index].enableAt = QTime(hourEn, minEn, 0, 0);
        m_timePlan[index].disableAt = QTime(hourDi, minDi, 0, 0);
    }
    Q_EMIT enableChanged();
    Q_EMIT disableChanged();
}

void Component::deleteTimePlan(int index)
{
    QList<TimePlan> list;
    for(int i =0; i<m_timePlan.size(); ++i){
        if(i != index){
            list.append(m_timePlan[i]);
        }
    }
    m_timePlan = list;
    Q_EMIT enableChanged();
    Q_EMIT disableChanged();
}

QJsonDocument Component::toDoc(Component &comp)
{
    QJsonObject component;
    component["el_type"] = comp.type();
    component["name"] = comp.name();
    component["roomIndex"] = comp.roomIndex();
    component["lowPoint"] = comp.lowPoint();
    component["highPoint"] = comp.highPoint();
    component["delta"] = comp.delta();
    component["isAuto"] = comp.isAuto();
    component["enabled"] = comp.enabled();
    component["index"] = comp.index();
    component["value"] = comp.value();
    QJsonArray enableAtArray;
    QJsonArray disableAtArray;
    QJsonArray infoArray;
    for(auto& t: comp.m_timePlan){
        enableAtArray.append(t.enableAt.toString());
        disableAtArray.append(t.disableAt.toString());
    }
    for(auto& p : comp.info()){
        infoArray.append(p);
    }
    component["enableAt"] = enableAtArray;
    component["disableAt"] = disableAtArray;
    component["info"] = infoArray;
    return QJsonDocument(component);
}

Component Component::fromDoc(QJsonDocument &doc)
{
    Component component;
    QJsonObject comp = doc.object();
    component.setType(static_cast<ComponentType>(comp.value("el_type").toInt(0)));
    QString name = comp.value("name").toString();
    component.setName(name);
    component.setRoomIndex(comp.value("roomIndex").toInt(0));
    component.setIndex(comp.value("index").toInt());
    component.setLowPoint(comp.value("lowPoint").toDouble(0));
    component.setHighPoint(comp.value("highPoint").toDouble(0));
    component.setDelta(comp.value("delta").toDouble(0));
    component.setIsAuto(comp.value("isAuto").toBool(false));
    component.setEnabled(comp.value("enabled").toBool());
    component.setIndex(comp.value("index").toInt());
    component.setValue(comp.value("value").toDouble());
    component.m_enStr = (comp.value("enStr").toString());
    component.m_disStr = (comp.value("disStr").toString());
    QJsonArray enableAtArray = comp.value("enableAt").toArray();
    QList<QTime> enableAtList;
    QJsonArray disableAtArray = comp.value("disableAt").toArray();
    QList<QTime> disableAtList;;
    QJsonArray infoArray = comp.value("info").toArray();
    QList<QString> infoList;
    for(auto a : enableAtArray) {
        enableAtList.append(QTime::fromString(a.toString()));
    }
    for(auto a : disableAtArray) {
        disableAtList.append(QTime::fromString(a.toString()));
    }
    for(auto a : infoArray) {
        infoList.append(a.toString());
    }
    for(int i =0; i<enableAtList.size(); ++i){
        component.m_timePlan.append(TimePlan{enableAtList[i], disableAtList[i]});
    }
    component.m_info = infoList;

    return component;
}

QList<QString> Component::enableAt()
{
    QList<QString> list;
    for(auto& time : m_timePlan){
        list.append(time.enableAt.toString());
    }
    return list;
}

QList<QString> Component::disableAt()
{
    QList<QString> list;
    for(auto& time : m_timePlan){
        list.append(time.disableAt.toString());
    }
    return list;
}

void Component::setIndex(int index)
{
    m_index = index;
    Q_EMIT indexChanged();
}

void Component::setName(QString &name)
{
    m_name = name;
    Q_EMIT nameChanged();
}

void Component::setLowPoint(float p)
{
    m_lowPoint = p;
    Q_EMIT lowPointChanged();
}

void Component::setHighPoint(float p)
{
    m_highPoint = p;
    Q_EMIT highPointChanged();
}

void Component::setDelta(float d)
{
    m_pointDelta = d;
    Q_EMIT deltaChanged();
}

void Component::setInfo(QList<QString> info)
{
    m_info = info;
    Q_EMIT infoChanged();
}

void Component::setType(ComponentType type)
{
    m_type = type;
    Q_EMIT typeChanged();
}

void Component::setTimePlan(QList<TimePlan> plan)
{
m_timePlan = plan;
Q_EMIT timePlanChanged();
}

void Component::setRoomIndex(int index)
{
    m_roomIndex = index;
    Q_EMIT roomIndexChanged();
}

void Component::setIsAuto(bool v)
{
    m_auto = v;
    Q_EMIT isAutoChanged();
}

void Component::setEnabled(bool v)
{
    if(m_enabled != v){
        m_enabled = v;
        QString infoString = (m_enabled ? "Ввімкнено о " : "Вимкнено о ");
        m_info.push_front(infoString + QTime::currentTime().toString());
        Q_EMIT enabledChanged();
    }
}

void Component::setValue(float v){
    m_value = v;
    Q_EMIT valueChanged();
}

void Component::setValueName(QString v){
    m_valueName = v;
    Q_EMIT valueNameChanged();
}





