cmake_minimum_required(VERSION 3.10)
project(DiscordRichPresence C)

set(CMAKE_C_STANDARD 99)

# Definir caminho do SDK do Discord RPC
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(DISCORD_SDK_PATH "${CMAKE_SOURCE_DIR}/discord_sdk/win64-dynamic")
    else()
        set(DISCORD_SDK_PATH "${CMAKE_SOURCE_DIR}/discord_sdk/win32-dynamic")
    endif()
    set(DISCORD_LIB discord-rpc.lib)  # Usar o arquivo de importação, NÃO a DLL
elseif(UNIX)
    set(DISCORD_SDK_PATH "${CMAKE_SOURCE_DIR}/discord_sdk/linux-dynamic")
    set(DISCORD_LIB discord-rpc)  # Sem extensão para facilitar compatibilidade
endif()

# Incluir diretórios de headers do Discord RPC
include_directories(${DISCORD_SDK_PATH}/include)

# Adicionar diretórios de bibliotecas
link_directories(${DISCORD_SDK_PATH}/lib)

# Criar o executável
add_executable(DiscordRichPresence src/main.c)

# Linkar as bibliotecas necessárias
target_link_libraries(DiscordRichPresence ${DISCORD_LIB})
