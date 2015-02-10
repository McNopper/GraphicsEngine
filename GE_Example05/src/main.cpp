#include "GraphicsEngine.h"

using namespace std;

static GroundPlane groundPlane;

static CameraSP currentCamera;

static vector<GeneralEntitySP> wireframeEntities;

static vector<GeneralEntitySP> debugEntities;

static vector<ModelEntitySP> lightEntities;

static vector<ModelEntitySP> cameraEntities;

static bool drawDebug = true;

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

	CameraEntityFactory cameraEntityFactory;

	LightEntityFactory lightEntityFactory;

	ModelEntitySP modelEntity;

	GroundEntityFactory groundEntityFactory;

	GroundEntitySP groundEntity;

	SurfaceMaterialFactory surfaceMaterialFactory;
	SurfaceMaterialSP surfaceMaterial;

	AnimationLayerSP animationLayer;
	vector<AnimationStackSP> allAnimStacks;

	Point4 position;

	string filename;

	//
	//
	//

	// Building

	filename = "Medieval_building.FBX";
	modelEntity = entityFactory.loadFbxModelFile("Medieval_building", filename, 1.0f);
	if (!modelEntity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, 0.0f, -10.0f);
	modelEntity->setPosition(position);
	modelEntity->setRotation(0.0f, 90.0f, 0.0f);

	modelEntity->setUsePositionAsBoundingSphereCenter(true);

	GeneralEntityManager::getInstance()->updateEntity(modelEntity);

	wireframeEntities.push_back(modelEntity);

	//

	Texture2DSP stoneTexture = Texture2DManager::getInstance()->createTexture("rocks.jpg");
	Texture2DSP displacementTexture = Texture2DManager::getInstance()->createTexture("rocks_NM_height.dds");

	SurfaceMaterialSP stoneMaterial = surfaceMaterialFactory.createSurfaceMaterial("Stones", stoneTexture, displacementTexture);

	groundEntity = groundEntityFactory.createGroundEntity("Stones", 8.0f, 8.0f, 8.0f, stoneMaterial);
	groundEntity->setPosition(position);
	groundEntity->setRotation(-90.0f, 0.0f, 0.0f);
	// Repeat the texture four times
	groundEntity->setRepeat(4.0f);
	// Displace given unit
	groundEntity->setDisplacementScale(0.01f);
	// Tessellate depending on screen space
	groundEntity->setScreenDistance(8.0f);

	GeneralEntityManager::getInstance()->updateEntity(groundEntity);

	wireframeEntities.push_back(groundEntity);

	//
	//
	//

	// Lights

	LightSP directionalLight = LightSP(new DirectionalLight("DirectionalLight", Color::GREY, Color::BLACK));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);

	LightSP spotLight = LightSP(new SpotLight("SpotLight", 0.9f, 0.75f, 1.0f, 0.0f, 0.0f, Color::WHITE, Color::WHITE));
	LightManager::getInstance()->setLight("SpotLight", spotLight);

	// The lights are treated as node entities

	modelEntity = lightEntityFactory.createLightEntity("DirectionalLight", directionalLight);
	modelEntity->setPosition(Point4(0.0f, 10.0f, -20.0f));
	modelEntity->setRotation(Quaternion(-45.0f, Vector3(1.0f, 0.0f, 0.0f)));
	modelEntity->setDebug(true);

	GeneralEntityManager::getInstance()->updateEntity(modelEntity);

	debugEntities.push_back(modelEntity);

	lightEntities.push_back(modelEntity);

	//
	// The later spor light will be animated
	//

	animationLayer = AnimationLayerSP(new AnimationLayer());
	animationLayer->addRotationValue(AnimationLayer::Z, 0.0f, 0.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Z, 1.0f, 45.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Z, 3.0f, -45.0f, LinearInterpolator::interpolator);
	animationLayer->addRotationValue(AnimationLayer::Z, 4.0f, 0.0f, LinearInterpolator::interpolator);
	allAnimStacks.push_back(AnimationStackSP(new AnimationStack("Alternate", 0.0f, 4.0f)));
	allAnimStacks[0]->addAnimationLayer(animationLayer);

	//

	modelEntity = lightEntityFactory.createLightEntity("SpotLight", spotLight, allAnimStacks);
	modelEntity->setPosition(Point4(0.0f, 1.0f, -5.0f));
	modelEntity->setRotation(Quaternion(80.0f, Vector3(1.0f, 0.0f, 0.0f)));
	modelEntity->setAnimation(0, 0);
	modelEntity->setDebug(true);

	GeneralEntityManager::getInstance()->updateEntity(modelEntity);

	debugEntities.push_back(modelEntity);

	lightEntities.push_back(modelEntity);

	//
	//
	//

	PerspectiveCameraSP camera = PerspectiveCameraSP(new PerspectiveCamera("RenderCamera"));
	//camera->lookAt(Point4(0.0f, 10.0f, 0.0f), Point4(0.0f, 0.0f, -10.0f), Vector3(0.0f, 1.0f, 0.0f));

	CameraManager::getInstance()->setCamera("RenderCamera", camera, true);

	// The render camera is treated as a node entity

	modelEntity = cameraEntityFactory.createCameraEntity("RenderCamera", camera);
	modelEntity->setPosition(Point4(0.0f, 10.0f, 0.0f));
	modelEntity->setRotation(Quaternion(-45.0f, Vector3(1.0f, 0.0f, 0.0f)) * Quaternion(90.0f, Vector3(0.0f, 1.0f, 0.0f)));
	modelEntity->setDebug(true);

	GeneralEntityManager::getInstance()->updateEntity(modelEntity);

	debugEntities.push_back(modelEntity);

	cameraEntities.push_back(modelEntity);

	//

	currentCamera = CameraManager::getInstance()->getDefaultPerspectiveCamera();

	//
	//
	//

	// Position the user

	User::defaultUser.setPosition(Point4(0.0f, 0.5f, 0.0f));

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

	// Update everything

	GeneralEntityManager::getInstance()->update();

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, currentCamera, deltaTime, false);

	// Lights are updated by model itself

	if (User::defaultUser.getUserCamera().get())
	{
		ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, currentCamera, Point4(), Quaternion());
	}
	else
	{
		cameraEntities[0]->setCamera("RenderCamera");
	}

	int32_t numberLights = 0;
	auto walkerLights = lightEntities.begin();
	while(walkerLights != lightEntities.end())
	{
		numberLights = (*walkerLights)->setLights(numberLights);

		walkerLights++;
	}
	ProgramManagerProxy::setNumberLightsByType(ProgramManager::DEFAULT_PROGRAM_TYPE, numberLights);
	ProgramManagerProxy::setAmbientLightColorByType(ProgramManager::DEFAULT_PROGRAM_TYPE);
	ProgramManagerProxy::setNoShadowByType(ProgramManager::DEFAULT_PROGRAM_TYPE);

	//

	GeneralEntityManager::getInstance()->sort();

	//

	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Debug plane

	glDepthMask(GL_FALSE);
	groundPlane.draw(currentCamera->getEye(), Color::GREY);
	glDepthMask(GL_TRUE);

	// All the primitves

	GeneralEntityManager::getInstance()->render();

	if (drawDebug)
	{
		CameraManager::getInstance()->getDefaultPerspectiveCamera()->debugDraw(Point4(), Quaternion());
	}

	//

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// FPS

	FpsPrinter::printer.print(deltaTime);

	// Debug Menu

	FontSP font = FontManager::getInstance()->getFont("CourierNew");
	font->print(760.0f, 10.0f, Color::RED, "Toggle wireframe: [Space]");
	font->print(760.0f, 40.0f, Color::RED, "Toggle camera:    [c]");
	font->print(760.0f, 70.0f, Color::RED, "Toggle debug:     [v]");

	return GLUS_TRUE;
}

GLUSvoid terminateGame(GLUSvoid)
{
	cameraEntities.clear();
	lightEntities.clear();
	debugEntities.clear();
	wireframeEntities.clear();

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

	if (!pressed)
	{
		if (key == ' ')
		{
			auto walker = wireframeEntities.begin();

			while (walker != wireframeEntities.end())
			{
				(*walker)->setWireframe(!(*walker)->isWireframe());

				walker++;
			}

			return;
		}
		else if (key == 'c')
		{
			if (currentCamera == CameraManager::getInstance()->getDefaultPerspectiveCamera())
			{
				currentCamera = CameraManager::getInstance()->getCamera("RenderCamera");

				User::defaultUser.setUserCamera(CameraSP());
			}
			else
			{
				currentCamera = CameraManager::getInstance()->getDefaultPerspectiveCamera();

				User::defaultUser.setUserCamera(currentCamera);
			}

			return;
		}
		else if (key == 'v')
		{
			auto walker = debugEntities.begin();

			while (walker != debugEntities.end())
			{
				(*walker)->setDebug(!(*walker)->isDebug());

				walker++;
			}

			drawDebug = !drawDebug;

			return;
		}
	}

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
