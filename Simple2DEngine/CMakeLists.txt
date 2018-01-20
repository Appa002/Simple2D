cmake_minimum_required(VERSION 3.10)
project(Simple2DEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Simple2DEngine main.cpp header/singleton.h header/Engine.h header/stb_image.h src/Map.cpp header/Map.h header/GameObject.h header/Utils.h header/ExternalCodeLoadingWrapper.h src/MapManager.cpp header/MapManager.h src/stb_image.cpp src/GameObject.cpp)
target_link_libraries(Simple2DEngine SDL2)
target_link_libraries(Simple2DEngine GLEW)
target_link_libraries(Simple2DEngine GLU)
target_link_libraries(Simple2DEngine OpenGL)
target_link_libraries(Simple2DEngine lua)
target_link_libraries(Simple2DEngine dl)