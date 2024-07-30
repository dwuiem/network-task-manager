cmake_minimum_required(VERSION 3.27)
project(networking)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.85.0 REQUIRED)

file(GLOB SOURCES src/*)

add_library(${PROJECT_NAME} ${SOURCES}
        src/server/server.cpp
        include/server/server.h
        src/server/connection.cpp
        include/server/connection.h
        src/client/client.cpp
        include/client/client.h
        src/client/user_interface.cpp
        include/client/user_interface.h
        src/client/application.cpp
        include/client/application.h
        src/server/event_handler.cpp
        include/server/event_handler.h
        src/server/session.cpp
        include/server/session.h
        src/server/user.cpp
        include/server/user.h
        src/server/task.cpp
        include/server/task.h
        src/server/session_authorization.cpp
        include/server/session_authorization.h
        src/server/user_storage.cpp
        include/server/user_storage.h
        src/server/command_handler.cpp
        include/server/command_handler.h
        src/server/message_sender.cpp
        include/server/message_sender.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${Boost_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} ws2_32)
target_link_libraries(${PROJECT_NAME} wsock32)

add_definitions(-D_WIN32_WINNT=0x0601)