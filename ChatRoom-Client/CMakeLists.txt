cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME "ChatRoom-Client")  # 定义项目名称
message(STATUS "Configuring project: ${PROJECT_NAME}")

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

# C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Setting up Qt configurations")
# 启用 Qt 自动处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

# 设置 Qt6 路径
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")
message(STATUS "Qt6 path set to: ${CMAKE_PREFIX_PATH}")

# 查找所需的 Qt6 组件
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Network HttpServer)
message(STATUS "Qt6 components found")

# 添加源文件
message(STATUS "Adding source files")



set(MAINFILE 
    main.cpp 
)
set(MAINWINDOW
    modules/mainwindow/include/mainwindow.h
    modules/mainwindow/src/mainwindow.cpp
)

set(CHAT_ROOM
    modules/chatroom/include/chatroom.h
    modules/chatroom/src/chatroom.cpp
    modules/chatroom/include/chattextedit.h
    modules/chatroom/src/chattextedit.cpp
)
set(NETWORK_DATA_MANAGER
    modules/network_data_manager/include/network_data_manager.h
    modules/network_data_manager/src/network_data_manager.cpp
    modules/network_data_manager/include/message_data.h
)
set(GAME_SCREEN
    modules/game_screen/include/game_screen.h
    modules/game_screen/src/game_screen.cpp
    modules/game_screen/include/code_card.h
    modules/game_screen/src/code_card.cpp
    modules/game_screen/include/card_color.h
)
set(GAME_CORE
    modules/game_core/include/game_core.h
    modules/game_core/src/game_core.cpp 
    modules/game_core/include/candidate_words.h
)

# 添加 UI 文件
set(UI_FILES
    modules/mainwindow/ui/mainwindow.ui
    modules/chatroom/ui/chatroom.ui
    modules/game_screen/ui/game_screen.ui
)
set(RESOURCE_FILES
    resources/resources.qrc
)
 
 
# 明确指定 UI 文件的处理
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

message(STATUS "UI files: ${UI_FILES}")
message(STATUS "Generated UI headers: ${UI_HEADERS}")

# 创建可执行文件
add_executable(${PROJECT_NAME}
    ${MAINFILE}
    ${MAINWINDOW}
    ${CHAT_ROOM}
    ${NETWORK_DATA_MANAGER}
    ${RESOURCE_FILES} 
    ${GAME_CORE}
    ${GAME_SCREEN}
    ${UI_FILES}
    # ${UI_HEADERS}  # 确保包含生成的 UI 头文件
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Widgets 
    Qt6::Network 
    Qt6::HttpServer
) 

# 设置包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/mainwindow/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/game_core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/game_screen/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/chatroom/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/network_data_manager/include
    ${CMAKE_CURRENT_BINARY_DIR}  # 包含生成的 UI 头文件
)

# 设置可执行文件的输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
# 确保 UI 头文件被正确生成
# add_custom_target(generate_ui_headers DEPENDS ${UI_HEADERS})
# add_dependencies(${PROJECT_NAME} generate_ui_headers)
# 根据编译模式设置不同的编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE "-g")  # 启用调试符号
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE "-O3") # 启用优化
endif()

# 复制 Qt DLL 和平台插件到输出目录 (仅在 Windows 上)
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_PREFIX_PATH}/bin/windeployqt.exe
            --qmldir ${CMAKE_SOURCE_DIR}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_NAME:${PROJECT_NAME}>
    )
endif()

message(STATUS "CMake configuration completed")