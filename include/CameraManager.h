#pragma once

#include "Singleton.h"
#include "camera.h"

#define CAM Singleton<CameraManager>::getInstance()

/**
* @class CameraManager
*
* @author Morgan Smolder
*/
class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	void restorePreviousCam();

	Camera * getActiveCam();

	void switchFPSCam();

	void updateActiveCam(Camera & toset);

	void toggleFreeCam();

private:
	Camera fpscam;
	Camera freecam;

	Camera * activecam;
	Camera * prevcam;
};

