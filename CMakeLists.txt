cmake_minimum_required(VERSION 2.8)

project(typedump)

add_executable(typedump   typedump.cpp)
add_executable(typegen    typegen.cpp)
add_executable(typesearch typesearch.cpp)

install(
  FILES ${CMAKE_BINARY_DIR}/typedump ${CMAKE_BINARY_DIR}/typegen ${CMAKE_BINARY_DIR}/typesearch
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
  DESTINATION bin
)

