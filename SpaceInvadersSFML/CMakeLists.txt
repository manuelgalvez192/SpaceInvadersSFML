cmake_minimum_required(VERSION 3.19)
project(SfmlWithCMake VERSION 1.0)
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)

set(PROJECT_HEADERS 
include/Enemies.h
include/Bullets.h
include/BulletsEnemy.h
include/Player.h
include/GameController.h
include/LevelController.h
include/Values.h
)

set(PROJECT_SOURCES 
main.cpp
source/Enemies.cpp
source/Bullets.cpp
source/BulletsEnemy.cpp
source/Player.cpp
source/GameController.cpp
source/LevelController.cpp
)

set(PROJECT_IMAGES
data/images/spaceInvadersShip.png
data/images/invader.png
data/font/ARCADE.TTF
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
  ${PROJECT_IMAGES}
)

include_directories(${PROJECT_NAME} PRIVATE include )

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
 SfmlWithCMake
 main.cpp
 ${PROJECT_FILES}
)

target_link_libraries(
 SfmlWithCMake
 sfml-graphics
)