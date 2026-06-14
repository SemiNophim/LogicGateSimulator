#pragma once
#include <QString>

class QGraphicsScene; 

class SaveManager {
public:
    static bool saveProject(const QString& filePath, QGraphicsScene* scene);
    static bool loadProject(const QString& filePath, QGraphicsScene* scene);
};

