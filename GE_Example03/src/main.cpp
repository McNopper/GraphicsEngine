#include "GraphicsEngine.h"

using namespace std;

static User userInput;

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

	// Post processor with multisample

	PostProcessor2DMultisampleSP postProcessor = PostProcessor2DMultisampleSP(new PostProcessor2DMultisample(8, GL_RGB16F, false));

	PostProcessor2DMultisampleManager::getInstance()->addPostProcessor("PostProcessor", postProcessor);

	// Sky sphere

	SkySP sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "LobbyCube.dds"));
	SkyManager::getInstance()->setSky("Lobby", sky);

	SkyManager::getInstance()->setActiveSky("Lobby");

	// Monkey

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Diamond", Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, 0.0f, Color::WHITE, Color::WHITE, RI_DIAMOND);

	filename = "monkey.fbx";
	entity = entityFactory.loadFbxFile(filename, 2.0f, surfaceMaterial);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, -2.0f, -15.0f);
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

GLUSboolean updateGame(GLUSfloat deltaTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	userInput.update(deltaTime);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	ModelEntityManager::getInstance()->updateMetrics();
	ModelEntityManager::getInstance()->sort();
	ModelEntityManager::getInstance()->update();

	//

	PostProcessor2DMultisampleSP postProcessor = PostProcessor2DMultisampleManager::getInstance()->getPostProcessor("PostProcessor");
	postProcessor->use(true);

	glEnable(GL_MULTISAMPLE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	SkyManager::getInstance()->getActiveSky()->render(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye());
	ModelEntityManager::getInstance()->render();

	glDisable(GL_MULTISAMPLE);

	postProcessor->render();

	FpsPrinter::printer.print(deltaTime);

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
	// We render to a MSAA frame buffer, so MSAA not needed here
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
