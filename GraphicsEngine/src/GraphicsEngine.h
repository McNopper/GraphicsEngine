/*
 * GraphicsEngine.h
 *
 *  Created on: 28.09.2012
 *      Author: nopper
 */

#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include "UsedLibs.h"

#include "layer0/math/Point4.h"
#include "layer0/math/Vector3.h"
#include "layer0/noise/PerlinNoise1D.h"
#include "layer0/noise/PerlinNoise2D.h"
#include "layer0/noise/PerlinNoise3D.h"
#include "layer0/statistic/FrameCounter.h"
#include "layer1/command/WorkerManager.h"
#include "layer1/event/EventManager.h"
#include "layer1/renderbuffer/RenderBuffer.h"
#include "layer1/renderbuffer/RenderBufferManager.h"
#include "layer1/renderbuffer/RenderBufferMultisample.h"
#include "layer1/renderbuffer/RenderBufferMultisampleManager.h"
#include "layer1/shader/Program.h"
#include "layer1/shader/ProgramFactory.h"
#include "layer1/shader/ProgramManager.h"
#include "layer1/texture/Texture1DManager.h"
#include "layer1/texture/Texture1DArrayManager.h"
#include "layer1/texture/Texture2DManager.h"
#include "layer1/texture/Texture2DArrayManager.h"
#include "layer1/texture/Texture2DMultisampleManager.h"
#include "layer1/texture/TextureCubeMapManager.h"
#include "layer1/texture/TextureFactory.h"
#include "layer2/debug/DebugDraw.h"
#include "layer2/debug/DebugDrawFactory.h"
#include "layer2/debug/GroundPlane.h"
#include "layer2/debug/LineGeometryManager.h"
#include "layer2/environment/SkyDome.h"
#include "layer2/environment/SkyManager.h"
#include "layer2/environment/SkySphere.h"
#include "layer2/framebuffer/FrameBuffer2D.h"
#include "layer2/framebuffer/FrameBuffer2DManager.h"
#include "layer2/framebuffer/FrameBuffer2DMultisample.h"
#include "layer2/framebuffer/FrameBuffer2DMultisampleManager.h"
#include "layer2/framebuffer/FrameBufferCubeMap.h"
#include "layer2/framebuffer/FrameBufferCubeMapManager.h"
#include "layer2/ground/GroundManager.h"
#include "layer2/interpolation/ConstantInterpolator.h"
#include "layer2/interpolation/CubicInterpolator.h"
#include "layer2/interpolation/LinearInterpolator.h"
#include "layer2/material/RefractiveIndices.h"
#include "layer2/material/SurfaceMaterial.h"
#include "layer2/material/SurfaceMaterialFactory.h"
#include "layer3/animation/AnimationLayer.h"
#include "layer3/animation/AnimationStack.h"
#include "layer3/camera/CameraManager.h"
#include "layer3/camera/OrthographicCamera.h"
#include "layer3/camera/PerspectiveCamera.h"
#include "layer3/camera/ViewportManager.h"
#include "layer3/light/DirectionalLight.h"
#include "layer3/light/LightManager.h"
#include "layer3/light/PointLight.h"
#include "layer3/light/SpotLight.h"
#include "layer4/entity/EntityList.h"
#include "layer4/font/Font.h"
#include "layer4/font/FontFactory.h"
#include "layer4/font/FontManager.h"
#include "layer4/input/User.h"
#include "layer4/postprocess/PostProcessor2D.h"
#include "layer4/postprocess/PostProcessor2DManager.h"
#include "layer4/postprocess/PostProcessor2DMultisample.h"
#include "layer4/postprocess/PostProcessor2DMultisampleManager.h"
#include "layer4/shader/ProgramManagerProxy.h"
#include "layer4/shadow/OrthographicCameraCascadedShadowMap2D.h"
#include "layer4/shadow/OrthographicCameraShadowMap2D.h"
#include "layer5/command/EntityCommandManager.h"
#include "layer5/debug/FpsPrinter.h"
#include "layer5/environment/DynamicEnvironmentManager.h"
#include "layer6/octree/OctreeFactory.h"
#include "layer6/model/ModelManager.h"
#include "layer7/entity/GeneralEntityManager.h"
#include "layer8/groundentity/GroundEntity.h"
#include "layer8/path/CirclePath.h"
#include "layer8/path/LinePath.h"
#include "layer8/path/Path.h"
#include "layer8/path/PathEntityManager.h"
#include "layer8/path/OrientedCirclePath.h"
#include "layer8/path/OrientedLinePath.h"
#include "layer9/camerafactory/CameraEntityFactory.h"
#ifndef GE_NO_FBX
#include "layer9/fbxfactory/FbxEntityFactory.h"
#endif
#include "layer9/gltffactory/GlTfEntityDecoderFactory.h"
#include "layer9/gltffactory/GlTfEntityEncoderFactory.h"
#include "layer9/groundfactory/GroundEntityFactory.h"
#include "layer9/lightfactory/LightEntityFactory.h"
#include "layer9/primitivefactory/PrimitiveEntityFactory.h"

GLUSvoid mouseButtonEngine(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos);

GLUSvoid mouseWheelEngine(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos);

GLUSvoid mouseMoveEngine(GLUSint buttons, GLUSint xPos, GLUSint yPos);

GLUSvoid keyEngine(GLUSboolean pressed, GLUSint key);

GLUSboolean initEngine(GLUSuint logLevel = GLUS_LOG_INFO, int32_t numberWorker = 8);

GLUSvoid reshapeEngine(GLUSint width, GLUSint height);

GLUSboolean updateEngine(GLUSfloat deltaTime);

GLUSvoid terminateEngine(GLUSvoid);

#endif /* GRAPHICSENGINE_H_ */
