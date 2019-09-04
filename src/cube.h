#pragma once

#include "shader.h"

// Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cube
{

public:
	Cube() = delete;
	Cube(std::string vs, std::string fs);

	void setModel(glm::mat4 mat);
	void setView(glm::mat4 mat);
	void setProjection(glm::mat4 mat);

	void render();

	Shader getShader();

private:
	unsigned int vbo;
	unsigned int vao;

	Shader shader;

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	static const float vertices[];
};