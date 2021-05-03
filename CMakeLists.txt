cmake_minimum_required(VERSION 3.15)
project(wkJellyWorm)

set(CMAKE_CXX_STANDARD 17)


set(PRE_CONFIGURE_FILE "cmake/git.cc.in")
set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/git.cc")
include(cmake/git_watcher.cmake)

# Create a library out of the compiled post-configure file.
add_library(git STATIC ${POST_CONFIGURE_FILE})
target_include_directories(git PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(git check_git)

add_library(hacklib STATIC
        lib/hacklib/ExeFile.cpp lib/hacklib/ExeFile_WIN32.cpp
        lib/hacklib/PatternScanner.cpp lib/hacklib/Memory_WIN32.cpp
        )

link_directories(lib)
include_directories(include cmake)
add_definitions(-DGLEW_STATIC)
add_library(wkJellyWorm SHARED
        src/dllmain.cpp
        src/DevConsole.cpp src/DevConsole.h
        include/sigscanner.h include/json.hpp include/args.hxx
        include/forward.hpp include/sol.hpp
        src/Hooks.cpp src/Hooks.h
        src/Constants.h
        src/entities/Entities.h
        src/Lobby.cpp src/Lobby.h
        src/Config.cpp src/Config.h
        src/Game.cpp src/Game.h
        src/Chat.cpp src/Chat.h
        src/Landscape.cpp src/Landscape.h

        src/CustomWeapons.cpp src/CustomWeapons.h
        src/Packets.cpp src/Packets.h
        src/Lua.cpp src/Lua.h
        src/packages/Package.cpp src/packages/Package.h
        src/packages/PackageManager.cpp src/packages/PackageManager.h
        src/Utils.cpp src/Utils.h

        src/entities/CTask.cpp src/entities/CTask.h
        src/entities/CGameTask.cpp src/entities/CGameTask.h

        src/entities/tasks/CTaskTurnGame.cpp src/entities/tasks/CTaskTurnGame.h
        src/entities/tasks/CTaskTeam.cpp src/entities/tasks/CTaskTeam.h
        src/entities/tasks/CTaskFire.cpp src/entities/tasks/CTaskFire.h
        src/entities/tasks/CTaskFlame.cpp src/entities/tasks/CTaskFlame.h
        src/entities/tasks/CTaskFilter.cpp src/entities/tasks/CTaskFilter.h
        src/entities/tasks/CTaskAirStrike.cpp src/entities/tasks/CTaskAirStrike.h
        src/entities/tasks/CTaskSpriteAnimation.cpp src/entities/tasks/CTaskSpriteAnimation.h
        src/entities/tasks/CTaskSmoke.cpp src/entities/tasks/CTaskSmoke.h
        src/entities/tasks/CTaskGass.cpp src/entities/tasks/CTaskGass.h
        src/entities/tasks/CTaskCPU.cpp src/entities/tasks/CTaskCPU.h
        src/entities/tasks/CTaskCloud.cpp src/entities/tasks/CTaskCloud.h
        src/entities/tasks/CTaskDirt.cpp src/entities/tasks/CTaskDirt.h
        src/entities/tasks/CTaskFireBall.cpp src/entities/tasks/CTaskFireBall.h
        src/entities/tasks/CTaskScoreBubble.cpp src/entities/tasks/CTaskScoreBubble.h
        src/entities/tasks/CTaskSeaBubble.cpp src/entities/tasks/CTaskSeaBubble.h

        src/entities/gametasks/CTaskArrow.cpp src/entities/gametasks/CTaskArrow.h
        src/entities/gametasks/CTaskWorm.cpp src/entities/gametasks/CTaskWorm.h
        src/entities/gametasks/CTaskMissile.cpp src/entities/gametasks/CTaskMissile.h
        src/entities/gametasks/CTaskLand.cpp src/entities/gametasks/CTaskLand.h
        src/entities/gametasks/CTaskCanister.cpp src/entities/gametasks/CTaskCanister.h
        src/entities/gametasks/CTaskCrate.cpp src/entities/gametasks/CTaskCrate.h
        src/entities/gametasks/CTaskCross.cpp src/entities/gametasks/CTaskCross.h
        src/entities/gametasks/CTaskOildrum.cpp src/entities/gametasks/CTaskOildrum.h
        src/entities/gametasks/CTaskMine.cpp src/entities/gametasks/CTaskMine.h
        src/entities/gametasks/CTaskOldWorm.cpp src/entities/gametasks/CTaskOldWorm.h

        src/Sounds.cpp src/Sounds.h
        src/Sprites.cpp src/Sprites.h
        src/WaLibc.cpp src/WaLibc.h
        src/Explosions.cpp src/Explosions.h
        src/Weapons.cpp src/Weapons.h
        src/renderer/Bitmap.cpp src/renderer/Bitmap.h
        src/renderer/Renderer.cpp src/renderer/Renderer.h
        src/renderer/Palette.cpp src/renderer/Palette.h src/renderer/BitmapExtension.cpp src/renderer/BitmapExtension.h src/renderer/Drawing.cpp src/renderer/Drawing.h)

set_property(TARGET wkJellyWorm git hacklib PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
target_link_libraries(wkJellyWorm hacklib libMinHook-x86-v141-mt git lua53 glew32s glu32 opengl32 capstone Polyhook_2)
