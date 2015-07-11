OpenGL 4 Graphics Engine:
-------------------------

How to build the Graphics Engine and the examples:

1. Install Eclipse IDE for C/C++ Developers and a GNU Compiler Collection for your operating system.
   For building with Visual C++ 2013, CMake and the Windows SDK 8.1 are needed. 
2. Import GLUS, GraphicsEngine, External and GE_Binaries as an existing project.   
3. Set the build configuration in Eclipse to your operating system.
4. Build GLUS.
5. Build GraphicsEngine.
6. Import an example as an existing project.
7. Set the build configuration of the example in Eclipse to your operating system.
8. Build the example.
9. The executable is located in the GE_Binaries folder.

If you get build errors:

- Please make sure, that you install all the needed header and libraries.
- Pre-build libraries are located in the External project folder. If you want, replace these libraries with your own build.
- The DevIL and the Autodesk FBX headers/libraries have to be installed separately. 
- Note: On Ubuntu 15.04, just use the libraries provided with the OS.

SDKs and Libraries:

- Autodesk FBX SDK 2015.1 http://usa.autodesk.com/fbx/
- DevIL 1.7.8 http://openil.sourceforge.net/
- GLEW 1.12.0 http://glew.sourceforge.net/
- GLFW 3.1.1 http://www.glfw.org/

Features (maybe incomplete):

- Primitive rendering of Sphere, Dome, Cube, Torus, Cylinder and Cone
- Model rendering out of FBX File
- Octree or list rendering
- Frustum culling
- Sorting of entities (for alpha blending etc.)
- Excluding of entities by a list
- Mouse/Key input and movement
- Phong with diffuse, specular, normal map and environment (static/dynamic) texture (reflection and refraction)
- Alpha blending
- Animation (Transform and Color)
- Skinning
- Entity instancing (CPU)
- Enabling/disabling of nodes
- Directional, point and spot light
- Perspective and orthographic cameras
- Overlay text output
- Debug: Frames per second
- Debug: Rendering of lines, planes, cubes and spheres
- Debug: Rendering of bounding sphere and octree nodes 
- Debug: Ground plane
- Multithreaded update loop
- Sky sphere and dome
- Post processing with MSAA, gamma correction, tone mapping (HDR), blur, bloom and depth of field (DOF)
- Render filter, that only transparent, opaque or all nodes should be rendered
- Animated paths (line, circle) for lights, cameras and entities
- Shadow and cascaded shadow mapping
- Ground rendering with displacement mapping

Build configuration naming:

[CPU]_[GPU]_[OS]_[OpenGL]_[Compiler]_[Configuration]

CPU:								ARMv6, ARMv7, x64, x86
GPU/Emulator (Optional):			AMD, ANGLE, Khronos, Mali, PowerVR, VC4, Vivante  
OS: 								Darwin, Linux, Windows
OpenGL/OpenGL ES/OpenVG (Optional):	GLES2, GLES3, GLES31, VG11
Compiler:							GCC, MinGW
Configuration:						Debug, Release

e.g. x86__Windows__MinGW_Debug or ARMv6_VC4_Linux_GLES2_GCC_Release


Yours Norbert Nopper


Changelog:

29.01.2015 - Updated to GLEW 1.12.0.

29.08.2014 - Reorganisation and improvement of READMEs.
