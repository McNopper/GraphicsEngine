#include "GraphicsEngine.h"

#define STEP_PER_SEDCOND 2.0f

using namespace std;

static float aperture = 10.0f;

static float focal = 3.0f;

static float focusedObject = 6.0f;

static bool useMultisample = false;

static bool useDepthOfField = true;

static GLUSint globalKey;

static GroundPlane groundPlane;

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

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Diamond", Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, 0.0f, Color::WHITE, Color::WHITE, RI_DIAMOND, 0.0f);

	filename = "monkey.fbx";
	entity = entityFactory.loadFbxModelFile("Monkey", filename, 1.0f, false, surfaceMaterial);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, 1.0f, -5.0f);
	entity->setPosition(position);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// Plane

	filename = "seymourplane_triangulate.fbx";
	entity = entityFactory.loadFbxModelFile("Plane0", filename, 0.1f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(5.0f, 2.0f, -5.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	// Light up the material a little bit
	for (int32_t i = 0; i < entity->getModel()->getSurfaceMaterialCount(); i++)
	{
		entity->getModel()->getSurfaceMaterialAt(i)->setAmbient(Color(0.5f, 0.5f, 0.5f));
	}

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// ...

	position = Point4(4.0f, 1.0f, -2.0f);

	entity = entity->getNewInstance("Plane1");
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// ...

	position = Point4(6.0f, 3.0f, -8.0f);

	entity = entity->getNewInstance("Plane2");
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// Duck

	filename = "duck_triangulate.fbx";
	entity = entityFactory.loadFbxModelFile("Duck", filename, 0.01f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(-5.0f, 0.0f, -20.0f);
	entity->setPosition(position);

	// Light up the material a little bit
	for (int32_t i = 0; i < entity->getModel()->getSurfaceMaterialCount(); i++)
	{
		entity->getModel()->getSurfaceMaterialAt(i)->setAmbient(Color(0.5f, 0.5f, 0.5f));
	}

	GeneralEntityManager::getInstance()->updateEntity(entity);

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

	//

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
	if (!updateEngine(deltaTime))
	{
		return GLUS_FALSE;
	}

	updateInput(deltaTime);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), Point4(), Quaternion());

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	GeneralEntityManager::getInstance()->update();
	GeneralEntityManager::getInstance()->sort();

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
	GeneralEntityManager::getInstance()->render();

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
