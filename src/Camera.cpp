#include "../headers/Camera.h"

Camera::Camera(int windowWidth, int windowHeight) {
	view = glm::lookAt(position, target, up);
	setAspectRatio(windowWidth, windowHeight);
}

inline void Camera::updateProjView() {
	projView = proj * view;
}

glm::mat4& Camera::getProjViewMatrix() {
	return projView;
}

glm::vec3 Camera::getViewerPos() {
	return position;
}

void Camera::setAspectRatio(int windowWidth, int windowHeight) {
	aspectRatio = (float)windowWidth / (float)windowHeight;
	proj = glm::perspective(fieldOfView, aspectRatio, near, far);
	updateProjView();
}

void Camera::rotate(float deg, glm::vec3 axis) {
	position = glm::rotate(position, glm::radians(deg), axis);
	view = glm::lookAt(position, target, up);
	updateProjView();
}