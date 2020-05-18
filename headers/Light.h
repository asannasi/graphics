#pragma once

#include <glm/glm.hpp>

class PointLight {
private:
	glm::vec3 color;
	glm::vec3 position;
	glm::mat4 pointToWorld = glm::mat4(1.0f);
public:
	PointLight(glm::vec3 color, glm::vec3 position);
	glm::vec3 getColor();
	glm::vec3 getPosition();
};

class DirectionalLight {
private:
	glm::vec3 color;
	glm::vec3 direction;
public:
	DirectionalLight(glm::vec3 color, glm::vec3 direction);
	glm::vec3 getColor();
	glm::vec3 getDirection();
};