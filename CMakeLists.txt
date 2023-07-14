cmake_minimum_required(VERSION 3.16)

set(APP_NAME threads)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
project(${APP_NAME} C CXX)


#####################################################
# Sources and headers
#####################################################
# Relative path to the project sources.
set (APP_SRC ".")  

#list the target source files
set(APP_SRC ${APP_SRC} 
    main.cpp
)

# build and link target executable
add_executable(${APP_NAME} ${APP_SRC})
