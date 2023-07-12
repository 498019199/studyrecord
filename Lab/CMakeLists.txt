project(labTEST)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_POSITION_INDEPENDENT_CODE on)
#SET(CMAKE_OPTION "-rdynamic -Wno-deprecated -fstack-protector-all ")
set(CMAKE_CXX_FLAGS "-m64 -O0 -std=c++20 -g -ggdb -Wall -pthread -fcoroutines")
set(CMAKE_CXX_FLAGS_RELEASE "-m64 -O2 -std=c++20 -Wall -pthread -fcoroutines")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_3RD_DIR ${PROJECT_SOURCE_DIR}/3rd)
message(${PROJECT_SOURCE_DIR})

add_subdirectory(task)
file(COPY ${PROJECT_SOURCE_DIR}/task/include DESTINATION "${LIBRARY_OUTPUT_PATH}")

add_subdirectory(common)
