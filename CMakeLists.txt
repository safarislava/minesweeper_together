cmake_minimum_required(VERSION 3.25)

project(server)
set(CMAKE_CXX_STANDARD 17)
add_executable(server server.cpp)

project(client)
set(CMAKE_CXX_STANDARD 17)
link_libraries(ws2_32 wsock32)
set(CMAKE_MODULE_PATH ../cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
add_executable(client client.cpp)
target_link_libraries(client ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -static-libstdc++ -static-libgcc)

