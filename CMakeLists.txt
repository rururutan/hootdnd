cmake_minimum_required(VERSION 3.10)
project(hootdnd C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")

set(SRC src/hootdnd.c)
set(RC src/resource.rc)
set(MANIFEST src/hootdnd.manifest)

add_executable(hootdnd ${SRC} ${RC} ${MANIFEST})

target_link_libraries(hootdnd PRIVATE shlwapi)
set_target_properties(hootdnd PROPERTIES WIN32_EXECUTABLE TRUE)

