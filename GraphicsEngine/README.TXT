OpenGL Graphics Engine:
-----------------------

How to build the engine / examples:

1. Install Eclipse IDE for C/C++ Developers and the GNU Compiler Collection for Linux, the Windows SDK for Windows or the command line tools from Xcode for Mac OS X
2. Extract this ZIP file and set the workspace-cpp folder as your Eclipse workspace.
3. Import each folder as a separate, existing project.
4. Set the build configurations in Eclipse to your operating system.
5. Build GLUS.
6. Build the Graphics Engine.
7. Build any of the examples.
8. Please read the README.txt in the GE_Binaries folder. 
9. The executables are located in the GE_Binaries folder. Execute them directly or create a run configuration in Eclipse.

If you get build errors:

- Please make sure, that you install all the needed header and libraries (see below).
- Some pre-build libraries are located in the External project folder. If you want, replace these libraries with your own build.
- The DevIL, Boost and the Autodesk FBX headers/libraries have to be installed separately. 

Libraries/SDKs used:

- Autodesk FBX SDK 2014.1 http://usa.autodesk.com/fbx/
- Boost 1.53.0 http://www.boost.org/ http://boost.teeks99.com/ http://www.macports.org/
- DevIL 1.7.8 http://openil.sourceforge.net/
- GLEW 1.9.0 http://glew.sourceforge.net/
- GLFW 3.0.3 http://www.glfw.org/

Please note: On Ubuntu 12.04, just use the libraries provided with the OS, even if they are older versions.

Features:

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

CPU:						ARMv6, x64, x86
GPU (Optional):				VC4
OS: 						Darwin, Linux, Windows
OpenGL (Optional):			GLES2, GLES3
Compiler:					GCC, MinGW, MSVC
Configuration:				Debug, Release

e.g. x86__Windows__MSVC_Debug

10.11.2013 Norbert Nopper (norbert@nopper.tv)

Changelog:

- Added shadow and cascaded shadow mapping
- Removed FBX python script for blender, as now integrated in Blender 2.69
- Added latest GLFW (3.0.3)
- Added latest GLFW (2.7.9)
- Using latest FBX SDK and Boost libraries
- Added dynamic environment mapping
- Added latest GLFW (2.7.8)
- Added entity exclude list
- Added path
- Added depth of field
- Added ground plane debug output
- Added plane debug output
- Changed build configuration naming
- Added MSAA textures, render buffers and frame buffers
- Added MSAA post processor 
- Bug fixes and improvements
