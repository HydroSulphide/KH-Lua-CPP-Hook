cmake_minimum_required(VERSION 3.7...3.27)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(KH-Lua-CPP-Hook LANGUAGES CXX ASM)

set(PROGRAM_VERSION "" CACHE STRING "Program version override")

option(WIL_BUILD_TESTS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# FetchContent for dependencies
FetchContent_Declare(wil
    GIT_REPOSITORY https://github.com/microsoft/wil.git
    GIT_TAG        8501377980a52d98d1b51d04f60f571a7f0dc3db)

FetchContent_Declare(tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG        d8fa9a1fddc90254cac2366dde23f0b613bc1280)

FetchContent_Declare(DiscordRPC
    GIT_REPOSITORY https://github.com/discord/discord-rpc.git
    GIT_TAG        963aa9f3e5ce81a4682c6ca3d136cddda614db33)

FetchContent_Declare(rapidjson
    GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
    GIT_TAG        master
)

FetchContent_MakeAvailable(wil tomlplusplus DiscordRPC rapidjson)
target_include_directories(discord-rpc PRIVATE ${rapidjson_SOURCE_DIR}/include)


# Lua subproject
add_subdirectory(external/subproject/lua544)

set(SOURCE
    "src/hook/main_dll.cpp"
    "src/hook/config.cpp"
    "src/hook/header_text.cpp"
    "src/hook/console_lib.cpp"
    "src/hook/input.cpp"

    "src/discord/discord_instance.cpp"

    "src/lua/lua_exec.cpp"
    "src/lua/lua_backend.cpp"

    "src/cpp/cpp_handler.cpp"
    "src/cpp/api/kh_characters.cpp"   
    "src/cpp/events/event_hook.cpp" 
    
    "src/cpp/api/kh_gameobject.cpp"
    
    "include/extra/wil_extra.h"

    "include/hook/config.h"
    "include/hook/game_info.h"
    "include/hook/header_text.h"
    "include/hook/console_lib.h"
    "include/hook/memory_lib.h"
    "include/hook/input.h"

    "include/discord/discord_instance.h"

    "include/lua/lua_exec.h"
    "include/lua/lua_backend.h"

    "include/cpp/cpp_handler.h"
    "include/cpp/api/kh_characters.h"
    "include/cpp/events/event_hook.h"
    
    "include/cpp/api/kh_gameobject.h"
)

add_custom_target(clang-format
    COMMAND clang-format -i -style=file ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(build-info
    COMMAND ${CMAKE_COMMAND}
        -DPROGRAM_VERSION:STRING=${PROGRAM_VERSION}
        -DINSTALL_DIR:STRING=${CMAKE_CURRENT_BINARY_DIR}
        -P CMake/BuildInfo.cmake
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    VERBATIM
)

add_library(DBGHELP SHARED ${SOURCE})
add_dependencies(DBGHELP build-info)

if(MSVC)
    target_compile_options(DBGHELP PRIVATE /std:c++latest -W4 -WX -DZTD_STD_LIBRARY_RANGES=0)
else()
    target_compile_options(DBGHELP PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_features(DBGHELP PRIVATE cxx_std_20)
target_compile_definitions(DBGHELP PRIVATE -DUNICODE -D_UNICODE)
target_include_directories(DBGHELP PRIVATE
    include/
    include/cpp
    include/cpp/api
    include/cpp/events
    include/lua
    include/hook
    include/discord
    include/extra
    external/include
    external/subproject/lua544
    ${DiscordRPC_SOURCE_DIR}/include
    ${rapidjson_SOURCE_DIR}/include  # Add RapidJSON include directory
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_link_libraries(DBGHELP PRIVATE
    WIL
    tomlplusplus::tomlplusplus
    lua54
    discord-rpc
)

unset(PROGRAM_VERSION CACHE)

add_custom_target(
    RunCompileMods ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Running batch script to compile mods..."
    COMMAND ${CMAKE_COMMAND} -E echo "Current Directory: ${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH}" cmd /c compile_mods.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Executing compile_mods.bat"
    VERBATIM
)

add_custom_target(
    RunCopyOutput ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Running batch script to copy compiled mods and DBGHELP.dll to the game directory..."
    COMMAND ${CMAKE_COMMAND} -E echo "Current Directory: ${CMAKE_SOURCE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E env "PATH=$ENV{PATH}" cmd /c copy_output_files.bat
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Executing copy_output_files.bat"
    VERBATIM
)

add_dependencies(RunCopyOutput RunCompileMods)
add_dependencies(RunCompileMods DBGHELP)
add_dependencies(RunCopyOutput DBGHELP)
