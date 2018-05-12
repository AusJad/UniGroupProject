#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Identifiers.h"
#include "ResourceList.h"
#include "RenderModuleStubb.h"
#include "Singleton.h"
//#include <glm/glm.hpp>
#include "Maths.h"

//--------------------------------------------------------------------------------------

/**
* @class Camera
* @brief Class for creating updating and handling the camera object.
*
* @author Mat DeVene
* @version 01
* @date 02/04/2018
*/
class Camera : public GameObject
{
public:

	Camera(Identifiers & id, vec3 pos, ResourceList & list);
	void stop();

	Camera(const Camera & tocpy);

	GameObject* create();

	/**
	* @brief Get the center offset vector.
	*
	* @return vec3 - The center offset vector.
	*/
	vec3 getCenterOffset();

	/**
	* @brief Set the field of view
	*
	* @param fov - The new FoV.
	*/
	void SetFov(float fov); //sets field of view

	/**
	* @brief Sets the viewing frustrum near and far plane.
	*
	* @param nearPlane - The nearest plane.
	* @param farPlane - The furthest Plane.
	*/
	void SetFrustrumNearFar(float nearPlane, float farPlane); //sets the viewing frustrum near and far plane
	
	/**
	* @brief Changes the direction the camera is facing.
	*
	* @param upAngle
	* @param rightAngle
	*/
	void Rotate(float upAngle, float rightAngle); //Changes the direction the camera is facing

	/**
	* @brief Adjusts camera rotation to look at 'pos'.
	*
	* @param pos - The position.
	*/
	void LookAt(vec3 pos); // adjusts camera rotation to look at 'pos'

	/**
	* @brief Set the position.
	*
	* @param pos - The new position.
	*/
	void SetPosition(const vec3& pos);

	/**
	* @brief Set the aspect ratio.
	*
	* @param aspectratio - The new aspect ratio.
	*/
	void SetAspectRatio(float aspectRatio);


	/**
	* @brief Get the FoV.
	*
	* @return float - FoV.
	*/
	float GetFov() const;

	/**
	* @brief Get the frustrum near plane
	*
	* @return float - Frustrum near plane.
	*/
	float GetFrustrumNearPlane() const;

	/**
	* @brief Get the frustrum far plane.
	*
	* @return float - Frustrum far plane.
	*/
	float GetFrustrumFarPlane() const;

	/**
	* @brief Get the aspect ratio.
	*
	* @return float - The aspect ratio.
	*/
	float GetAspectRatio() const;

	/**
	* @brief Rotation matrix for the direction of the camera.
	*
	* @return mat4 - The direction
	*/
	mat4 GetDirection() const; //rotation matrix for the direction of the camera

	/**
	* @brief Vector for cameras X axis (left / right).
	*
	* @return vec3 - The camera x axis position
	*/
	vec3 GetCamX() const; //vector for cameras X axis (left / right)

	/**
	* @brief Vector for camera's Y axis (up / down).
	*
	* @return vec3 - The camera y axis position
	*/
	vec3 GetCamY() const; //vector for camera's Y axis (up/down)

	/**
	* @brief Vector for the cameras Z axis (what it is looking at).
	*
	* @return vec3 - The camera y axis position
	*/
	vec3 GetCamZ() const; //vector for the cameras Z axis (what it is looking at)

	/**
	* @brief Camera's transformation matrix.
	*
	* @return mat4 - The cameras transformation matrix.
	*/
	mat4 GetTransMatrix() const; //camera's transformation matrix

	/**
	* @brief Perspective projection transformation matrix.
	*
	* @return mat4 - The cameras projection matrix.
	*/
	mat4 GetProjectionMatrix() const; //perspective projection transformation matrix

	/**
	* @brief Translation and rotation matrix.
	*
	* @return mat4 - The cameras view matrix.
	*/
	mat4 GetViewMatrix() const; //translation and rotation matrix


	/**
	* @brief Update function for camera.
	*
	* @param time - System time.
	*/
	void update(float time);

	/**
	* @brief Call render function.
	*/
	void render();

	/**
	* @brief Look at function.
	*/
	void callGLLookAt();

	/**
	* @brief Find if the camera is collidable.
	*
	* @return bool - If the camera can collide.
	*/
	bool isCollidable();
private:
	/// Move speed of camera.
	float moveSpeed;
	/// Rotation speed of camera.
	float rotateSpeed;
	/// Move speed decay rate.
	float speedDecay;
	/// If moving foward.
	bool moveForward;
	/// If moving backwards.
	bool moveBack;
	/// If moving right.
	bool moveRight;
	/// If moving left.
	bool moveLeft;
	/// If looking down.
	bool lookDown;
	/// If looking up.
	bool lookUp;
	/// Max speed of the camera.
	float maxlspeed;
	/**
	* @brief Correcting the angles at boundaries.
	*/
	void CorrectAngleBoundaries();
	/// Field of View.
	float fov;
	/// Aspect ratio.
	float aspectRatio;
	/// Near plane.
	float nearPlane;
	/// Far plane.
	float farPlane;
	/// Horizontal Angle.
	float horizontalAngle;
	/// Verticle Angle.
	float verticalAngle;
	/// Max angle.
	float maxAngle;
	/// Max angle of the n angle.
	float maxNangle;
	/// If the camera is birds eye view or not.
	bool birdseye;
	/// The y offset data.
	float yoff;
	
	/**
	* @brief A method to switch the view mode of the camera.
	*/
	void switchViewMode();
};

#endif