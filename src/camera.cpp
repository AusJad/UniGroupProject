#include "Camera.h"

#include <math.h>



Camera::Camera(Identifiers & id, vec3 pos, ResourceList & list) : GameObject(id, pos, list)
{
	rotateSpeed = 6.0f;
	moveSpeed = 3.0f;
	speedDecay = 7.0f;
	fov = 50.0f;
	nearPlane = 0.01f;
	farPlane = 100.0f;
	aspectRatio = (4.0f / 3.0f);
	horizontalAngle = 180.0f;
	verticalAngle = 0.0f;
	maxlspeed = 100.0f;
	moveForward = false;
	moveBack = false;
	moveRight = false;
	moveLeft = false;
	lookDown = false;
	lookUp = false;
	maxAngle = 80.0f;
	maxNangle = -80.0f;
	birdseye = false;
	yoff = 30.0f;
}

void Camera::update(float time) {
	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();
	Message tmpm;
	Message tmrm;

	while (tmp->hasIMessage(this->id.getId())) {
		tmpm = tmp->getIMessage(this->id.getId());
		if (tmpm.getInstruction() == "POS" || tmpm.getInstruction() == "LPOS") {
			tmrm.setFrom(this->id);
			if (tmpm.getInstruction() == "LPOS") {
				tmrm.getData().mvdata.push_back(pos);
				tmrm.getData().mvdata.push_back(vec3(GetCamZ()));
				tmrm.getData().mvdata.push_back(vec3(GetCamY()));
				tmrm.setData(this->pos);
			}
			else {
				tmrm.setData(this->pos);
			}
			if (tmpm.getInstruction() == "POS") tmrm.setInstruction("PR");
			else tmrm.setInstruction("LPR");
			tmrm.setData(tmpm.getData().sdata);
			tmp->postIMessage(tmrm, tmpm.getFrom().getId());
		}
	}

	while (tmp->hasMessage(id)) {

		tmpm = tmp->getMessage(id);

		if (defaultMessageHandler(tmpm)) {
			//no action -- handled automatically.
		}
		else
		if (tmpm.getInstruction() == "MVF") {
			this->moveForward = true;
		}
		else
		if (tmpm.getInstruction() == "SMF") {
			this->moveForward = false;
		}
		else
		if (tmpm.getInstruction() == "MVB") {
			this->moveBack = true;
		}
		else
		if (tmpm.getInstruction() == "SMB") {
			this->moveBack = false;
		}
		else
		if (tmpm.getInstruction() == "MVR") {
			this->moveRight = true;
		}
		else
		if (tmpm.getInstruction() == "SMR") {
			this->moveRight = false;
		}
		else
		if (tmpm.getInstruction() == "MVL") {
			this->moveLeft = true;
		}
		else
		if (tmpm.getInstruction() == "SML") {
			this->moveLeft = false;
		}
		else
		if (tmpm.getInstruction() == "LD") {
			this->lookDown = true;
		}
		else
		if (tmpm.getInstruction() == "SLD") {
			this->lookDown = false;
		}
		else
		if (tmpm.getInstruction() == "LU") {
			this->lookUp = true;
		}
		else
		if (tmpm.getInstruction() == "SLU") {
			this->lookUp = false;
		}
		else
		if (tmpm.getInstruction() == "LX") {
			horizontalAngle -= tmpm.getData().fdata * time * rotateSpeed;
		}
		else
		if (tmpm.getInstruction() == "LY") {
			verticalAngle -= tmpm.getData().fdata * time * rotateSpeed;
			if (verticalAngle <= maxNangle && tmpm.getData().fdata > 0) verticalAngle = maxNangle;
			if (verticalAngle >= maxAngle && tmpm.getData().fdata < 0) verticalAngle = maxAngle;
		}
		else
		if (tmpm.getInstruction() == POS_REQUEST) {
			tmpm.setInstruction(POS_RESPONSE);
			tmpm.getData().vdata = pos;
			tmp->postMessage(tmpm, tmpm.getFrom());
		}
		else
		if (tmpm.getInstruction() == GET_FRONT) {
			tmpm.setInstruction(GET_FRONT_RESPONSE);
			tmpm.getData().vdata = GetCamZ();
			tmp->postMessage(tmpm, tmpm.getFrom());
		}
		else
		if (tmpm.getInstruction() == SWITCH_VIEW_MODE) {
			switchViewMode();
		}
		else
		if (tmpm.getInstruction() == DAMAGE) {
			if (resources.hasResource("player")) MSGBS->postMessage(tmpm, Identifiers("", resources.getResource("player")));
		}
	}

	if (this->moveForward) {
		target += GetCamZ()* moveSpeed;
	}
	else
	if (this->moveBack) {
		target += -GetCamZ()* moveSpeed;
	}

	if (this->moveRight) {
		target += GetCamX()* moveSpeed;
	}
	else
	if (this->moveLeft) {
		target -= GetCamX()* moveSpeed;
	}

	if (this->lookDown) {
		target -= vec3(0, 1, 0)* moveSpeed;
	}
	else
	if (this->lookUp) {
		target += vec3(0, 1, 0)* moveSpeed;
	}

	pos += (target * (time * speedDecay));
	target -= (target * (time * speedDecay));
}

bool Camera::isCollidable() {
	return !birdseye;
}

void Camera::switchViewMode() {
	birdseye = !birdseye;
	
	if (!birdseye) {
		maxAngle = 80.0f;
		maxNangle = -80.0f;
		//yoff = 15.0f;
		moveSpeed = 3.0f;
	}
	else {
		maxAngle = 80.0f;
		maxNangle = -80.0f;
		//yoff = 1000.0f;
		moveSpeed = 6.0f;
	}
}

void Camera::stop(){
	moveForward = false;
	moveBack = false;
	moveRight = false;
	moveLeft = false;
	lookDown = false;
	lookUp = false;
	target = vec3();
}

void Camera::render() {
	callGLLookAt();
}

void Camera::callGLLookAt()
{
	Singleton<RenderModuleStubb>::getInstance()->callLookAt(vec3(pos.x(), pos.y(), pos.z()), 
				vec3(pos.x() + GetCamZ().x(), pos.y() + GetCamZ().y(), pos.z() + GetCamZ().z()),
				vec3(GetCamY().x(), GetCamY().y(), GetCamY().z()));

}

void Camera::SetFov(float fov) {
	assert(fov > 0.0f && fov < 180.0f);
	fov = fov;
}

void Camera::SetFrustrumNearFar(float nearPlane, float farPlane) {
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	nearPlane = nearPlane;
	farPlane = farPlane;
}

void Camera::Rotate(float upAngle, float rightAngle) {
	horizontalAngle += rightAngle;
	verticalAngle += upAngle;
	CorrectAngleBoundaries();
}

void Camera::LookAt(vec3 pos) {
	vec3 direction = Maths::normalize(pos - vec3(this->pos.x(), this->pos.y(), this->pos.z()));
	verticalAngle = Maths::radians(asinf(-direction.y()));
	horizontalAngle = -Maths::radians(atan2f(-direction.x(), -direction.z()));
	CorrectAngleBoundaries();
}

void Camera::SetPosition(const vec3& pos) {
	this->pos = pos;
}

void Camera::SetAspectRatio(float aspectRatio) {
	assert(aspectRatio > 0.0);
	this->aspectRatio = aspectRatio;
}


float Camera::GetFov() const {
	return fov;
}

float Camera::GetFrustrumNearPlane() const {
	return nearPlane;
}

float Camera::GetFrustrumFarPlane() const {
	return farPlane;
}

float Camera::GetAspectRatio() const {
	return aspectRatio;
}

mat4 Camera::GetDirection() const {
	mat4 direction;
	direction = Maths::rotate(direction, Maths::radians(verticalAngle), vec3(1, 0, 0));
	direction = Maths::rotate(direction, Maths::radians(horizontalAngle), vec3(0, 1, 0));
	return direction;
}

vec3 Camera::GetCamX() const {
	vec4 right = Maths::inverse(GetDirection()) * vec4(1, 0, 0, 1);
	return vec3(right);
}

vec3 Camera::GetCamY() const {
	vec4 up = Maths::inverse(GetDirection()) * vec4(0, 1, 0, 1);
	return vec3(up);
}

vec3 Camera::GetCamZ() const {
	vec4 camZ = Maths::inverse(GetDirection()) * vec4(0, 0, -1, 1);
	return vec3(camZ);
}

mat4 Camera::GetTransMatrix() const {
	return GetProjectionMatrix() * GetViewMatrix();
}

mat4 Camera::GetProjectionMatrix() const {
	return Maths::perspective(Maths::radians(fov), aspectRatio, nearPlane, farPlane);
}

mat4 Camera::GetViewMatrix() const {
	return GetDirection() * Maths::translate(mat4(), vec3(pos.x() * -1, pos.y() * -1, pos.z() * -1));
}

void Camera::CorrectAngleBoundaries() {
	horizontalAngle = fmodf(horizontalAngle, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if (horizontalAngle < 0.0f)
		horizontalAngle += 360.0f;

	if (verticalAngle > maxAngle)
		verticalAngle = maxAngle;
	else if (verticalAngle < maxNangle)
		verticalAngle = maxNangle;
}

vec3 Camera::getCenterOffset() {
	return vec3(0, yoff, 0);
}

Camera::Camera(const Camera & tocpy) : GameObject(tocpy) {
	moveSpeed = tocpy.moveSpeed;
	rotateSpeed = tocpy.rotateSpeed;
	speedDecay = tocpy.speedDecay;
	moveForward = tocpy.moveForward;
	moveBack = tocpy.moveBack;
	moveRight = tocpy.moveRight;
	moveLeft = tocpy.moveLeft;
	lookDown = tocpy.lookDown;
	lookUp = tocpy.lookUp;
	maxlspeed = tocpy.maxlspeed;
	fov = tocpy.fov;
	aspectRatio = tocpy.aspectRatio;
	nearPlane = tocpy.nearPlane;
	farPlane = tocpy.farPlane;
	horizontalAngle = tocpy.horizontalAngle;
	verticalAngle = tocpy.verticalAngle;
	maxAngle = tocpy.maxAngle;
	maxNangle = tocpy.maxNangle;
	birdseye = tocpy.birdseye;
	yoff = tocpy.yoff;
}

GameObject* Camera::create() {
	return new Camera(*this);
}

std::string Camera::toString()
{
	std::string towrite;

	towrite = GameObject::toString();
	towrite += "FACING," + std::to_string(horizontalAngle) + "," + std::to_string(verticalAngle);

	return towrite;
}

bool Camera::fromstring(std::string toread)
{
	float tmpf;
	std::string linehead;
	int delimlen = 1;

	while (!toread.empty())
	{
		linehead = toread.substr(0, toread.find(','));
		toread.erase(0, toread.find(',') + delimlen);

		if(!GameObject::fromstring(linehead, toread))
		if (linehead == "FACING")
		{
			tmpf = stof(toread.substr(0, toread.find(',')));
			horizontalAngle = tmpf;
			toread.erase(0, toread.find(',') + delimlen);

			tmpf = stof(toread);
			verticalAngle = tmpf;
			toread.erase();
		}
	}
	return true;
}