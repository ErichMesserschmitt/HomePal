#include "component.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>


Component::Component(QObject *parent) : QObject(parent)
{


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





