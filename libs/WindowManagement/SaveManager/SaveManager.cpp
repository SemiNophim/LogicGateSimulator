#include "SaveManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "Element.h"
#include "PowerElement.h"
#include "Wire.h"

#include "DCPower.h"
#include "LED.h"
#include "Ground.h"

bool SaveManager::saveProject(const QString& filePath, QGraphicsScene* scene) {
    if (!scene || filePath.isEmpty()) return false;

    QJsonObject rootObject;

    QJsonArray elementsArray;

    for (QGraphicsItem* item : scene->items()) {
        if (Element* el = dynamic_cast<Element*>(item)) {
            QJsonObject elObject;
            
            elObject["id"] = static_cast<qint64>(reinterpret_cast<quintptr>(el));
            elObject["type"] = elementTypeToString(el->getElementType());
            elObject["x"] = el->x();
            elObject["y"] = el->y();

            if (PowerElement* power = dynamic_cast<PowerElement*>(el)) {
                elObject["customValue"] = power->getOutputVoltage();
            } else {
                elObject["customValue"] = 0.0;
            }

            QJsonArray pinsArray;
            for (const Pin& pin : el->getPins()) {
                QJsonObject pinObj;
                pinObj["pinId"] = pin.id;
                pinObj["type"] = static_cast<int>(pin.type);
                pinsArray.append(pinObj);
            }
            elObject["pins"] = pinsArray;

            elementsArray.append(elObject);
        }
    }
    rootObject["elements"] = elementsArray;

    QJsonArray wiresArray;
    for (QGraphicsItem* item : scene->items()) {
        if (Wire* wire = dynamic_cast<Wire*>(item)) {
            Pin* pA = wire->startPin();
            Pin* pB = wire->endPin();

            if (pA && pB) {
                QJsonObject wireObject;
                wireObject["startPinId"] = pA->id;
                wireObject["endPinId"] = pB->id;
                wiresArray.append(wireObject);
            }
        }
    }
    rootObject["wires"] = wiresArray;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonDocument doc(rootObject);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool SaveManager::loadProject(const QString& filePath, QGraphicsScene* scene) {
    if (!scene || filePath.isEmpty()) return false;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) return false;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) return false;

    QJsonObject rootObject = doc.object();

    scene->clear(); 

    std::map<int, Pin*> pinMap;

    QJsonArray elementsArray = rootObject["elements"].toArray();
    for (QJsonValue ref : elementsArray) {
        QJsonObject elObj = ref.toObject();
        QString typeStr = elObj["type"].toString();
        qreal x = elObj["x"].toDouble();
        qreal y = elObj["y"].toDouble();
        float customValue = elObj["customValue"].toDouble();

        Element* newEl = nullptr;
        if (typeStr == "DCPower") {
            DCPower* power = new DCPower();
            newEl = power;
        } 
        else if (typeStr == "LED") {
            newEl = new LED();
        } 
        else if (typeStr == "Ground") {
            newEl = new Ground();
        }

        if (newEl) {
            newEl->setPos(x, y);
            newEl->setFlag(QGraphicsItem::ItemIsMovable, true);
            newEl->setFlag(QGraphicsItem::ItemIsSelectable, true);

            scene->addItem(newEl); 

            QJsonArray pinsArray = elObj["pins"].toArray();
            auto& newPins = newEl->getPins(); 

            for (int i = 0; i < pinsArray.size() && i < (int)newPins.size(); ++i) {
                QJsonObject pinObj = pinsArray[i].toObject();
                int oldPinId = pinObj["pinId"].toInt();
                
                pinMap[oldPinId] = &newPins[i];
            }
        }
    }

    QJsonArray wiresArray = rootObject["wires"].toArray();
    for (QJsonValue ref : wiresArray) {
        QJsonObject wireObj = ref.toObject();
        int startPinId = wireObj["startPinId"].toInt();
        int endPinId = wireObj["endPinId"].toInt();

        if (pinMap.find(startPinId) != pinMap.end() && pinMap.find(endPinId) != pinMap.end()) {
            Pin* pinA = pinMap[startPinId];
            Pin* pinB = pinMap[endPinId];

            Wire* newWire = new Wire(pinA, pinB);
            scene->addItem(newWire);

            pinA->connectedWires.push_back(newWire);
            pinB->connectedWires.push_back(newWire);
            
            newWire->updatePath(); 
        }
    }

    return true;
}

