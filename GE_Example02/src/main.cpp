#include "GraphicsEngine.h"

using namespace std;

static bool writeBrightColor = true;
static float brightColorLimit = 1.0f;

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

	// Post processor

	PostProcessor2DSP postProcessor = PostProcessor2DSP(new PostProcessor2D(GL_RGB16F, GL_RGB, GL_BYTE));

	postProcessor->setUseBloom(true);

	postProcessor->setUseExposure(true);
	postProcessor->setExposure(2.0f);

	postProcessor->setUseGamma(true);
	postProcessor->setGamma(2.2f);

	PostProcessor2DManager::getInstance()->addPostProcessor("PostProcessor", postProcessor);

	// Sky sphere

	SkySP sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "hills_positive_x.png", "hills_negative_x.png", "hills_positive_y.png", "hills_negative_y.png", "hills_positive_z.png", "hills_negative_z.png"));
	SkyManager::getInstance()->setSky("Hills", sky);

	sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "LobbyCube.dds"));
	SkyManager::getInstance()->setSky("Lobby", sky);

	sky = SkySP(new SkySphere(100.0f, 100.0f, 100.0f, "uffizi_cross.dds"));
	SkyManager::getInstance()->setSky("Uffizi", sky);

	SkyManager::getInstance()->setActiveSky("Uffizi");

	SkyManager::getInstance()->setBrightColorEffect(writeBrightColor, brightColorLimit);

	// Teapot

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Reflective", Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, 0.0f, Color::WHITE, Color::BLACK, 0.0f, 0.0f);

	filename = "teapot.fbx";
	entity = entityFactory.loadFbxFile("Teapot", filename, 1.0f, false, surfaceMaterial);
	if (!entity.get())
	{
		glusLogPrint(GLUS_LOG_ERROR, "File not found %s", filename.c_str());

		return GLUS_FALSE;
	}
	position = Point4(0.0f, -2.0f, -15.0f);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	// Yellow sphere

	surfaceMaterial = surfaceMaterialFactory.createSurfaceMaterial("Yellow", Color::BLACK, Color(0.2f, 0.2f, 0.0f), Color(0.8f, 0.8f, 0.0f), Color(0.9f, 0.9f, 9.0f), 20.0f);
	position = Point4(-10.0f, 0.0f, -15.0f);

	entity = primitiveEntityFactory.createSpherePrimitiveEntity("YellowSphere", 5.0f, 5.0f, 5.0f, surfaceMaterial);
	entity->setPosition(position);

	ModelEntityManager::getInstance()->updateEntity(entity);

	//

	ModelEntityManager::getInstance()->setBrightColorEffect(writeBrightColor, brightColorLimit);

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

	ProgramManagerProxy::setCameraByType(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera());

	ModelEntity::setCurrentValues(ProgramManager::DEFAULT_PROGRAM_TYPE, CameraManager::getInstance()->getDefaultPerspectiveCamera(), deltaTime, false);

	ModelEntityManager::getInstance()->update();
	ModelEntityManager::getInstance()->sort();

	PostProcessor2DSP postProcessor = PostProcessor2DManager::getInstance()->getPostProcessor("PostProcessor");
	postProcessor->use(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	SkyManager::getInstance()->getActiveSky()->render(CameraManager::getInstance()->getDefaultPerspectiveCamera()->getEye());
	ModelEntityManager::getInstance()->render();

	postProcessor->render();

	FpsPrinter::printer.print(deltaTime);

	//

	FontSP font = FontManager::getInstance()->getFont("CourierNew");
	font->print(700.0f, 10.0f, Color::RED, "Toggle bloom:       [n]");
	font->print(700.0f, 25.0f, Color::RED, "Bloom:              %s", postProcessor->isUseBloom() ? "On" : "Off");
	font->print(700.0f, 40.0f, Color::RED, "Toggle blur:        [b]");
	font->print(700.0f, 55.0f, Color::RED, "Blur:               %s", postProcessor->isUseBlur() ? "On" : "Off");
	font->print(700.0f, 70.0f, Color::RED, "Toggle exposure:    [e]");
	font->print(700.0f, 85.0f, Color::RED, "Dec./Inc. exposure: [r]/[t]");
	font->print(700.0f, 100.0f, Color::RED, "Exposure:           %s %.1f", postProcessor->isUseExposure() ? "On" : "Off", postProcessor->getExposure());
	font->print(700.0f, 115.0f, Color::RED, "Toggle gamma:       [g]");
	font->print(700.0f, 130.0f, Color::RED, "Dec./Inc. gamma:    [h]/[j]");
	font->print(700.0f, 145.0f, Color::RED, "Gamma correction:   %s %.1f", postProcessor->isUseGamma() ? "On" : "Off", postProcessor->getGamma());
	font->print(700.0f, 160.0f, Color::RED, "Set environment:    [1][2][3]");

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

	PostProcessor2DSP postProcessor = PostProcessor2DManager::getInstance()->getPostProcessor("PostProcessor");

	if (!pressed)
	{
		if (key == 'n')
		{
			postProcessor->setUseBloom(!postProcessor->isUseBloom());

			return;
		}
		else if (key == 'b')
		{
			postProcessor->setUseBlur(!postProcessor->isUseBlur());

			return;
		}
		else if (key == 'e')
		{
			postProcessor->setUseExposure(!postProcessor->isUseExposure());

			return;
		}
		else if (key == 'r')
		{
			postProcessor->setExposure(postProcessor->getExposure() - 0.25f);

			return;
		}
		else if (key == 't')
		{
			postProcessor->setExposure(postProcessor->getExposure() + 0.25f);

			return;
		}
		else if (key == 'g')
		{
			postProcessor->setUseGamma(!postProcessor->isUseGamma());

			return;
		}
		else if (key == 'h')
		{
			postProcessor->setGamma(postProcessor->getGamma() - 0.1f);

			return;
		}
		else if (key == 'j')
		{
			postProcessor->setGamma(postProcessor->getGamma() + 0.1f);

			return;
		}
		else if (key == '1')
		{
			SkyManager::getInstance()->setActiveSky("Uffizi");

			return;
		}
		else if (key == '2')
		{
			SkyManager::getInstance()->setActiveSky("Lobby");

			return;
		}
		else if (key == '3')
		{
			SkyManager::getInstance()->setActiveSky("Hills");

			return;
		}
	}

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
