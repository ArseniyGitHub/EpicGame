if(LINUX OR WIN32)
  add_executable(max-client "main.cpp" "../../Engine/Game.cpp" "../../Engine/Scene/Scene.cpp" "../../Engine/Scene/GameScene.cpp" "../../Engine/Scene/MainMenuScene.cpp" "../../Engine/Entity/Entity.cpp" "../../Engine/Entity/Player.cpp" "../../Engine/Navigation/NavigationGrid.cpp")
  target_link_libraries(max-client PRIVATE raylib "${TORCH_LIBRARIES}")
  if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET max-client
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:max-client>)
  endif (MSVC)
elseif(ANDROID)
  add_library(max-client "main.cpp" "../../Engine/Game.cpp" "../../Engine/Scene/Scene.cpp" "../../Engine/Scene/GameScene.cpp" "../../Engine/Scene/MainMenuScene.cpp" "../../Engine/Entity/Entity.cpp" "../../Engine/Entity/Player.cpp" "../../Engine/Navigation/NavigationGrid.cpp")
  target_link_libraries(max-client PRIVATE android log raylib)
endif()

