#include "room.h"
#include "component.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>



RoomGroup::RoomGroup(QObject *parent) : QObject(parent)
{


}


void RoomGroup::setIndex(int index)
{
    if(m_index != index) {
        m_index = index;
        Q_EMIT indexChanged();
    }
}

void RoomGroup::setName(QString &name)
{
    if(name != m_name){
        m_name = name;
        Q_EMIT nameChanged();
    }
}

QJsonDocument RoomGroup::toDoc(RoomGroup &room)
{
    QJsonObject doc;
    doc["index"] = room.index();
    doc["el_type"] = ComponentType::Room;
    doc["name"] = room.name();
    return QJsonDocument(doc);
}

RoomGroup RoomGroup::fromDoc(QJsonDocument &doc)
{
    RoomGroup room;
    QJsonObject o = doc.object();
    room.setIndex(o.value("index").toInt());
    QString name = o.value("name").toString();
    room.setName(name);
    return room;
}





