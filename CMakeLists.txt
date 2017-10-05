cmake_minimum_required(VERSION 2.8)

project(intdump)

add_executable(intdump intdump.cpp)

install(
    FILES ${CMAKE_BINARY_DIR}/intdump
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    DESTINATION bin
)
