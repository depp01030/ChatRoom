cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "ChatRoom-Server")  # Define the project name variable

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt6 path
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# Use the variable for the executable name
add_executable(${PROJECT_NAME}
src/main.cpp
src/mainwindow.cpp
include/mainwindow.h
src/server_utils.cpp
include/server_utils.h 
src/mainwindow.ui
resources/resources.qrc
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Network) 


# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Set output directory for executables
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add different compile options based on Debug or Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE "-g")  # Enable debugging symbols
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE "-O3") # Enable optimizations
endif()

# Copy Qt DLLs and platform plugin to output directory (for Windows)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe
            --qmldir ${CMAKE_SOURCE_DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>
    )
endif()