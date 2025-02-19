cmake_minimum_required(VERSION 3.10)
project(DiscordRichPresence C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(DISCORD_SDK_PATH "${CMAKE_SOURCE_DIR}/libs/discord_sdk")
set(SAMEMORY_PATH "${CMAKE_SOURCE_DIR}/libs/samemory")

if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(DISCORD_SDK_PATH "${DISCORD_SDK_PATH}/win64-dynamic")
    else()
        set(DISCORD_SDK_PATH "${DISCORD_SDK_PATH}/win32-dynamic")
    endif()
    set(DISCORD_LIB discord-rpc.lib)
elseif(UNIX)
    set(DISCORD_SDK_PATH "${DISCORD_SDK_PATH}/linux-dynamic")
    set(DISCORD_LIB discord-rpc)
endif()

include_directories(${DISCORD_SDK_PATH}/include ${CMAKE_SOURCE_DIR}/libs/samemory ${CMAKE_SOURCE_DIR}/include)

link_directories(${DISCORD_SDK_PATH}/lib ${SAMEMORY_PATH}/lib)

add_executable(DiscordRichPresence 
    src/main.c 
    libs/samemory/process_utils.c 
    libs/samemory/addresses.c 
    libs/samemory/zones.c 
    libs/samemory/player_data.c 
    libs/samemory/weapons.c 
    libs/samemory/vehicles.c
)

if(WIN32)
    target_link_libraries(DiscordRichPresence ${DISCORD_LIB} ws2_32)
else()
    target_link_libraries(DiscordRichPresence ${DISCORD_LIB} pthread)
endif()
