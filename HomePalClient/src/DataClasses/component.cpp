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
    component.setIndex(comp.value("index").toInt());
    component.setLowPoint(comp.value("lowPoint").toDouble(0));
    component.setHighPoint(comp.value("highPoint").toDouble(0));
    component.setDelta(comp.value("delta").toDouble(0));
    component.setIsAuto(comp.value("isAuto").toBool(false));
    component.setEnabled(comp.value("enabled").toBool());
    component.setIndex(comp.value("index").toInt());
    QJsonArray enableAtArray = comp.value("enableAt").toArray();
    QList<QDateTime> enableAtList;
    QJsonArray disableAtArray = comp.value("disableAt").toArray();
    QList<QDateTime> disableAtList;;
    QJsonArray infoArray = comp.value("info").toArray();
    QList<QString> infoList;
    for(auto a : enableAtArray) {
        enableAtList.append(QDateTime::fromString(a.toString()));
    }
    for(auto a : disableAtArray) {
        disableAtList.append(QDateTime::fromString(a.toString()));
    }
    for(auto a : infoArray) {
        infoList.append(a.toString());
    }
    component.m_enableAt = enableAtList;
    component.m_disableAt = disableAtList;
    component.m_info = infoList;

    return component;
}

QList<QString> Component::enableAt()
{
    QList<QString> list;
    for(auto& time : m_enableAt){
        list.append(time.toString());
    }
}

QList<QString> Component::disableAt()
{
    QList<QString> list;
    for(auto& time : m_disableAt){
        list.append(time.toString());
    }
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

void Component::setEnableAt(QList<QDateTime> d)
{
    m_enableAt = d;
    Q_EMIT enableChanged();
}

void Component::setDisableAt(QList<QDateTime> d)
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
    m_auto = v;
    Q_EMIT isAutoChanged();
}

void Component::setEnabled(bool v)
{
    if(m_enabled != v){
        m_enabled = v;
        QString infoString = (m_enabled ? "Enabled at " : "Disabled at ");
        m_info.push_front(infoString + QTime::currentTime().toString());
        Q_EMIT enabledChanged();
    }
}





