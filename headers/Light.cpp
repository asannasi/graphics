#include "Light.h"

PointLight::PointLight(glm::vec3 color, glm::vec3 position) : 
	color(color), position(position) {
}

glm::vec3 PointLight::getColor() {
	return color;
}

glm::vec3 PointLight::getPosition() {
	return position;
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) :
	color(color), direction(direction) {
}

glm::vec3 DirectionalLight::getColor() {
	return color;
}

glm::vec3 DirectionalLight::getDirection() {
	return direction;
}
