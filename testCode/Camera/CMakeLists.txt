cmake_minimum_required(VERSION 3.0)
project(CameraGameObject)

set(CMAKE_CXX_STANDARD 17)

ADD_COMPILE_OPTIONS()

add_library(CameraGameObject SHARED index.cpp ../../Simple2DEngine/header/Simple2D.h
        ../../Simple2DEngine/src/Simple2D.cpp ../../Simple2DEngine/header/types.h
        ../../Simple2DEngine/src/GameObject.cpp ../../Simple2DEngine/header/singleton.h
        ../../Simple2DEngine/header/Engine.h ../../Simple2DEngine/src/Map.cpp ../../Simple2DEngine/header/Map.h
        ../../Simple2DEngine/header/GameObject.h ../../Simple2DEngine/header/Utils.h ../../Simple2DEngine/header/ExternalCodeLoadingWrapper.h
        ../../Simple2DEngine/src/MapManager.cpp ../../Simple2DEngine/header/MapManager.h ../../Simple2DEngine/header/types.h)

set_target_properties(CameraGameObject PROPERTIES PREFIX "")
set_target_properties(CameraGameObject PROPERTIES OUTPUT_NAME "external")

add_custom_command(TARGET CameraGameObject
        POST_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/update.sh
        )