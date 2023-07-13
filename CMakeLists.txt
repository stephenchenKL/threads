cmake_minimum_required(VERSION 3.16)

set(APP_NAME threads)
set(CMAKE_BUILD_TYPE Debug)
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
