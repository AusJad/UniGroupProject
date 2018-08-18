#include "CameraManager.h"



CameraManager::CameraManager()
	: fpscam(Identifiers("CAM", "Camera"), vec3(), ResourceList("player", "Player")),
	freecam(Identifiers("CAM", "Camera"), vec3(), ResourceList("player", "Player"))
{
	activecam = &fpscam;
	prevcam = NULL;
}


CameraManager::~CameraManager(){

}


void CameraManager::restorePreviousCam() {
	if (prevcam == NULL) return;

	Camera * tmp;

	tmp = activecam;

	activecam = prevcam;

	prevcam = tmp;
}

Camera * CameraManager::getActiveCam() {
	return activecam;
}

void CameraManager::switchFPSCam() {
	prevcam = activecam;

	activecam = &fpscam;
}

void CameraManager::updateActiveCam(Camera & toset) {
	*activecam = Camera(toset);
}

void CameraManager::toggleFreeCam() {
	activecam->toggleFreeCam();
}