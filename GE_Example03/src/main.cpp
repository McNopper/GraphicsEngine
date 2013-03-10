#include "GraphicsEngine.h"

#define STEP_PER_SEDCOND 2.0f

using namespace std;

static float aperture = 10.0f;

static float focal = 3.0f;

static float focusedObject = 6.0f;

static bool useMultisample = false;

static bool useDepthOfField = true;

static GLUSint globalKey;

static User userInput;

static GroundPlane groundPlane;

GLUSboolean initGame(GLUSvoid)
{
	//glusLogSetLevel(GLUS_LOG_DEBUG);

	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();
	WorkerManager::getInstance()->addWorker();

	FontFactory fontFactory;
	fontFactory.createDefaultFont();

	DebugDrawFactory debugDrawFactory;
	debugDrawFactory.createDefaultDebugGeometry();

	OctreeFactory octreeFactory;
	OctreeSP octree = octreeFactory.createOctree(6, 1024, Point4(), 256.0f, 256.0f, 256.0f);
	ModelEntityManager::getInstance()->setOctree(octree);
	//octree->setDebug(true);

	PrimitiveEntityFactory primitiveEntityFactory;

	FbxEntityFactory entityFactory;

	ModelEntitySP entity;

	SurfaceMaterialFactory surfaceMaterialFactory;
	SurfaceMaterialSP surfaceMaterial;

	AnimationLayerSP animationLayer;
	vector<AnimationStackSP> allAnimStacks;

	Point4 position;

	string filename;

	// Post processor

	PostProcessor2DSP postProcessor2D = PostProcessor2DSP(new PostProcessor2D(GL_RGB16F, GL_RGB, GL_BYTE));
	postProcessor2D->setUseDoF(useDepthOfField);
	postProcessor2D->setAperture(aperture);
	postProcessor2D->setFocal(focal);
	postProcessor2D->setFocusedObject(focusedObject);

	PostProcessor2DManager::getInstance()->addPostProcessor("PostProcessor", postProcessor2D);

	// Post processor with multisample

	PostProcessor2DMultisampleSP postProcessor2DMultisample = PostProcessor2DMultisampleSP(new PostProcessor2DMultisample(4, GL_RGB16F, false));
	postProcessor2DMultisample->setUseDoF(useDepthOfField);
	postProcessor2DMultisample->setAperture(aperture);
	postProcessor2DMultisample->setFocal(focal);
	postProcessor2DMultisample->setFocusedObject(focusedObject);

	PostProcessor2DMultisampleManager::getInstance()->addPostProcessor("PostProcessorMultisample", postProcessor2DMultisample);

	// Sky sphere

	SkySP sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "LobbyCube.dds"));
	SkyManager::getInstance()->setSky("Lobby", sky);

	SkyManager::getInstance()->setActiveSky("Lobby");

	// Monkey

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Diamond", Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, 0.0f, Color::WHITE, Color::WHITE, RI_DIAMOND);

	filename = "monkey.fbx";
	entity = entityFactory.loadFbxFile(filename, 1.0f, surfaceMaterial);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, 1.0f, -5.0f);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Plane

	filename = "seymourplane_triangulate.fbx";
	entity = entityFactory.loadFbxFile(filename, 0.1f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(5.0f, 2.0f, -5.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// ...

	position = Point4(4.0f, 1.0f, -2.0f);

	entity = entity->getNewInstance();
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// ...

	position = Point4(6.0f, 3.0f, -8.0f);

	entity = entity->getNewInstance();
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Duck

	filename = "duck_triangulate.fbx";
	entity = entityFactory.loadFbxFile(filename, 0.01f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(-5.0f, 0.0f, -20.0f);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Camera

	userInput.setUserCamera(CameraManager::getInstance()->getDefaultPerspectiveCamera());

	// Lights

	Color ambient(0.1f, 0.1f, 0.1f, 1.0f);
	Color specular(0.5f, 0.5f, 0.5f, 1.0f);

	LightSP directionalLight = LightSP(new DirectionalLight(Vector3(1.0f, 1.0f, 1.0f), ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);
	LightSP pointLight = LightSP(new PointLight(Point4(0.0f, 0.0f, 5.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("PointLight", pointLight);
	LightSP spotLight = LightSP(new SpotLight(Vector3(0.0f, 0.0f, -1.0f), 0.5f, 2.0f, Point4(0.0f, 0.0f, 10.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("SpotLight", spotLight);

	ProgramManagerProxy::setLightByType(ProgramManager::DEFAULT_PROGRAM_TYPE, directionalLight);

	//

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClearDepth(1.0f);

	return GLUS_TRUE;
}

GLUSvoid reshapeGame(GLUSint width, GLUSint height)
{
	ViewportSP defaultViewport = ViewportManager::getInstance()->getDefaultViewport();
	defaultViewport->setViewport(0, 0, width, height);
	defaultViewport->use();

	CameraManager::getInstance()->updateWindowViewport(*defaultViewport);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	FrameBuffer2DManager::getInstance()->updateWidthHeight(width, height);
	FrameBuffer2DMultisampleManager::getInstance()->updateWidthHeight(width, height);
}

GLUSvoid updateInput(GLUSfloat deltaTime)
{
	PostProcessor2DSP postProcessor2D = PostProcessor2DManager::getInstance()->getPostProcessor("PostProcessor");
	PostProcessor2DMultisampleSP postProcessor2DMultisample = PostProcessor2DMultisampleManager::getInstance()->getPostProcessor("PostProcessorMultisample");

	if (globalKey == '1')
	{
		aperture -= STEP_PER_SEDCOND * deltaTime;

		if (aperture <= 1.0f)
		{
			aperture = 1.0f;
		}

		postProcessor2D->setAperture(aperture);
		postProcessor2DMultisample->setAperture(aperture);

		return;
	}
	else if (globalKey == '2')
	{
		aperture += STEP_PER_SEDCOND * deltaTime;

		postProcessor2D->setAperture(aperture);
		postProcessor2DMultisample->setAperture(aperture);

		return;
	}
	else if (globalKey == '3')
	{
		focal -= STEP_PER_SEDCOND * deltaTime;

		if (focal <= 1.0f)
		{
			focal = 1.0f;
		}

		postProcessor2D->setFocal(focal);
		postProcessor2DMultisample->setFocal(focal);

		return;
	}
	else if (globalKey == '4')
	{
		focal += STEP_PER_SEDCOND * deltaTime;

		postProcessor2D->setFocal(focal);
		postProcessor2DMultisample->setFocal(focal);

		return;
	}
	else if (globalKey == '5')
	{
		focusedObject -= STEP_PER_SEDCOND * deltaTime;

		if (focusedObject <= 1.0f)
		{
			focusedObject = 1.0f;
		}

		postProcessor2D->setFocusedObject(focusedObject);
		postProcessor2DMultisample->setFocusedObject(focusedObject);

		return;
	}
	else if (globalKey == '6')
	{
		focusedObject += STEP_PER_SEDCOND * deltaTime;

		postProcessor2D->setFocusedObject(focusedObject);
		postProcessor2DMultisample->setFocusedObject(focusedObject);

		return;
	}
}

GLUSboolean updateGame(GLUSfloat deltaTime)
{
	updateInput(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	userInput.update(deltaTime);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	ModelEntityManager::getInstance()->updateMetrics();
	ModelEntityManager::getInstance()->sort();
	ModelEntityManager::getInstance()->update();

	//
	PostProcessorSP postProcessor;

	if (useMultisample)
	{
		postProcessor = PostProcessor2DMultisampleManager::getInstance()->getPostProcessor("PostProcessorMultisample");
	}
	else
	{
		postProcessor = PostProcessor2DManager::getInstance()->getPostProcessor("PostProcessor");
	}

	postProcessor->use(true);

	glEnable(GL_MULTISAMPLE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Debug output of the ground plane
	groundPlane.draw(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye(), Color::GREY);

	SkyManager::getInstance()->getActiveSky()->render(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye());
	ModelEntityManager::getInstance()->render();

	postProcessor->render();

	// No MSAA for the text

	glDisable(GL_MULTISAMPLE);

	FpsPrinter::printer.print(deltaTime);

	//

	FontSP font = FontManager::getInstance()->getFont("CourierNew");
	font->print(690.0f, 10.0f, Color::RED, "Toggle MSAA:              [m]");
	font->print(690.0f, 25.0f, Color::RED, "MSAA:                     %s", useMultisample ? "On" : "Off");
	font->print(690.0f, 40.0f, Color::RED, "Toggle DoF:               [f]");
	font->print(690.0f, 55.0f, Color::RED, "Depth of Field:           %s", useDepthOfField ? "On" : "Off");
	font->print(690.0f, 70.0f, Color::RED, "Dec./Inc. aperture:       [1]/[2]");
	font->print(690.0f, 85.0f, Color::RED, "Aperture:                 %.1f", aperture);
	font->print(690.0f, 100.0f, Color::RED, "Dec./Inc. focal:          [3]/[4]");
	font->print(690.0f, 115.0f, Color::RED, "Focal:                    %.1f", focal);
	font->print(690.0f, 130.0f, Color::RED, "Dec./Inc. focused object: [5]/[6]");
	font->print(690.0f, 145.0f, Color::RED, "Focused object:           %.1f", focusedObject);

	return GLUS_TRUE;
}

GLUSvoid terminateGame(GLUSvoid)
{
	userInput.setUserCamera(CameraSP());

	SkyManager::terminate();
	EntityCommandManager::terminate();
	WorkerManager::terminate();
	LineGeometryManager::terminate();
	FontManager::terminate();
	PostProcessor2DManager::terminate();
	PostProcessor2DMultisampleManager::terminate();
	FrameBuffer2DManager::terminate();
	FrameBuffer2DMultisampleManager::terminate();
	RenderBufferManager::terminate();
	RenderBufferMultisampleManager::terminate();
	Texture2DManager::terminate();
	Texture2DMultisampleManager::terminate();
	TextureCubeMapManager::terminate();
	ModelEntityManager::terminate();
	ModelManager::terminate();
	ViewportManager::terminate();
	LightManager::terminate();
	CameraManager::terminate();
	ProgramManager::terminate();
}

GLUSvoid mouseButtonGame(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseButton %d %d %d %d", pressed, button, xPos, yPos);
	userInput.mouseButton(pressed, button, xPos, yPos);
}

GLUSvoid mouseWheelGame(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos)
{
	static GLUSint lastTicks = 0;

	glusLogPrint(GLUS_LOG_DEBUG, "mouseWheel %d %d %d %d", buttons, ticks, xPos, yPos);
	userInput.mouseWheel(buttons, ticks-lastTicks, xPos, yPos);

	lastTicks = ticks;
}

GLUSvoid mouseMoveGame(GLUSint buttons, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseMove %d %d %d", buttons, xPos, yPos);
	userInput.mouseMove(buttons, xPos, yPos);
}

GLUSvoid keyGame(GLUSboolean pressed, GLUSint key)
{
	glusLogPrint(GLUS_LOG_DEBUG, "key %d %d %c", pressed, key, (char)key);

	PostProcessor2DSP postProcessor2D = PostProcessor2DManager::getInstance()->getPostProcessor("PostProcessor");
	PostProcessor2DMultisampleSP postProcessor2DMultisample = PostProcessor2DMultisampleManager::getInstance()->getPostProcessor("PostProcessorMultisample");

	if (!pressed)
	{
		globalKey = 0;

		if (key == 'm')
		{
			useMultisample = !useMultisample;

			return;
		}
		else if (key == 'f')
		{
			useDepthOfField = !useDepthOfField;

			postProcessor2D->setUseDoF(useDepthOfField);
			postProcessor2DMultisample->setUseDoF(useDepthOfField);

			return;
		}
	}
	else
	{
		globalKey = key;
	}

	userInput.key(pressed, key);
}

int main(int argc, char* argv[])
{
	glusInitFunc(::initGame);
	glusReshapeFunc(::reshapeGame);
	glusUpdateFunc(::updateGame);
	glusTerminateFunc(::terminateGame);
	glusMouseFunc(::mouseButtonGame);
	glusMouseWheelFunc(::mouseWheelGame);
	glusMouseMoveFunc(::mouseMoveGame);
	glusKeyFunc(::keyGame);

	glusPrepareContext(4, 2, GLUS_FORWARD_COMPATIBLE_BIT);
	// Use MSAA frame buffer for MSAA - can be toggled
	//glusPrepareMSAA(8);
	glusPrepareNoResize(GLUS_TRUE);
	if (!glusCreateWindow("OpenGL Graphics Engine", 1024, 768, 24, 8, GLUS_FALSE))
	{
		return -1;
	}

	glusLogPrint(GLUS_LOG_INFO, "Initialization complete");

	glusRun();

	return 0;
}
