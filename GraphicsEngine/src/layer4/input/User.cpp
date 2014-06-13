/*
 * User.cpp
 *
 *  Created on: 11.05.2011
 *      Author: Norbert Nopper
 */

#include "../../layer0/math/Matrix4x4.h"

#include "User.h"

using namespace std;

User User::defaultUser = User();

User::User() :
	zoomingFactor(1.0f), panningFactor(0.1f), rotationFactor(0.1f), moveFactor(10.0f), lastX(0), lastY(0), rotation(), position(), direction(0.0f, 0.0f, -1.0f), up(), left(-1.0f, 0.0f, 0.0f), wPressed(false), aPressed(false), sPressed(false), dPressed(false), dirtyFlag(false), userCamera()
{
}

User::~User()
{
}

void User::updateCamera()
{
	if (userCamera.get())
	{
		Vector3 direction(0.0f, 0.0f, -1.0f);
		Vector3 up(0.0f, 1.0f, 0.0f);
		Vector3 left(-1.0f, 0.0f, 0.0f);

		this->direction = rotation * direction;
		this->up = rotation * up;
		this->left = rotation * left;

		Point4 center = position + this->direction;

		userCamera->lookAt(position, center, this->up);

		dirtyFlag = false;
	}
}

void User::setUserCamera(const CameraSP& userCamera)
{
	this->userCamera = userCamera;

	if (userCamera.get())
	{
		this->position = userCamera->getEye();
		this->direction = userCamera->getDirection();
		this->up = userCamera->getUp();
		this->left = up.cross(direction);

		this->rotation = Quaternion(Matrix3x3(-left, up, -direction));
	}

	dirtyFlag = true;
}

const CameraSP& User::getUserCamera() const
{
	return userCamera;
}

void User::mouseButton(bool pressed, int32_t button, int32_t xPos, int32_t yPos)
{
	if (pressed)
	{
		lastX = xPos;
		lastY = yPos;
	}
}

void User::mouseWheel(int32_t buttons, int32_t ticks, int32_t xPos, int32_t yPos)
{
	// Zooming
	position = position + direction * (float(ticks) * zoomingFactor);

	dirtyFlag = true;
}

void User::mouseMove(int32_t buttons, int32_t xPos, int32_t yPos)
{
	int32_t deltaX = xPos - lastX;
	int32_t deltaY = yPos - lastY;

	if (buttons == 1)
	{
		// Panning
		position = position - left * ((float)deltaX * panningFactor) - up * ((float)deltaY * panningFactor);

		dirtyFlag = true;
	}
	else if (buttons == 4)
	{
		// Rotation
		float angleX = (float)deltaY * rotationFactor;
		float angleY = (float)deltaX * rotationFactor;

		Vector3 up(0.0f, 1.0f, 0.0f);
		Vector3 left(-1.0f, 0.0f, 0.0f);

		while (angleX <= -180.0f)
		{
			angleX += 360.0f;
		}
		while (angleX > +180.0f)
		{
			angleX -= 360.0f;
		}
		while (angleY <= -180.0f)
		{
			angleY += 360.0f;
		}
		while (angleY > +180.0f)
		{
			angleY -= 360.0f;
		}

		Quaternion rotX(angleX, left);
		Quaternion rotY(-angleY, up);

		rotation = rotY * rotation * rotX;

		dirtyFlag = true;
	}

	lastX = xPos;
	lastY = yPos;
}

void User::key(bool pressed, int32_t key)
{
	char c = static_cast<char>(key);

	if (pressed)
	{
		switch(c)
		{
			case 'w':
				wPressed = true;
				break;
			case 'a':
				aPressed = true;
				break;
			case 's':
				sPressed = true;
				break;
			case 'd':
				dPressed = true;
				break;
		}
	}
	else
	{
		switch(c)
		{
			case 'w':
				wPressed = false;
				break;
			case 'a':
				aPressed = false;
				break;
			case 's':
				sPressed = false;
				break;
			case 'd':
				dPressed = false;
				break;
		}
	}
}

void User::update(float deltaTime)
{
	if (wPressed)
	{
		if (aPressed)
		{
			position += (direction + left).normalize() * moveFactor * deltaTime;
		}
		else if (dPressed)
		{
			position += (direction - left).normalize() * moveFactor * deltaTime;
		}
		else
		{
			position += direction * moveFactor * deltaTime;
		}
	}
	else if (sPressed)
	{
		if (aPressed)
		{
			position -= (direction - left).normalize() * moveFactor * deltaTime;
		}
		else if (dPressed)
		{
			position -= (direction + left).normalize() * moveFactor * deltaTime;
		}
		else
		{
			position -= direction * moveFactor * deltaTime;
		}
	}
	else if (aPressed)
	{
		position += left * moveFactor * deltaTime;
	}
	else if (dPressed)
	{
		position -= left * moveFactor * deltaTime;
	}

	if (wPressed || aPressed || sPressed || dPressed || dirtyFlag)
	{
		updateCamera();
	}
}

float User::getMoveFactor() const {
	return moveFactor;
}

void User::setMoveFactor(float moveFactor) {
	this->moveFactor = moveFactor;
}

float User::getPanningFactor() const {
	return panningFactor;
}

void User::setPanningFactor(float panningFactor) {
	this->panningFactor = panningFactor;
}

float User::getRotationFactor() const {
	return rotationFactor;
}

void User::setRotationFactor(float rotationFactor) {
	this->rotationFactor = rotationFactor;
}

float User::getZoomingFactor() const {
	return zoomingFactor;
}

void User::setZoomingFactor(float zoomingFactor) {
	this->zoomingFactor = zoomingFactor;
}

const Point4& User::getPosition() const
{
	return position;
}

void User::setPosition(const Point4& position)
{
	this->position = position;
}

const Quaternion& User::getRotation() const
{
	return rotation;
}

void User::setRotation(const Quaternion& rotation)
{
	this->rotation = rotation;
}
