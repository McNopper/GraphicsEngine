/*
 * CameraManager.cpp
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

#include "CameraManager.h"

using namespace std;

const string CameraManager::DEFAULT_PERSPECTIVE_CAMERA_KEY = "default_perspective";

const string CameraManager::DEFAULT_ORTHOGRAPHIC_CAMERA_KEY = "default_orthographic";

CameraManager::CameraManager() :
		Singleton<CameraManager>(), allCameras(), allWindowCameras()
{
	allCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY] = CameraSP(new PerspectiveCamera(DEFAULT_PERSPECTIVE_CAMERA_KEY));
	allCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY] = CameraSP(new OrthographicCamera(DEFAULT_ORTHOGRAPHIC_CAMERA_KEY));
	allWindowCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY] = allCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY];
	allWindowCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY] = allCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY];

	allCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY]->lookAt(Point4(0.0f, 0.0f, 5.0f), Point4(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
	allCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY]->lookAt(Point4(0.0f, 0.0f, 5.0f), Point4(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
}

CameraManager::~CameraManager()
{
	map<string, CameraSP>::iterator walker = allCameras.begin();
	while (walker != allCameras.end())
	{
		walker->second.reset();
		walker++;
	}
	allCameras.clear();
	allWindowCameras.clear();
}

const CameraSP& CameraManager::getDefaultPerspectiveCamera() const
{
	return allCameras.at(DEFAULT_PERSPECTIVE_CAMERA_KEY);
}

const CameraSP& CameraManager::getDefaultOrthographicCamera() const
{
	return allCameras.at(DEFAULT_ORTHOGRAPHIC_CAMERA_KEY);
}

bool CameraManager::containsCamera(const string& key) const
{
	return allCameras.contains(key);
}

const CameraSP& CameraManager::getCamera(const string& key) const
{
	return allCameras.at(key);
}

void CameraManager::setCamera(const string& key, const CameraSP& camera, bool windowCamera)
{
	assert(DEFAULT_PERSPECTIVE_CAMERA_KEY.compare(key) != 0);

	glusLogPrint(GLUS_LOG_INFO, "Adding camera to manager: %s", camera->getName().c_str());

	allCameras[key] = camera;

	if (windowCamera)
	{
		allWindowCameras[key] = camera;
	}
}

void CameraManager::updateWindowViewport(const Viewport& viewport)
{
	map<string, CameraSP>::iterator walker = allWindowCameras.begin();

	while (walker != allWindowCameras.end())
	{
		walker->second->updateWindowViewport(viewport);

		walker++;
	}
}
