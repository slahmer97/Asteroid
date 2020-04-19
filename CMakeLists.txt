cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Asteroid)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(my_libs)


ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# FOR BOOST CHECK THIS TO GET SAME VERSION ^_^
# https://www.osetc.com/en/how-to-install-boost-on-ubuntu-16-04-18-04-linux.html
find_package(Boost 1.58 COMPONENTS program_options log REQUIRED)

find_package(websocketpp)
set(CLIENT_SOURCE_PATH client_sources/)
set(SERVER_SOURCE_PATH server_sources/)
set(SHARED_SOURCE_PATH shared_sources/)
set(SIMPLE_WEBSOCKET my_libs/Simple-WebSocket-Server)
include_directories(CLIENT_HEADER_FILES_I client_sources/headers)
include_directories(SERVER_HEADER_FILES_I server_sources/headers)
include_directories(SHARED_HEADER_FILES_I shared_sources/headers)
include_directories(WEBSOCKET my_libs/Simple-WebSocket-Server)

set(CLIENT_SOURCE_FILES
        ${CLIENT_SOURCE_PATH}/asteroid_client.cpp
        ${CLIENT_SOURCE_PATH}/rest_client.cpp
        server_sources/headers/polyServeur.h server_sources/headers/asteroid.h server_sources/headers/grandAsteroid.h server_sources/headers/moyenAsteroid.h server_sources/headers/petitAsteroid.h server_sources/headers/vaisseau.h server_sources/headers/laser.h)

set(SERVER_SOURCE_FILES
        ${SERVER_SOURCE_PATH}/asteroid_server.cpp
        ${SERVER_SOURCE_PATH}/vec2d.cpp
        ${SERVER_SOURCE_PATH}/rest_server.cpp
        )
set(SHARED_SOURCE_FILES
        )

#client side
add_executable(Asteroid_client client_sources/asteroid_client.cpp ${CLIENT_SOURCE_FILES} ${CLIENT_HEADER_FILES_I} ${WEBSOCKET})
target_link_libraries(Asteroid_client
        ${Boost_LIBRARIES}
        SDL2
        boost_system
        crypto
        ssl
        -lSDL2_ttf
        Boost::log_setup
        Boost::log
       )


#server side
add_executable(Asteroid_server server_sources/asteroid_server.cpp ${SERVER_SOURCE_FILES} ${SERVER_HEADER_FILES_I} ${WEBSOCKET})
target_link_libraries(Asteroid_server
        ${Boost_LIBRARIES}
        boost_system
        crypto
        ssl
        Boost::log_setup
        Boost::log
        )
