#include "GraphicsEngine.h"

using namespace std;

static GroundPlane groundPlane;

static CameraSP currentCamera;

static ModelEntitySP modelEntity;

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

	filename = "simplescene.fbx";
	modelEntity = entityFactory.loadFbxSceneFile("Simple Scene", filename, 1.0f);

	if (!modelEntity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	modelEntity->setDebug(true);

	modelEntity->passLightsToManager();
	modelEntity->passCamerasToManager();

	GeneralEntityManager::getInstance()->updateEntity(modelEntity);

	//
	//
	//

	currentCamera = CameraManager::getInstance()->getDefaultPerspectiveCamera();

	//
	//
	//

	// Position the user

	User::defaultUser.setPosition(Point4(0.0f, 0.0f, 10.0f));

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

	// Camera

	if (User::defaultUser.getUserCamera().get())
	{
		ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, currentCamera, Point4(), Quaternion());
	}
	else
	{
		modelEntity->setCamera("Camera");
	}

	// Lights

	int32_t numberLights = 0;
	numberLights = modelEntity->setLights(numberLights);
	ProgramManagerProxy::setNumberLightsByType(ProgramManager::DEFAULT_PROGRAM_TYPE, numberLights);
	ProgramManagerProxy::setAmbientLightColorByType(ProgramManager::DEFAULT_PROGRAM_TYPE);
	ProgramManagerProxy::setNoShadowByType(ProgramManager::DEFAULT_PROGRAM_TYPE);

	//

	GeneralEntityManager::getInstance()->sort();

	//

	glClearColor(0.9f, 0.9f, 0.9f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// All the primitves

	GeneralEntityManager::getInstance()->render();

	if (drawDebug)
	{
		CameraManager::getInstance()->getDefaultPerspectiveCamera()->debugDraw(Point4(), Quaternion());
	}

	//

	// Debug plane

	groundPlane.draw(currentCamera->getEye(), Color::GREY);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// FPS

	FpsPrinter::printer.print(deltaTime);

	// Debug Menu

	FontSP font = FontManager::getInstance()->getFont("CourierNew");
	font->print(760.0f, 10.0f, Color::RED, "Toggle camera:    [c]");

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

	if (!pressed)
	{
		if (key == 'c')
		{
			if (currentCamera == CameraManager::getInstance()->getDefaultPerspectiveCamera())
			{
				currentCamera = CameraManager::getInstance()->getCamera("Camera");

				User::defaultUser.setUserCamera(CameraSP());
			}
			else
			{
				currentCamera = CameraManager::getInstance()->getDefaultPerspectiveCamera();

				User::defaultUser.setUserCamera(currentCamera);
			}

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
