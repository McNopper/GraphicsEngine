/*
 * User.h
 *
 *  Created on: 11.05.2011
 *      Author: Norbert Nopper
 */

#ifndef USER_H_
#define USER_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Point4.h"
#include "../../layer0/math/Quaternion.h"
#include "../../layer3/camera/Camera.h"

class User
{

private:

	float zoomingFactor;
	float panningFactor;
	float rotationFactor;
	float moveFactor;

	std::int32_t lastX;
	std::int32_t lastY;

	Quaternion rotation;

	Point4 position;
	Vector3 direction;
	Vector3 up;
	Vector3 left;

	bool wPressed;
	bool aPressed;
	bool sPressed;
	bool dPressed;

	bool dirtyFlag;

	CameraSP userCamera;

private:

	void updateCamera();

public:

	static User defaultUser;

	User();
	virtual ~User();

	void setUserCamera(const CameraSP& userCamera);

	const CameraSP& getUserCamera() const;

	void mouseButton(bool pressed, std::int32_t button, std::int32_t xPos, std::int32_t yPos);

	void mouseWheel(std::int32_t buttons, std::int32_t ticks, std::int32_t xPos, std::int32_t yPos);

	void mouseMove(std::int32_t buttons, std::int32_t xPos, std::int32_t yPos);

	void key(bool pressed, std::int32_t key);

	void update(float deltaTime);

	float getMoveFactor() const;
	void setMoveFactor(float moveFactor);
	float getPanningFactor() const;
	void setPanningFactor(float panningFactor);
	float getRotationFactor() const;
	void setRotationFactor(float rotationFactor);
	float getZoomingFactor() const;
	void setZoomingFactor(float zoomingFactor);

	const Point4& getPosition() const;
	void setPosition(const Point4& position);

	const Quaternion& getRotation() const;
	void setRotation(const Quaternion& rotation);

};

#endif /* USER_H_ */
