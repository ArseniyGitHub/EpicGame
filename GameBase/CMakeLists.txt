# CMakeList.txt: проект CMake для GameBase; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

if(ANDROID)
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  string(REGEX MATCH "android-([0-9]+)" _ ${ANDROID_PLATFORM} FORCE)
  set(ANDROID_API_VERSION ${CMAKE_MATCH_1} CACHE STRING "" FORCE)
  set(ANDROID_ARCH ${CMAKE_ANDROID_ARCH} CACHE STRING "" FORCE)
  set(PLATFORM "Android" CACHE STRING "" FORCE)
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
endif()

add_subdirectory("Client")
add_subdirectory("Server")
add_subdirectory("Engine")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
