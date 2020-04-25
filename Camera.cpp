#include "Camera.h"

Camera::Camera(int width, int height) {
	view = glm::lookAt(position, target, up);
	setAspectRatio(width, height);
}

Camera::~Camera() {}

void Camera::setAspectRatio(int width, int height) {
	aspectRatio = (float)width / (float)height;
	proj = glm::perspective(fov, aspectRatio, near, far);
}

glm::mat4 Camera::getProjViewMatrix() {
	return proj * view;
}