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


#client side
include_directories(client client/includes)
add_executable(client client/main.cpp)
target_link_libraries(client ${Boost_LIBRARIES} SDL2::Main)


#server side
include_directories(server server/includes)
add_executable(server server/main.cpp)
target_link_libraries(server ${Boost_LIBRARIES})