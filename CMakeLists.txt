project(libcec-daemon)
cmake_minimum_required(VERSION 2.8)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "0.9")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

configure_file(${PROJECT_SOURCE_DIR}/cmake/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Threads)
find_package(Boost COMPONENTS thread system program_options chrono)
find_package(Cec)
find_package(Log4cplus)

file(GLOB libcec-daemon_SOURCES ${PROJECT_SOURCE_DIR}/src/*cpp)
add_executable(libcec-daemon ${libcec-daemon_SOURCES})
target_link_libraries(libcec-daemon ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${LOG4CPLUS_LIBRARIES} ${Cec_LIBRARIES} ${CMAKE_DL_LIBS})

