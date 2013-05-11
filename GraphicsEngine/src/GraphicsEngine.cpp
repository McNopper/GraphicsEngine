/*
 * GraphicsEngine.cpp
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#include "GraphicsEngine.h"

using namespace std;

using namespace boost;

GLUSvoid mouseButtonEngine(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos)
{
	User::defaultUser.mouseButton(pressed, button, xPos, yPos);
}

GLUSvoid mouseWheelEngine(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos)
{
	static GLUSint lastTicks = 0;

	User::defaultUser.mouseWheel(buttons, ticks-lastTicks, xPos, yPos);

	lastTicks = ticks;
}

GLUSvoid mouseMoveEngine(GLUSint buttons, GLUSint xPos, GLUSint yPos)
{
	User::defaultUser.mouseMove(buttons, xPos, yPos);
}

GLUSvoid keyEngine(GLUSboolean pressed, GLUSint key)
{
	User::defaultUser.key(pressed, key);
}

GLUSboolean initEngine(GLUSuint logLevel, int32_t numberWorker)
{
	glusLogSetLevel(logLevel);

	if (numberWorker < 0)
	{
		numberWorker = 0;
	}

	for (int32_t i = 0; i < numberWorker; i++)
	{
		WorkerManager::getInstance()->addWorker();
	}

	FontFactory fontFactory;
	fontFactory.createDefaultFont();

	DebugDrawFactory debugDrawFactory;
	debugDrawFactory.createDefaultDebugGeometry();

	// Camera

	User::defaultUser.setUserCamera(CameraManager::getInstance()->getDefaultPerspectiveCamera());

	return GLUS_TRUE;
}

GLUSvoid reshapeEngine(GLUSint width, GLUSint height)
{
	ViewportSP defaultViewport = ViewportManager::getInstance()->getDefaultViewport();
	defaultViewport->setViewport(0, 0, width, height);
	defaultViewport->use();

	CameraManager::getInstance()->updateWindowViewport(*defaultViewport);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	FrameBuffer2DManager::getInstance()->updateWidthHeight(width, height);
	FrameBuffer2DMultisampleManager::getInstance()->updateWidthHeight(width, height);
}

GLUSboolean updateEngine(GLUSfloat deltaTime)
{
	User::defaultUser.update(deltaTime);

	return GLUS_TRUE;
}

GLUSvoid terminateEngine(GLUSvoid)
{
	User::defaultUser.setUserCamera(CameraSP());

	PathEntityManager::terminate();

	GeneralEntityManager::terminate();

	ModelManager::terminate();

	DynamicEnvironmentManager::terminate();
	PostProcessor2DManager::terminate();
	PostProcessor2DMultisampleManager::terminate();

	SkyManager::terminate();
	FontManager::terminate();
	FrameBuffer2DManager::terminate();
	FrameBuffer2DMultisampleManager::terminate();
	FrameBufferCubeMapManager::terminate();
	EntityCommandManager::terminate();

	CameraManager::terminate();
	ViewportManager::terminate();
	LightManager::terminate();
	LineGeometryManager::terminate();
	EventManager::terminate();
	WorkerManager::terminate();

	RenderBufferManager::terminate();
	RenderBufferMultisampleManager::terminate();
	Texture1DManager::terminate();
	Texture1DArrayManager::terminate();
	Texture2DManager::terminate();
	Texture2DMultisampleManager::terminate();
	TextureCubeMapManager::terminate();
	ProgramManager::terminate();
}
