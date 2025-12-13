# CMakeList.txt: проект CMake для GameBase; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.

# cmake_minimum_required (VERSION 3.16)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
project ("GameBase")

set(BUILD_SHARED_LIBS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ENET_TEST OFF CACHE BOOL "" FORCE)
set(ENET_SHARED ON CACHE BOOL "" FORCE)
set(ENET_STATIC OFF CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
  add_compile_definitions(ENET_DLL)
endif()

set(RAYGUI_EXTERNAL_INCLUDE "External/raygui")
set(RAYLIB_INCLUDE "External/raylib")
set(ENET_EXTERNAL_INCLUDE "External/enet/include")
set(JSON_EXTERNAL_INCLUDE "External/json")

if(ANDROID)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  string(REGEX MATCH "android-([0-9]+)" _ ${ANDROID_PLATFORM} FORCE)
  set(ANDROID_API_VERSION ${CMAKE_MATCH_1} CACHE STRING "" FORCE)
  set(ANDROID_ARCH ${CMAKE_ANDROID_ARCH} CACHE STRING "" FORCE)
  set(PLATFORM "Android" CACHE STRING "" FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
endif()


add_subdirectory("External/enet")
add_subdirectory("External/json")
add_subdirectory("External/raylib")
# add_subdirectory("External")

# add_subdirectory("Engine")
# add_subdirectory("Client")
# add_subdirectory("Server")

add_subdirectory("Test/01")






# TODO: Добавьте тесты и целевые объекты, если это необходимо.
