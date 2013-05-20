/*
 * GraphicsEngine.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "UsedLibs.h"

#include "layer0/algorithm/PerlinNoise1D.h"
#include "layer0/algorithm/PerlinNoise2D.h"
#include "layer0/algorithm/PerlinNoise3D.h"
#include "layer0/math/Point4.h"
#include "layer0/math/Vector3.h"
#include "layer0/renderbuffer/RenderBuffer.h"
#include "layer0/renderbuffer/RenderBufferManager.h"
#include "layer0/renderbuffer/RenderBufferMultisample.h"
#include "layer0/renderbuffer/RenderBufferMultisampleManager.h"
#include "layer0/shader/Program.h"
#include "layer0/shader/ProgramFactory.h"
#include "layer0/shader/ProgramManager.h"
#include "layer0/statistic/FrameCounter.h"
#include "layer0/texture/Texture1DManager.h"
#include "layer0/texture/Texture1DArrayManager.h"
#include "layer0/texture/Texture2DManager.h"
#include "layer0/texture/Texture2DMultisampleManager.h"
#include "layer0/texture/TextureCubeMapManager.h"
#include "layer1/camera/CameraManager.h"
#include "layer1/camera/OrthographicCamera.h"
#include "layer1/camera/PerspectiveCamera.h"
#include "layer1/camera/ViewportManager.h"
#include "layer1/debug/DebugDraw.h"
#include "layer1/debug/DebugDrawFactory.h"
#include "layer1/debug/LineGeometryManager.h"
#include "layer1/event/EventManager.h"
#include "layer1/interpolation/ConstantInterpolator.h"
#include "layer1/interpolation/CubicInterpolator.h"
#include "layer1/interpolation/LinearInterpolator.h"
#include "layer1/light/DirectionalLight.h"
#include "layer1/light/LightManager.h"
#include "layer1/light/PointLight.h"
#include "layer1/light/SpotLight.h"
#include "layer1/material/RefractiveIndices.h"
#include "layer1/material/SurfaceMaterial.h"
#include "layer1/material/SurfaceMaterialFactory.h"
#include "layer1/worker/WorkerManager.h"
#include "layer2/animation/AnimationLayer.h"
#include "layer2/animation/AnimationStack.h"
#include "layer2/debug/GroundPlane.h"
#include "layer2/entity/EntityCommandManager.h"
#include "layer2/entity/EntityList.h"
#include "layer2/environment/SkyDome.h"
#include "layer2/environment/SkyManager.h"
#include "layer2/environment/SkySphere.h"
#include "layer2/font/Font.h"
#include "layer2/font/FontFactory.h"
#include "layer2/font/FontManager.h"
#include "layer2/framebuffer/FrameBuffer2D.h"
#include "layer2/framebuffer/FrameBuffer2DManager.h"
#include "layer2/framebuffer/FrameBuffer2DMultisample.h"
#include "layer2/framebuffer/FrameBuffer2DMultisampleManager.h"
#include "layer2/framebuffer/FrameBufferCubeMap.h"
#include "layer2/framebuffer/FrameBufferCubeMapManager.h"
#include "layer2/ground/GroundManager.h"
#include "layer2/input/User.h"
#include "layer2/shader/ProgramManagerProxy.h"
#include "layer3/debug/FpsPrinter.h"
#include "layer3/environment/DynamicEnvironmentManager.h"
#include "layer3/octree/OctreeFactory.h"
#include "layer3/postprocess/PostProcessor2D.h"
#include "layer3/postprocess/PostProcessor2DManager.h"
#include "layer3/postprocess/PostProcessor2DMultisample.h"
#include "layer3/postprocess/PostProcessor2DMultisampleManager.h"
#include "layer4/entity/GeneralEntityManager.h"
#include "layer4/model/ModelManager.h"
#include "layer5/nodeentity/NodeEntity.h"
#include "layer5/nodeentity/NodeEntityFactory.h"
#include "layer5/groundentity/GroundEntity.h"
#include "layer5/groundentity/GroundEntityFactory.h"
#include "layer5/path/CirclePath.h"
#include "layer5/path/LinePath.h"
#include "layer5/path/Path.h"
#include "layer5/path/PathEntityManager.h"
#include "layer5/path/OrientedCirclePath.h"
#include "layer5/path/OrientedLinePath.h"
#include "layer6/fbx/FbxEntityFactory.h"
#include "layer6/primitives/PrimitiveEntityFactory.h"

GLUSvoid mouseButtonEngine(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos);

GLUSvoid mouseWheelEngine(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos);

GLUSvoid mouseMoveEngine(GLUSint buttons, GLUSint xPos, GLUSint yPos);

GLUSvoid keyEngine(GLUSboolean pressed, GLUSint key);

GLUSboolean initEngine(GLUSuint logLevel = GLUS_LOG_INFO, int32_t numberWorker = 8);

GLUSvoid reshapeEngine(GLUSint width, GLUSint height);

GLUSboolean updateEngine(GLUSfloat deltaTime);

GLUSvoid terminateEngine(GLUSvoid);

#endif /* GRAPHICSENGINE_H_ */
