cmake_minimum_required(VERSION 2.8)

project(typedump)

add_executable(typedump typedump.cpp)

install(
    FILES ${CMAKE_BINARY_DIR}/typedump
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    DESTINATION bin
)
