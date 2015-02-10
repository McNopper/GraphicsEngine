#include "GraphicsEngine.h"

using namespace std;

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

	GlTfEntityDecoderFactory glTFentityDecoderFactory;

	ModelEntitySP entity;

	SurfaceMaterialFactory surfaceMaterialFactory;
	SurfaceMaterialSP surfaceMaterial;

	AnimationLayerSP animationLayer;
	vector<AnimationStackSP> allAnimStacks;

	Point4 position;

	string filename;
	string foldername;

	//
	// Textured cube with rotation animation.
	//

	filename = "CrateCube.json";
	foldername = "assets/CrateCube/";
	entity = glTFentityDecoderFactory.loadGlTfModelFile("CrateCube", filename, foldername, 5.0f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, 0.0f, -20.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	//
	// Skinned and animated cylinder.
	//

	filename = "SkinnedCylinder.json";
	foldername = "assets/SkinnedCylinder/";
	entity = glTFentityDecoderFactory.loadGlTfModelFile("Cylinder", filename, foldername, 1.0f);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(5.0f, 0.0f, -20.0f);
	entity->setPosition(position);
	entity->setAnimation(0, 0);

	GeneralEntityManager::getInstance()->updateEntity(entity);

	// Lights

	Color ambient(0.5f, 0.5f, 0.5f, 1.0f);

	LightManager::getInstance()->setAmbientLightColor(ambient);

	Color specular(0.5f, 0.5f, 0.5f, 1.0f);

	LightSP directionalLight = LightSP(new DirectionalLight("DirectionalLight", Color::WHITE, specular));
	LightManager::getInstance()->setLight("DirectionalLight", directionalLight);

	ProgramManagerProxy::setLightByType(ProgramManager::DEFAULT_PROGRAM_TYPE, 0, directionalLight, Point4(0.0f, 0.0f, 10.0f), Quaternion(90, Vector3(1.0f, 0.0f, 0.0f)));
	ProgramManagerProxy::setNumberLightsByType(ProgramManager::DEFAULT_PROGRAM_TYPE, 1);
	ProgramManagerProxy::setAmbientLightColorByType(ProgramManager::DEFAULT_PROGRAM_TYPE);
	ProgramManagerProxy::setNoShadowByType(ProgramManager::DEFAULT_PROGRAM_TYPE);

	//

	glEnable(GL_MULTISAMPLE);
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

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), Point4(), Quaternion());

	GeneralEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);
	GeneralEntityManager::getInstance()->update();
	GeneralEntityManager::getInstance()->sort();
	GeneralEntityManager::getInstance()->render();

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
    		EGL_CONTEXT_MINOR_VERSION, 4,
    		EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE, EGL_TRUE,
    		EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
    		EGL_CONTEXT_OPENGL_DEBUG, EGL_TRUE,
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
