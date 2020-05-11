#include "../headers/Camera.h"

Camera::Camera(int width, int height) {
	view = glm::lookAt(position, target, up);
	setAspectRatio(width, height);
}

Camera::~Camera() {}

inline void Camera::updateProjView() {
	projView = proj * view;
}

glm::mat4& Camera::getProjViewMatrix() {
	return projView;
}

void Camera::setAspectRatio(int width, int height) {
	aspectRatio = (float)width / (float)height;
	proj = glm::perspective(fieldOfView, aspectRatio, near, far);
	updateProjView();
}

void Camera::rotate(float deg, glm::vec3 axis) {
	position = glm::rotate(position, glm::radians(deg), axis);
	view = glm::lookAt(position, target, up);
	updateProjView();
}