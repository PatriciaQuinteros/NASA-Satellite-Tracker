cmake_minimum_required(VERSION 3.29.2)
project(SatelliteTrackingTool)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Add source files
file(GLOB SOURCES "src/*.cpp")

# Add executable based on the specified source files
add_executable(SatelliteTrackingTool src/main.cpp src/TLEParser.cpp)

target_include_directories(SatelliteTrackingTool PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Find CURL if you're using it
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(SatelliteTrackingTool ${CURL_LIBRARIES})
endif()