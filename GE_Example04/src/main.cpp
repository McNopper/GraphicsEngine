#include "GraphicsEngine.h"

using namespace std;

static GroundPlane groundPlane;

GLUSboolean initGame(GLUSvoid)
{
	if (!initEngine(GLUS_LOG_INFO, 7))
	{
		return GLUS_FALSE;
	}

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

	// Sky sphere

	SkySP sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "SwedishRoyalCastle_posx.jpg", "SwedishRoyalCastle_negx.jpg", "SwedishRoyalCastle_posy.jpg", "SwedishRoyalCastle_negy.jpg", "SwedishRoyalCastle_posz.jpg", "SwedishRoyalCastle_negz.jpg"));
	SkyManager::getInstance()->setSky("SwedishRoyalCastle", sky);

	SkyManager::getInstance()->setActiveSky("SwedishRoyalCastle");

	// Textured, transparent cube with rotation animation

	Texture2DSP cubeTexture = Texture2DManager::getInstance()->createTexture("Glass.bmp");
	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Glass", Color(1.0f, 1.0f, 1.0f, 0.5f), Color::BLACK_TRANSPARENT, Color::BLACK_TRANSPARENT, cubeTexture, Color::BLACK_TRANSPARENT, 0.0f);
	position = Point4(0.0f, 1.0f, -10.0f);

	animationLayer = AnimationLayerSP(new AnimationLayer());
	animationLayer->addRotationValue(AnimationLayer::Y, 0.0f, 0.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Y, 5.0f, 360.0f, LinearInterpolator::interpolator);
	allAnimStacks.clear();
	allAnimStacks.push_back(AnimationStackSP(new AnimationStack(0.0f, 5.0f)));
	allAnimStacks[0]->addAnimationLayer(animationLayer);

	entity = primitiveEntityFactory.createCubePrimitiveEntity("GlassCube", 2.0f, 2.0f, 2.0f, surfaceMaterial, allAnimStacks);
	entity->setPosition(position);
	entity->setAnimation(0, 0);
	entity->getModel()->getRootNode()->setTransparentRecursive(true);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Path animation

	PathSP path = PathSP(new LinePath(entity->getPosition(), entity->getPosition() + Vector3(0.0f, 0.0f, -10.0f)));
	PathEntityManager::getInstance()->addEntity(entity.get(), path);
	path->setSpeed(4.0f);
	path->setLooping(true);
	path->startPath();

	// Lights

	Color ambient(0.25f, 0.25f, 0.25f, 1.0f);
	Color specular(0.5f, 0.5f, 0.5f, 1.0f);

	LightSP directionalLight = LightSP(new DirectionalLight(Vector3(1.0f, 1.0f, 1.0f), ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);
	LightSP pointLight = LightSP(new PointLight(Point4(0.0f, 0.0f, 5.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("PointLight", pointLight);
	LightSP spotLight = LightSP(new SpotLight(Vector3(0.0f, 0.0f, -1.0f), 0.5f, 2.0f, Point4(0.0f, 0.0f, 10.0f), 1.0f, 0.0f, 0.0f, ambient, Color::WHITE, specular));
	LightManager::getInstance()->setLight("SpotLight", spotLight);

	ProgramManagerProxy::setLightByType(ProgramManager::DEFAULT_PROGRAM_TYPE, directionalLight);

	// Basic OpenGL settings

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClearDepth(1.0f);

	return GLUS_TRUE;
}

GLUSvoid reshapeGame(GLUSint width, GLUSint height)
{
	reshapeEngine(width, height);
}

GLUSboolean updateGame(GLUSfloat deltaTime)
{
	if (!updateEngine(deltaTime))
	{
		return GLUS_FALSE;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	// Path animation

	// Get the glass cube ...
	ModelEntitySP entity = ModelEntityManager::getInstance()->findEntity("GlassCube");
	// ... update the path ...
	PathEntityManager::getInstance()->updateEntity(entity.get(), deltaTime);
	// ... and pass the values to the manager.
	ModelEntityManager::getInstance()->updateEntity(entity);

	//

	ModelEntityManager::getInstance()->updateMetrics();
	ModelEntityManager::getInstance()->sort();
	ModelEntityManager::getInstance()->update();

	// Sky

	SkyManager::getInstance()->getActiveSky()->render(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye());

	// Debug plane

	groundPlane.draw(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye(), Color::GREY);

	// All the primitves

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false, RENDER_OPAQUE);
	ModelEntityManager::getInstance()->render();

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, true, RENDER_TRANSPARENT);
	glFrontFace(GL_CW);
	ModelEntityManager::getInstance()->render();
	glFrontFace(GL_CCW);
	ModelEntityManager::getInstance()->render();

	// FPS

	FpsPrinter::printer.print(deltaTime);

	return GLUS_TRUE;
}

GLUSvoid terminateGame(GLUSvoid)
{
	terminateEngine();
}

GLUSvoid mouseButtonGame(GLUSboolean pressed, GLUSint button, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseButton %d %d %d %d", pressed, button, xPos, yPos);
	mouseButtonEngine(pressed, button, xPos, yPos);
}

GLUSvoid mouseWheelGame(GLUSint buttons, GLUSint ticks, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseWheel %d %d %d %d", buttons, ticks, xPos, yPos);
	mouseWheelEngine(buttons, ticks, xPos, yPos);
}

GLUSvoid mouseMoveGame(GLUSint buttons, GLUSint xPos, GLUSint yPos)
{
	glusLogPrint(GLUS_LOG_DEBUG, "mouseMove %d %d %d", buttons, xPos, yPos);
	mouseMoveEngine(buttons, xPos, yPos);
}

GLUSvoid keyGame(GLUSboolean pressed, GLUSint key)
{
	glusLogPrint(GLUS_LOG_DEBUG, "key %d %d %c", pressed, key, (char)key);
	keyEngine(pressed, key);
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
	glusPrepareMSAA(8);
	glusPrepareNoResize(GLUS_TRUE);
	if (!glusCreateWindow("OpenGL Graphics Engine", 1024, 768, 24, 8, GLUS_FALSE))
	{
		return -1;
	}

	glusLogPrint(GLUS_LOG_INFO, "Initialization complete");

	glusRun();

	return 0;
}
