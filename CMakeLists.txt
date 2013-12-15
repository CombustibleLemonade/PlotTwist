cmake_minimum_required(VERSION 2.8)
# Project Name
PROJECT(HW_OPENGL)

#Extending the module database
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)
#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# Find GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

#########################################################
# Include Files
#########################################################
include_directories(${CMAKE_SOURCE_DIR}/Common)
add_executable(plotTwist 
	Main/main.cpp
	Common/File2String.h
        Common/File2String.cpp
        Common/CreateShaderProgram.h
        Common/CreateShaderProgram.cpp)

########################################################
# Linking & stuff
#########################################################

  # create the program "test"
  target_link_libraries(plotTwist
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${GLEW_LIBRARY}
    ${OPENAL_LIBRARY}
)
