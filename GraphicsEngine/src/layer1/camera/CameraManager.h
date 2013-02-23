/*
 * CameraManager.h
 *
 *  Created on: 25.04.2011
 *      Author: Norbert Nopper
 */

#ifndef CAMERAMANAGER_H_
#define CAMERAMANAGER_H_

#include "../../UsedLibs.h"

#include "Camera.h"

class CameraManager
{
private:

	static CameraManager* instance;

	std::map<std::string, CameraSP> allCameras;

	std::map<std::string, CameraSP> allWindowCameras;

public:

	static const std::string DEFAULT_PERSPECTIVE_CAMERA_KEY;
	static const std::string DEFAULT_ORTHOGRAPHIC_CAMERA_KEY;

private:

	CameraManager();
	virtual ~CameraManager();

public:

	static CameraManager* getInstance();

	static void terminate();

	const CameraSP& getDefaultPerspectiveCamera() const;

	const CameraSP& getDefaultOrthographicCamera() const;

	bool containsCamera(const std::string& key) const;

	const CameraSP& getCamera(const std::string& key) const;

	void setCamera(const std::string& key, const CameraSP& camera, bool windowCamera);

	void updateWindowViewport(const Viewport& viewport);

};

#endif /* CAMERAMANAGER_H_ */
