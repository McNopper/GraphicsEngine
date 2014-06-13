/*
 * Path.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef PATH_H_
#define PATH_H_

#include "../../UsedLibs.h"

#include "../../layer7/entity/GeneralEntity.h"

class Path
{

protected:

	Quaternion baseRotation;

private:

	bool paused;

	bool looping;

	bool ended;

	float elapsedTime;

	float speed;

	Point4 position;

	Quaternion rotation;

protected:

	virtual void start() = 0;

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, const GeneralEntitySP& entity, bool updateRotation = true) = 0;

	void setPosition(const Point4& position);
	void setRotation(const Quaternion& rotation);

public:

	Path(const Quaternion& baseRotation);
	virtual ~Path();

	void startPath();

	void stopPath();

	void continuePath();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	bool updatePath(float deltaTime, const GeneralEntitySP& entity);

	bool isPaused() const;

	bool isLooping() const;
	void setLooping(bool looping);

	bool isEnded() const;

	float getElapsedTime() const;

	const Point4& getPosition() const;

	const Quaternion& getRotation() const;

	float getSpeed() const;
	void setSpeed(float speed);

};

typedef std::shared_ptr<Path> PathSP;

#endif /* PATH_H_ */
