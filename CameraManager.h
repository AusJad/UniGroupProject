#pragma once

#include "Singleton.h"
#include "camera.h"

#define CAM Singleton<CameraManager>::getInstance()

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void restorePreviousCam();

	Camera * getActiveCam();

	void switchFPSCam();

	void updateActiveCam(Camera & toset);

private:
	Camera fpscam;
	Camera freecam;

	Camera * activecam;
	Camera * prevcam;
};

