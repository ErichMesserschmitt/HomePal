#include "processcontroller.h"
#include "Connection/tcpserver.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QWebSocket>

ProcessController::ProcessController(QObject *parent) : QObject(parent)
{
    qDebug() << "ConnectionController::ConnectionController is initialized";

    startServer();

}

void ProcessController::startServer()
{
    m_server = new ServerTCP(1488, true, this);
    connect(m_server, &IServer::receivedData, this, &ProcessController::onDataReceived);
    connect(this, &ProcessController::dataProcessed, m_server, &IServer::sendData);
    m_lastPageUpdater = new QTimer(this);
    m_lastPageUpdater->setInterval(60000);
    m_journalUpdater = new QTimer(this);
    m_journalUpdater->setInterval(1800000);
    m_connectionTimer = new QTimer(this);
    connect(m_lastPageUpdater, &QTimer::timeout, this, &ProcessController::updateLastPage);
    connect(m_journalUpdater, &QTimer::timeout, this, &ProcessController::updateJournal);
    connect(m_connectionTimer, &QTimer::timeout, this, &ProcessController::updateAll);
    connect(m_server, &IServer::clientConnected, this, &ProcessController::initializeUpdate);

    test();

    m_lastPageUpdater->setSingleShot(false);
    m_lastPageUpdater->start(6000);
    m_journalUpdater->setSingleShot(false);
    m_journalUpdater->start(1800000);
    m_connectionTimer->setSingleShot(true);
    m_connectionTimer->setInterval(200);
}

void ProcessController::onDataReceived(QJsonDocument doc, QWebSocket* socket)
{
    qDebug() << "ConnectionController::onDataReceived :: signal emmited";
    processData(doc, socket);
}

void ProcessController::processData(QJsonDocument &doc, QWebSocket* socket)
{
    QJsonObject received = doc.object();
    ConnType dataType = static_cast<ConnType>(received.value("type").toInt());
    switch(dataType){
    case ConnType::Init:
        return;
    case ConnType::RequestComponents:
        sendComponents(socket);
        return;
    case ConnType::CreateComponent:
        addComponent(doc);
        return;
    case ConnType::CreateRoom:
        addRoom(doc);
        return;
    case ConnType::EditRoom:
        editRoom(doc);
        return;
    case ConnType::EditComponent:
        editComponent(doc);
        return;
    case ConnType::Journal:
        sendJournal(socket);
        return;
    case ConnType::DeleteComponent:
        deleteComponent(doc);
        return;
    case ConnType::DeleteRoom:
        deleteRoom(doc);
        return;
    case ConnType::LastPage:
        sendLastPage();
        return;
    case ConnType::Disconnect:
        qDebug() << "ConnectionController::processData :: client preparing for disconnect";
        if(socket){
            socket->disconnect(this);
        }
        return;

    default:
        return;

    }
}

void ProcessController::disconnectClient(QWebSocket* socket)
{
    m_server->disconnectClient(socket);
}

void ProcessController::processInitialization(QJsonDocument &data, QWebSocket *socket)
{

}

void ProcessController::addComponent(QJsonDocument& data)
{
    Component comp = Component::fromDoc(data);
    QList<Component> newList;
    for(auto& c : m_pendingComponents){
        if(c.index() == comp.index()){
            Component prepared(c);
            prepared.setRoomIndex(comp.roomIndex());
            m_connectedComponents.push_back(prepared);
        } else {
            newList.push_back(c);
        }
    }
    m_pendingComponents = newList;
    updateLastPage();
}

void ProcessController::addRoom(QJsonDocument& data)
{
    RoomGroup room = RoomGroup::fromDoc(data);
    int newIndex = 1;
    bool possible = true;
    while(true){
        for(auto& r : m_rooms){
            if(newIndex == r.index()){
                possible = false;
                break;
            }
        }
        if(possible){
            break;
        }
        possible = true;
        ++newIndex;
    }
    room.setIndex(newIndex);
    m_rooms.append(room);
    updateLastPage();
}

void ProcessController::editComponent(QJsonDocument& data)
{
    Component comp = Component::fromDoc(data);
    for(auto& c : m_connectedComponents){
        if(c.index() == comp.index()){
            auto copy = c;
            c.setIsAuto(comp.isAuto());
            c.setEnabled(comp.enabled());
            c.setType(copy.type());
            c.setLowPoint(copy.lowPoint());
            c.setHighPoint(copy.highPoint());
            c.setDelta(copy.delta());
            c.setEnableAt(comp.enableAtQ());
            c.setDisableAt(comp.disableAtQ());
            c.setValue(comp.value());
            c.fetchTimes(QTime::currentTime());
            updateLastPage();
        }
    }
}

void ProcessController::editRoom(QJsonDocument& data)
{
    RoomGroup room = RoomGroup::fromDoc(data);
    for(auto& r : m_rooms) {
        if(r.index() == room.index()){
            QString name = room.name();
            r.setName(name);
        }
    }
    updateLastPage();
}

void ProcessController::deleteComponent(QJsonDocument &data)
{
    Component comp = Component::fromDoc(data);
    QList<Component> newList;
    for(auto& r : m_connectedComponents) {
        if(r.index() != comp.index()){
            newList.append(r);
        }
    }
    m_connectedComponents = newList;
    m_pendingComponents.append(comp);
    updateLastPage();
}

void ProcessController::deleteRoom(QJsonDocument &data)
{
    RoomGroup room = RoomGroup::fromDoc(data);
    QList<RoomGroup> newList;

    for(auto& r : m_rooms) {
        if(r.index() != room.index()){
            newList.append(r);
        }
    }
    m_rooms = newList;

    for(auto& c : m_connectedComponents){
        if(c.roomIndex() == room.index()){
            c.setRoomIndex(0);
        }
    }
    updateLastPage();
}

void ProcessController::sendJournal(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::Journal;
    QJsonArray pageArray;

    for(auto& page : m_fullJournal){
        QJsonObject pageObj;

        QJsonArray roomArr;
        for(auto &room : page.m_rooms){
            roomArr.append(RoomGroup::toDoc(*room).object());
        }
        QJsonArray compArr;
        for(auto &comp : page.m_components){
            compArr.append(Component::toDoc(*comp).object());
        }
        QJsonArray infoArr;
        for(auto &inf : page.m_shortInfo){
            infoArr.append(QJsonValue(inf));
        }
        pageObj["rooms"] = roomArr;
        pageObj["components"] = compArr;
        pageObj["info"] = infoArr;
        pageArray.append(pageObj);
    }
    objToSend["list"] = pageArray;
    QJsonDocument doc = QJsonDocument(objToSend);
    qDebug() << "ProcessController::sendJournal :: journal sended " << QDateTime::currentDateTime().toString();
    Q_EMIT dataProcessed(doc);
}

void ProcessController::sendLastPage()
{
    QJsonObject pageObj;
    pageObj["type"] = ConnType::LastPage;
    QJsonArray roomArr;
    for(auto &room : m_lastPage.m_rooms){
        roomArr.append(RoomGroup::toDoc(*room).object());
    }
    QJsonArray compArr;
    for(auto &comp : m_lastPage.m_components){
        compArr.append(Component::toDoc(*comp).object());
    }
    QJsonArray infoArr;
    for(auto &inf : m_lastPage.m_shortInfo){
        infoArr.append(QJsonValue(inf));
    }
    pageObj["rooms"] = roomArr;
    pageObj["components"] = compArr;
    pageObj["info"] = infoArr;
    QJsonDocument doc = QJsonDocument(pageObj);
    qDebug() << "ProcessController::sendLastPage :: last page sended " << QDateTime::currentDateTime().toString();
    Q_EMIT dataProcessed(doc);
}



void ProcessController::sendComponents(QWebSocket* socket)
{
    QJsonObject objToSend;
    objToSend["type"] = ConnType::ComponentList;
    QJsonArray componentArr;
    for(auto &component : m_pendingComponents){
        componentArr.append(Component::toDoc(component).object());
    }
    objToSend["list"] = componentArr;
    QJsonDocument doc = QJsonDocument(objToSend);
    Q_EMIT dataProcessed(doc, socket);
}

void ProcessController::updateJournal()
{
    JournalPage page;
    for(auto& c:m_connectedComponents){
        page.m_components.push_back(new Component(c));
    }
    for(auto& c:m_rooms){
        page.m_rooms.push_back(new RoomGroup(c));
    }
    QString info = "Time " + QDateTime::currentDateTime().toString(Qt::DateFormat::TextDate) + ". Generated at simulation";
    page.m_shortInfo = info;

    m_fullJournal.append(page);
    qDebug() << "ProcessController::updateJournal";
    sendJournal();
}

void ProcessController::updateLastPage()
{
    JournalPage page;
    for(auto& c:m_connectedComponents){
        page.m_components.push_back(new Component(c));
    }
    for(auto& c:m_rooms){
        page.m_rooms.push_back(new RoomGroup(c));
    }
    QString info = "Time " + QDateTime::currentDateTime().toString(Qt::DateFormat::TextDate) + ". Generated at simulation";
    page.m_shortInfo = info;
    m_lastPage = page;
    qDebug() << "ProcessController::updateLastPage";
    sendLastPage();
}

void ProcessController::updateAll()
{
    updateLastPage();
    updateJournal();
}

void ProcessController::initializeUpdate()
{
    m_connectionTimer->start(50);
}

void ProcessController::test()
{
    QList<QString> names = {"Hoover 200 Cleaner", "Thermometerc C", "LG Air Conditioner", "SecuroServ", "Lamp", "Lamp", "Siemens Water Heater"};
    QList<float> low =     {0, 0, -15, 0, 0, 0, 15};
    QList<float> high =    {1, 1, 25, 1, 10, 10, 60};
    QList<float> delta =   {1, 1, 1,  1, 0.5, 0.5, 1};
    QList<ComponentType> type {ComponentType::Switcher, ComponentType::Switcher, ComponentType::Slider, ComponentType::Switcher, ComponentType::Slider, ComponentType::Slider, ComponentType::Slider};


    RoomGroup room;
    room.setIndex(0);
    QString name = "All Components";
    room.setName(name);
    m_rooms.push_back(room);

    for(int i =0; i<names.length(); ++i){
        Component c;
        QString name = names[i];
        c.setName(name);
        c.setIndex(i + 1);
        c.setRoomIndex(0);
        c.setDelta(delta[i]);
        c.setLowPoint(low[i]);
        c.setHighPoint(high[i]);
        QList<QString> infoList;
        c.setInfo(infoList);
        QList<QTime> enableDate({QTime(1, 22, 0, 0), QTime(5, 30, 0, 0)});
        QList<QTime> disableDate({QTime(5, 22, 0, 0), QTime(5, 35, 0, 0)});
        c.setEnableAt(enableDate);
        c.setDisableAt(disableDate);
        c.setType(type[i]);
        c.setIsAuto(false);
        c.setEnabled(false);
        m_pendingComponents.append(c);
    }
}

void ProcessController::simulateSomeResults()
{
    for(auto& c : m_connectedComponents) {
        switch(c.type()){
        case ComponentType::Switcher:

            return;
        case ComponentType::Slider:
            return;
        default:
            return;
        }
    }
}
