#include "room.h"
#include "component.h"
#include <QDebug>
#include <QDebug>
#include <QFontDatabase>
#include <QQmlContext>


Room::Room(QObject *parent) : QObject(parent)
{


}

void Room::addComponent(Component& component)
{
    bool m_indexCorrect = false;
    int index = m_components.length();
    while(!m_indexCorrect){
        m_indexCorrect = !checkIndex(index);
        if(!m_indexCorrect) {
            ++index;
        }
    }
    m_components.push_back(component);
}

void Room::setIndex(int index)
{
    if(m_roomIndex != index) {
        m_roomIndex = index;
    }
}

void Room::setName(QString &name)
{
    if(name != m_name){
        m_name = name;
        Q_EMIT nameChanged();
    }
}

bool Room::checkIndex(int index)
{
    for(auto& component : m_components) {
        if(component.index() == index){
            return true;
        }
    }
    return false;
}




