//
// Created by albert on 1/9/18.
//

#ifndef SIMPLE2D_MAPMANAGER_H
#define SIMPLE2D_MAPMANAGER_H

#include "singleton.h"
#include "Map.h"

namespace Simple2D{
    class MapManager: public Simple2D::Singleton<MapManager> {
    private:
        Map* curMap;


    public:
        Map* getCurrentMap();

        int loadMap(std::string path);
        int unloadMap();
    };
}



#endif //SIMPLE2D_MAPMANAGER_H
