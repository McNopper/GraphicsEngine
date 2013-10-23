#
# GE_Test03 CMake file
#
# (c) Norbert Nopper
# 

cmake_minimum_required(VERSION 2.6)

project(GE_Test03)

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
	
	include_directories(${GE_Test03_SOURCE_DIR}/../External/${ENV_DIR}/include ${GE_Test03_SOURCE_DIR}/../GLUS/src ${GE_Test03_SOURCE_DIR}/../GraphicsEngine/src "C:/Program Files/Autodesk/FBX/Fbx Sdk/2014.1/include" "C:/Development/Libraries/cpp/boost_1_53_0" "C:/Development/Libraries/cpp/devil_1_7_8/include")	
	
	link_directories(${GE_Test03_SOURCE_DIR}/../GLUS ${GE_Test03_SOURCE_DIR}/../GraphicsEngine ${GE_Test03_SOURCE_DIR}/../External/${ENV_DIR}/lib "C:/Development/Libraries/cpp/boost_1_53_0/lib32" "C:/Development/Libraries/cpp/devil_1_7_8/lib" "C:/Program Files/Autodesk/FBX/FBX SDK/2014.1/lib/vs2010/x86/")
	
ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GE_Test03_SOURCE_DIR}/../GE_Binaries)

# Source files
file(GLOB_RECURSE CPP_FILES ${GE_Test03_SOURCE_DIR}/src/*.cpp)

# Header files
file(GLOB_RECURSE H_FILES ${GE_Test03_SOURCE_DIR}/src/*.h)

add_executable(GE_Test03 ${CPP_FILES} ${H_FILES})
	
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# Windows
	
	target_link_libraries(GE_Test03 GLUS GraphicsEngine glfw3 glew32s opengl32 gdi32 user32 Advapi32 wininet DevIL ILU libfbxsdk-md.lib)
			
	message("Executable is deployed either to GE_Binaries/Release or GE_Binaries/Debug.")
	message("Copy the executable to the GE_Binaries folder.")
	message("CMAKE_RUNTIME_OUTPUT_DIRECTORY is set to GE_Binaries, but Release/Debug is appended.")
					
ENDIF()
