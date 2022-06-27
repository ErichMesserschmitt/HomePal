#include "component.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>


Component::Component(QObject *parent) : QObject(parent)
{
    m_enableTimer = new QTimer();
    m_disableTimer = new QTimer();
    connect(m_enableTimer, &QTimer::timeout, this, &Component::enableComponent);
    connect(m_disableTimer, &QTimer::timeout, this, &Component::disableComponent);
    fetchTimes(QTime::currentTime());
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
    component["enStr"] = comp.m_nextEnable.toString();
    component["disStr"] = comp.m_nextDisable.toString();
    QJsonArray enableAtArray;
    QJsonArray disableAtArray;
    QJsonArray infoArray;
    for(auto& p : comp.enableAtQ()){
        enableAtArray.append(p.toString(Qt::DateFormat::TextDate));
    }
    for(auto& p : comp.disableAtQ()){
        disableAtArray.append(p.toString(Qt::DateFormat::TextDate));
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
    component.setLowPoint(comp.value("lowPoint").toDouble(0));
    component.setHighPoint(comp.value("highPoint").toDouble(0));
    component.setDelta(comp.value("delta").toDouble(0));
    component.setIsAuto(comp.value("isAuto").toBool(false));
    component.setEnabled(comp.value("enabled").toBool());
    component.setIndex(comp.value("index").toInt());
    component.setValue(comp.value("value").toDouble());
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
    component.setEnableAt(enableAtList);
    component.setDisableAt(disableAtList);

    return component;
}

QList<QString> Component::enableAt()
{
    QList<QString> list;
    for(auto& time : m_enableAt){
        list.append(time.toString());
    }
    return list;
}

QList<QString> Component::disableAt()
{
    QList<QString> list;
    for(auto& time : m_disableAt){
        list.append(time.toString());
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

void Component::setEnableAt(QList<QTime> d)
{
    m_enableAt = d;
    Q_EMIT enableChanged();
}

void Component::setDisableAt(QList<QTime> d)
{
    m_disableAt = d;
    Q_EMIT disableChanged();
}

void Component::setRoomIndex(int index)
{
    m_roomIndex = index;
    Q_EMIT roomIndexChanged();
}

void Component::setIsAuto(bool v)
{
    if(m_auto != v){
        m_auto = v;
        QString infoString = (m_auto ? "Автоматичний режим увімкнений о " : "Ручний режим увімкнений о ");
        m_info.push_front(infoString + QTime::currentTime().toString());
        Q_EMIT isAutoChanged();
    }
}

void Component::setEnabled(bool v)
{
    if(m_enabled != v){
        m_enabled = v;
        QString infoString = (m_enabled ? "Увімкнений о " : "Вимкнений о ");
        m_info.push_front(infoString + QTime::currentTime().toString());
        Q_EMIT enabledChanged();
    }
}

void Component::enableComponent()
{
    m_enableTimer->stop();
    if(m_auto){
        setEnabled(true);
    }
    fetchTimes(QTime::currentTime());
}

void Component::disableComponent()
{
    m_disableTimer->stop();
    if(m_auto){
        setEnabled(false);
    }
    fetchTimes(QTime::currentTime());
}

void Component::fetchTimes(QTime startTime)
{
    QTime now = QTime::currentTime();
    QTime previousEnable = findPrevious(now, m_enableAt);
    QTime previousDisable = findPrevious(now, m_disableAt);
    QTime nextEnable = findNext(now, m_enableAt);
    QTime nextDisable = findNext(now, m_disableAt);
    m_nextEnable = nextEnable;
    m_nextDisable = nextDisable;
    if(previousDisable < previousEnable) {
        if(m_auto){
            setEnabled(true);
        }
    }

    int toen = QTime::currentTime().secsTo(nextEnable) * 1000;
    int todi = QTime::currentTime().secsTo(nextDisable)* 1000;
    if(toen > 0){
        m_enableTimer->start(toen);
    }
    if(todi > 0){
        m_disableTimer->start(todi);
    }
}

QTime Component::findNext(QTime startTime, QList<QTime> list)
{
    QTime minimalTime;

    //disabled Times
    bool firstTime = true;
    bool foundOne = false;
    for(auto& t : list){
        if(t > startTime){
            foundOne = true;
            if(firstTime) {
                firstTime = false;
                minimalTime = t;
            }
            minimalTime = std::min(minimalTime, t);
        }
    }

    firstTime = true;
    if(!foundOne) {
        for(auto& t : list){
            if(firstTime) {
                firstTime = false;
                minimalTime = t;
            }
            minimalTime = std::min(minimalTime, t);
        }
    }
    return minimalTime;
}

QTime Component::findPrevious(QTime startTime, QList<QTime> list)
{
    QTime maximalTime;

    bool firstTime = true;
    bool foundOne = false;
    for(auto& t : list){
        if(t < startTime){
            foundOne = true;
            if(firstTime) {
                firstTime = false;
                maximalTime = t;
            }
            maximalTime = std::max(maximalTime, t);

        }
    }
    firstTime = true;
    if(!foundOne) {
        for(auto& t : list){
            if(firstTime) {
                firstTime = false;
                maximalTime = t;
            }
            maximalTime = std::max(maximalTime, t);
        }
    }
    return maximalTime;
}







