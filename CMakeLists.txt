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




# FOR BOOST CHECK THIS TO GET SAME VERSION ^_^
# https://www.osetc.com/en/how-to-install-boost-on-ubuntu-16-04-18-04-linux.html
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)




#client side
include_directories(client client/includes)
add_executable(client client/main.cpp
                      client/client.cpp
                      client/client_message_factory.h
                      client/client.h
                      client/polygone.h
                      client/point.h
                      client/polyServeur.h
                      client/polyClient.h
                      client/affichable.h
                      client/alphaNumClient.h
                      client/client_http_service_handler.h
        )
target_link_libraries(client ${Boost_LIBRARIES} SDL2  boost_system crypto ssl cpprest -lSDL2_ttf)


#server side
include_directories(server server/includes)
add_executable(server server/main.cpp server/game.h server/games_scheduler.h
        server/server_http_service_handler.h server/stdafx.h)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} boost_system crypto ssl cpprest)
