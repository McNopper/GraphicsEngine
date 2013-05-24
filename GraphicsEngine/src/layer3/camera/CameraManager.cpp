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

CameraManager* CameraManager::instance = nullptr;

const string CameraManager::DEFAULT_PERSPECTIVE_CAMERA_KEY = "default_perspective";

const string CameraManager::DEFAULT_ORTHOGRAPHIC_CAMERA_KEY = "default_orthographic";

CameraManager::CameraManager() :
	allCameras(), allWindowCameras()
{
	allCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY] = CameraSP(new PerspectiveCamera());
	allCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY] = CameraSP(new OrthographicCamera());
	allWindowCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY] = allCameras[DEFAULT_PERSPECTIVE_CAMERA_KEY];
	allWindowCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY] = allCameras[DEFAULT_ORTHOGRAPHIC_CAMERA_KEY];
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

CameraManager* CameraManager::getInstance()
{
	if (!instance)
	{
		instance = new CameraManager();
	}

	return instance;
}

void CameraManager::terminate()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
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
	return allCameras.at(key);
}

const CameraSP& CameraManager::getCamera(const string& key) const
{
	return allCameras.at(key);
}

void CameraManager::setCamera(const string& key, const CameraSP& camera, bool windowCamera)
{
	BOOST_ASSERT(DEFAULT_PERSPECTIVE_CAMERA_KEY.compare(key) != 0);

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
		walker->second->updateViewport(viewport);

		walker++;
	}
}
