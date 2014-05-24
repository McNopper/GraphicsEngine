/*
 * ViewportManager.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef VIEWPORTMANAGER_H_
#define VIEWPORTMANAGER_H_

#include "../../UsedLibs.h"

#include "../../layer0/stereotype/KeyValueMap.h"
#include "../../layer0/stereotype/Singleton.h"

#include "Viewport.h"

class ViewportManager : public Singleton<ViewportManager>
{

	friend class Singleton<ViewportManager>;

private:

	KeyValueMap<std::string, ViewportSP> allViewports;

public:

	static const std::string DEFAULT_VIEWPORT_KEY;

private:

	ViewportManager();
	virtual ~ViewportManager();

public:

	const ViewportSP& getDefaultViewport() const;

	bool containsViewport(const std::string& key) const;

	const ViewportSP& getViewport(const std::string& key) const;

	void setViewport(const std::string& key, const ViewportSP& viewport);

};

#endif /* VIEWPORTMANAGER_H_ */
