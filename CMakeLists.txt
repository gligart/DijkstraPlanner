cmake_minimum_required(VERSION 2.8.3)
project(distancemap)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-O3 ")
find_package(OpenCV REQUIRED)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR})

add_library(distancemap src/libs/distancemaplib.cpp src/libs/distancemaplib.h)
target_link_libraries(distancemap ${OpenCV_LIBS})

add_library(baseplanner src/libs/baseplannerlib.cpp src/libs/baseplannerlib.h)
target_link_libraries(baseplanner ${OpenCV_LIBS} distancemap)

#add_executable(planning src/planning.cpp )
#target_link_libraries(planning distancemap baseplanner)

#add_executable(clickplan src/clickplan.cpp )
#target_link_libraries(clickplan distancemap baseplanner)

add_executable(dmap src/distancemap.cpp )
target_link_libraries(dmap  distancemap baseplanner ${OpenCV_LIBS})
