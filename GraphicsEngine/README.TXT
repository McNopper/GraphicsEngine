OpenGL Graphics Engine:
-----------------------

How to build the engine / examples:

1. Install Eclipse IDE for C/C++ Developers and the GNU Compiler Collection for Linux or the Windows SDK for Windows.
2. Extract this ZIP file and set the workspace-cpp folder as your Eclipse workspace.
3. Import each folder as a separate, existing project.
4. Set the build configuration in Eclipse to your operating system.
6. Build the Graphics Engine.
7. Build any of the examples.
8. Please read the README.txt in the GE_Binaries folder. 
9. The executables are located in the GE_Binaries folder. Execute them directly or create a run configuration in Eclipse.

If you get build errors:

- Please make sure, that you install all the needed header and libraries (see below).
- Some pre-build libraries are located in the External project folder. If you want, replace these libraries with your own build.
- The DevIL, Boost and the Autodesk FBX headers/libraries have to be installed separately. 

Libraries/SDKs used:

- Autodesk FBX SDK 2013.3 http://usa.autodesk.com/fbx/
- Boost 1.51.0 http://www.boost.org/ http://www.boostpro.com/
- DevIL 1.7.8 http://openil.sourceforge.net/
- GLEW 1.9.0 http://glew.sourceforge.net/
- GLFW 2.7.7 http://www.glfw.org/

Please note: On Ubuntu 12.04, just use the libraries provided with the OS, even if they are older versions.

Features:

- Primitive rendering of Sphere, Dome, Cube, Torus, Cylinder and Cone
- Model rendering out of FBX File
- Octree or list rendering
- Frustum culling
- Sorting of entities (for alpha blending etc.)
- Mouse/Key input and movement
- Phong with diffuse, normal map and environment texture (reflection and refraction)
- Alpha blending
- Animation (Transform and Color)
- Skinning
- Entity instancing (CPU)
- Enabling/disabling of nodes
- Directional, point and spot light
- Perspective and orthographic cameras
- Overlay text output
- Debug: Frames per second
- Debug: Rendering of lines, cubes and spheres
- Debug: Rendering of bounding sphere and octree nodes 
- Multithreaded update loop
- Sky sphere and dome
- Post processing with MSAA, gamma correction, tone mapping (HDR), blur and bloom
- Render filter, that only transparent, opaque or all nodes should be rendered

Changes:

- Added MSAA textures, render buffers and frame buffers
- Added MSAA post processor 
- Bug fixes and improvements

16.02.2012 Norbert Nopper (norbert@nopper.tv)
