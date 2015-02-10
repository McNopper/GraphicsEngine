#include "GraphicsEngine.h"

using namespace std;

static GroundPlane groundPlane;

static EntityListSP entityExcludeList;

GLUSboolean initGame(GLUSvoid)
{
	if (!initEngine(GLUS_LOG_INFO, 7))
	{
		return GLUS_FALSE;
	}

	OctreeFactory octreeFactory;
	OctreeSP octree = octreeFactory.createOctree(6, 1024, Point4(), 256.0f, 256.0f, 256.0f);
	GeneralEntityManager::getInstance()->setOctree(octree);
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

	SkySP sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "SwedishRoyalCastle", "SwedishRoyalCastle_posx.jpg", "SwedishRoyalCastle_negx.jpg", "SwedishRoyalCastle_posy.jpg", "SwedishRoyalCastle_negy.jpg", "SwedishRoyalCastle_posz.jpg", "SwedishRoyalCastle_negz.jpg"));
	SkyManager::getInstance()->setSky("SwedishRoyalCastle", sky);

	SkyManager::getInstance()->setActiveSky("SwedishRoyalCastle");

	//
	//
	//

	// Textured, transparent cube with rotation animation

	Texture2DSP cubeTexture = Texture2DManager::getInstance()->createTexture("Glass.bmp");
	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Glass", Color::WHITE, Color::BLACK_TRANSPARENT, Color::BLACK_TRANSPARENT, cubeTexture, Color::BLACK_TRANSPARENT, 0.0f);
	surfaceMaterial->setTransparency(0.5f);
	position = Point4(0.0f, 1.0f, -10.0f);

	animationLayer = AnimationLayerSP(new AnimationLayer());
	animationLayer->addRotationValue(AnimationLayer::Y, 0.0f, 0.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Y, 5.0f, 360.0f, LinearInterpolator::interpolator);
	allAnimStacks.clear();
	allAnimStacks.push_back(AnimationStackSP(new AnimationStack("Rotation", 0.0f, 5.0f)));
	allAnimStacks[0]->addAnimationLayer(animationLayer);

	entity = primitiveEntityFactory.createCubePrimitiveEntity("GlassCube", 2.0f, 2.0f, 2.0f, surfaceMaterial, allAnimStacks);
	entity->setPosition(position);
	entity->setAnimation(0, 0);
	entity->getModel()->getRootNode()->setTransparentRecursive(true);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// Path animation

	PathSP path = PathSP(new OrientedLinePath(Quaternion(), entity->getPosition(), entity->getPosition() + Vector3(5.0f, 5.0f, -5.0f)));
	PathEntityManager::getInstance()->addEntity(entity, path);
	path->setSpeed(4.0f);
	path->setLooping(true);
	path->startPath();

	//
	//
	//

	// Astro Boy

	filename = "astroBoy_walk.fbx";
	entity = entityFactory.loadFbxModelFile("AstroBoy", filename, 0.2f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, 0.0f, -20.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// Path animation

	Quaternion baseRotation(90.0f, Vector3(0.0f, 1.0f, 0.0f));

	path = PathSP(new OrientedCirclePath(baseRotation, entity->getPosition(), entity->getPosition() + Vector3(0.0f, 0.0f, -5.0f), false));
	PathEntityManager::getInstance()->addEntity(entity, path);
	path->setSpeed(2.5f);
	path->setLooping(true);
	path->startPath();

	//
	//
	//

	// Air plane

	filename = "seymourplane_triangulate.fbx";
	entity = entityFactory.loadFbxModelFile("Plane0", filename, 0.1f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(-5.0f, 4.0f, -12.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	//

	baseRotation = Quaternion(-90.0f, Vector3(1.0f, 1.0f, 0.0f));

	path = PathSP(new OrientedCirclePath(baseRotation, entity->getPosition(), entity->getPosition() + Vector3(0.0f, 0.0f, -3.0f), true, Vector3(1.0f, 1.0f, 0.0f)));
	PathEntityManager::getInstance()->addEntity(entity, path);
	path->setSpeed(5.0f);
	path->setLooping(true);
	path->startPath();

	//
	//
	//

	entity = entity->getNewInstance("Plane1");
	position = Point4(-5.0f, 4.0f, -11.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	//

	baseRotation = Quaternion(90.0f, Vector3(-1.0f, 1.0f, 0.0f));

	path = PathSP(new OrientedCirclePath(baseRotation, entity->getPosition(), entity->getPosition() + Vector3(0.0f, 0.0f, -4.0f), false, Vector3(-1.0f, 1.0f, 0.0f)));
	PathEntityManager::getInstance()->addEntity(entity, path);
	path->setSpeed(3.0f);
	path->setLooping(true);
	path->startPath();

	//
	//
	//

	// Full reflecting sphere with dynamic environment

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("FullReflection", Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, 0.0f, Color::WHITE, Color::BLACK, RI_VACUUM, 0.0f);
	position = Point4(-5.0f, 4.0f, -15.0f);

	entity = primitiveEntityFactory.createSpherePrimitiveEntity("FullReflectionSphere", 2.0f, 2.0f, 2.0f, surfaceMaterial);
	entity->setPosition(position);
	entity->setRefractiveIndex(RI_NOTHING);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	//

	FrameBufferCubeMapSP framebufferCubeMap = DynamicEnvironmentManager::getInstance()->createCubeMap(entity, 1024);
	surfaceMaterial->setDynamicCubeMapTexture(framebufferCubeMap->getCubeMapTexture());

	//
	//
	//

	// Entity exclude list

	entityExcludeList = EntityListSP(new EntityList());

	GeneralEntityManager::getInstance()->setEntityExcludeList(entityExcludeList);

	//
	//
	//

	// Lights

	Color ambient(0.25f, 0.25f, 0.25f, 1.0f);

	LightManager::getInstance()->setAmbientLightColor(ambient);

	Color specular(0.5f, 0.5f, 0.5f, 1.0f);

	LightSP directionalLight = LightSP(new DirectionalLight("DirectionalLight", Color::WHITE, specular));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);

	ProgramManagerProxy::setLightByType(ProgramManager::DEFAULT_PROGRAM_TYPE, 0, directionalLight, Point4(0.0f, 0.0f, 10.0f), Quaternion(45, Vector3(1.0f, 0.0f, -1.0f)));
	ProgramManagerProxy::setNumberLightsByType(ProgramManager::DEFAULT_PROGRAM_TYPE, 1);
	ProgramManagerProxy::setAmbientLightColorByType(ProgramManager::DEFAULT_PROGRAM_TYPE);
	ProgramManagerProxy::setNoShadowByType(ProgramManager::DEFAULT_PROGRAM_TYPE);
	ProgramManagerProxy::setLightByType(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, 0, directionalLight, Point4(0.0f, 0.0f, 10.0f), Quaternion(45, Vector3(1.0f, 0.0f, -1.0f)));
	ProgramManagerProxy::setNumberLightsByType(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, 1);
	ProgramManagerProxy::setAmbientLightColorByType(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE);
	ProgramManagerProxy::setNoShadowByType(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE);

	// Basic OpenGL settings

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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

	// Update the paths

	PathEntityManager::getInstance()->updateEntities(deltaTime);

	// Update everything

	GeneralEntityManager::getInstance()->update();

	//
	// Render the dynamic cube maps
	//

	auto allElements = DynamicEnvironmentManager::getInstance()->getKeyValueMap();

	auto walker = allElements.begin();

	while (walker != allElements.end())
	{
		auto currentEntity = walker->first;
		entityExcludeList->addEntity(currentEntity);

		auto currentDynamicEnvironment = walker->second;
		currentDynamicEnvironment->use(currentEntity->getBoundingSphere().getCenter());

		const Viewport& dynamicEnvironmentViewport = currentDynamicEnvironment->getCamera(0)->getViewport();
		dynamicEnvironmentViewport.use();

		ProgramManagerProxy::setCameraByType(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, currentDynamicEnvironment->getCamera(0), Point4(), Quaternion());

		GeneralEntity::setCurrentValues(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, currentDynamicEnvironment->getCamera(0), deltaTime, false);

		GeneralEntityManager::getInstance()->sort();

		//

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//

		GeneralEntity::setCurrentValues(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, currentDynamicEnvironment->getCamera(0), deltaTime, false, RENDER_OPAQUE);
		GeneralEntityManager::getInstance()->render(true);

		GeneralEntity::setCurrentValues(ProgramManager::RENDER_TO_CUBEMAP_PROGRAM_TYPE, currentDynamicEnvironment->getCamera(0), deltaTime, true, RENDER_TRANSPARENT);
		glFrontFace(GL_CW);
		GeneralEntityManager::getInstance()->render(true);
		glFrontFace(GL_CCW);
		GeneralEntityManager::getInstance()->render(true);

		//

		entityExcludeList->clear();

		currentDynamicEnvironment->unuse();

		walker++;
	}

	//
	// Render the normal scene
	//

	ViewportSP defaultViewport = ViewportManager::getInstance()->getDefaultViewport();
	defaultViewport->use();

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), Point4(), Quaternion());

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	GeneralEntityManager::getInstance()->sort();

	//

	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Sky

	SkyManager::getInstance()->getActiveSky()->render(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye());

	// Debug plane

	groundPlane.draw(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye(), Color::GREY);

	// All the primitves

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false, RENDER_OPAQUE, true);
	GeneralEntityManager::getInstance()->render();

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, true, RENDER_TRANSPARENT, true);
	glFrontFace(GL_CW);
	GeneralEntityManager::getInstance()->render();
	glFrontFace(GL_CCW);
	GeneralEntityManager::getInstance()->render();

	// FPS

	FpsPrinter::printer.print(deltaTime);

	return GLUS_TRUE;
}

GLUSvoid terminateGame(GLUSvoid)
{
	if (entityExcludeList.get())
	{
		entityExcludeList->clear();
	}

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
	EGLint eglConfigAttributes[] = {
	        EGL_RED_SIZE, 8,
	        EGL_GREEN_SIZE, 8,
	        EGL_BLUE_SIZE, 8,
	        EGL_DEPTH_SIZE, 24,
	        EGL_STENCIL_SIZE, 8,
	        EGL_SAMPLE_BUFFERS, 1,
	        EGL_SAMPLES, 8,
	        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
	        EGL_NONE
	};

    EGLint eglContextAttributes[] = {
    		EGL_CONTEXT_MAJOR_VERSION, 4,
    		EGL_CONTEXT_MINOR_VERSION, 1,
    		EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_TRUE,
    		EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
    		EGL_NONE
    };

	glusWindowSetInitFunc(::initGame);
	glusWindowSetReshapeFunc(::reshapeGame);
	glusWindowSetUpdateFunc(::updateGame);
	glusWindowSetTerminateFunc(::terminateGame);
	glusWindowSetMouseFunc(::mouseButtonGame);
	glusWindowSetMouseWheelFunc(::mouseWheelGame);
	glusWindowSetMouseMoveFunc(::mouseMoveGame);
	glusWindowSetKeyFunc(::keyGame);

	if (!glusWindowCreate("OpenGL Graphics Engine", 1024, 768, GLUS_FALSE, GLUS_TRUE, eglConfigAttributes, eglContextAttributes, 0))
	{
		return -1;
	}

	glusLogPrint(GLUS_LOG_INFO, "Initialization complete");

	glusWindowRun();

	return 0;
}
