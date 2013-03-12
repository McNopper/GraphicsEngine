/*
 * Path.h
 *
 *  Created on: 11.03.2013
 *      Author: nopper
 */

#ifndef PATH_H_
#define PATH_H_

#include "../../UsedLibs.h"

#include "../../layer0/math/Geometry.h"

class Path
{

private:

	bool paused;

	bool looping;

	bool ended;

	float elapsedTime;

	float speed;

	Point4 location;

	Quaternion orientation;

protected:

	virtual void start() = 0;

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	virtual bool update(float deltaTime, Geometry& geometry) = 0;

	void setLocation(const Point4& location);
	void setOrientation(const Quaternion& orientation);

public:

	Path();
	virtual ~Path();

	void startPath();

	void stopPath();

	void continuePath();

	/**
	 * @return true, if end of path reached. If looping, always false.
	 */
	bool updatePath(float deltaTime, Geometry& geometry);

	bool isPaused() const;

	bool isLooping() const;
	void setLooping(bool looping);

	bool isEnded() const;

	float getElapsedTime() const;

	const Point4& getLocation() const;

	const Quaternion& getOrientation() const;

	float getSpeed() const;
	void setSpeed(float speed);

};

typedef boost::shared_ptr<Path> PathSP;

#endif /* PATH_H_ */
