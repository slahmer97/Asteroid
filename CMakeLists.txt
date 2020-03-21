cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Asteroid)

# FOR BOOST CHECK THIS TO GET SAME VERSION ^_^
# https://www.osetc.com/en/how-to-install-boost-on-ubuntu-16-04-18-04-linux.html
find_package(Boost 1.58 COMPONENTS program_options REQUIRED)


#FOR SDL 2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)

#For cpprest https://github.com/microsoft/cpprestsdk
find_library( LIB_CPP_REST cpprest )
if(${LIB_CPP_REST} STREQUAL "LIB_CPP_REST-NOTFOUND")
    message(FATAL_ERROR "Couldn't find the 'libcpprest' library")
endif()


#client side
include_directories(client client/includes)
add_executable(client client/main.cpp client/client_message_factory.h)
target_link_libraries(client ${Boost_LIBRARIES} SDL2::Main  boost_system crypto ssl ${LIB_CPP_REST} SDL2_ttf)


#server side
include_directories(server server/includes)
add_executable(server server/main.cpp server/game.h server/games_scheduler.h
        server/http_service_handler.h server/stdafx.h)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES} boost_system crypto ssl ${LIB_CPP_REST}  )

