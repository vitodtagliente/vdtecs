cmake_minimum_required(VERSION 3.2)
if(TARGET vdtecs)
	return()
endif()
project(vdtecs)

set(CMAKE_CXX_STANDARD 17)

file(GLOB PROJECT_HEADERS "include/vdtecs/*.h") 
file(GLOB PROJECT_SOURCES "source/*.cpp")

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_library(
    ${PROJECT_NAME} 
	STATIC
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

target_include_directories(${PROJECT_NAME} PUBLIC include)