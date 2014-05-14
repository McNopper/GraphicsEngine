#
# GraphicsEngine CMake file
#
# (c) Norbert Nopper
# 

cmake_minimum_required(VERSION 2.6)

project(GraphicsEngine)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Windows
	
	add_definitions(-DFBXSDK_NEW_API)
	
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-wd4396)
	
	SET(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -D_ITERATOR_DEBUG_LEVEL=2")
	SET(CMAKE_CXX_FLAGS_RELEASE "-D_RELEASE -D_ITERATOR_DEBUG_LEVEL=0")
	
	SET(Processor "x86")
	SET(OperatingSystem "Windows")
	SET(Compiler "MSVC")
	
	set(ENV_DIR ${Processor}/${OperatingSystem}/${Compiler})
	
	include_directories(${GraphicsEngine_SOURCE_DIR}/../External/${ENV_DIR}/include ${GraphicsEngine_SOURCE_DIR}/../GLUS/src "C:/Program Files/Autodesk/FBX/Fbx Sdk/2015.1/include" "C:/Development/Libraries/cpp/boost_1_55_0" "C:/Development/Libraries/cpp/devil_1_7_8/include")	
		
ENDIF()

list(APPEND IGNORE_CPP_FILES	${GraphicsEngine_SOURCE_DIR}/src/layer1/texture/TextureFactory_GLUS.cpp
)

# Source files
file(GLOB_RECURSE CPP_FILES ${GraphicsEngine_SOURCE_DIR}/src/*.cpp)

list(REMOVE_ITEM CPP_FILES ${IGNORE_CPP_FILES})

# Header files
file(GLOB_RECURSE H_FILES ${GraphicsEngine_SOURCE_DIR}/src/*.h)

add_library(GraphicsEngine ${CPP_FILES} ${H_FILES})
