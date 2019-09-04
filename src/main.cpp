#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

// Project includes
#include "shader.h"
#include "cube.h"
#include "utils/root_dir.h"
#include "gui.h"

// Math (GLM)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Camera stuff
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

bool freeLook = false;

// Lighting
glm::vec3 lightPos(1.2f, 0.0f, 2.0f);
float lightSourceSpeed = 1.0f;
float lightSourceDistance = 1.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (freeLook)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDir = glm::normalize(front);
}


void freelook_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F && action == GLFW_PRESS)
		freeLook = !freeLook;
}

void wireframe(bool value)
{
	if (value)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		wireframe(true);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		wireframe(false);


	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraDir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraDir;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraDir, cameraUp)) * cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos.y += cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		cameraPos.y -= cameraSpeed;
}


int main(void)
{
	GLFWwindow* window;
	char *programName = "Phong Lighting Model Example";

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 1366x768
	unsigned int SCREEN_WIDTH = 1366;
	unsigned int SCREEN_HEIGHT = 768;

	// console output
	std::cout << programName << std::endl;
	std::cout << "Screen ratio (width/heght): " << (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT << std::endl;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, programName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetKeyCallback(window, freelook_key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	wireframe(false);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	std::string ROOT_DIR_STR = std::string(ROOT_DIR);

	Cube cube(ROOT_DIR_STR + "shaders/cube.vertex", ROOT_DIR_STR + "shaders/cube.fragment");
	Cube lamp(ROOT_DIR_STR + "shaders/lamp.vertex", ROOT_DIR_STR + "shaders/lamp.fragment");

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	Gui gui;
	gui.init(window);

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		if (freeLook)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  // Disable mouse cursor			
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  // Enable mouse cursor
		}

		processInput(window);
		gui.startFrame();
		gui.phong();

		// Clear screen
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);

		cube.setModel(model);
		cube.setView(view);
		cube.setProjection(projection);
		cube.getShader().use();

		cube.getShader().setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		cube.getShader().setVec3("viewPos", cameraPos);

		cube.getShader().setVec3("material.ambient", materialAmbient.x, materialAmbient.y, materialAmbient.z);
		cube.getShader().setVec3("material.diffuse", materialDiffuse.x, materialDiffuse.y, materialDiffuse.z);
		cube.getShader().setVec3("material.specular", materialSpecular.x, materialSpecular.y, materialSpecular.z);
		cube.getShader().setFloat("material.shininess", shininess);

		cube.getShader().setVec3("light.position", lightPos);
		cube.getShader().setVec3("light.ambient", lightSourceAmbient.x, lightSourceAmbient.y, lightSourceAmbient.z);
		cube.getShader().setVec3("light.diffuse", lightSourceDiffuse.x, lightSourceDiffuse.y, lightSourceDiffuse.z); // darken the light a bit to fit the scene			
		cube.getShader().setVec3("light.specular", lightSourceSpecular.x, lightSourceSpecular.y, lightSourceSpecular.z);
		
		cube.getShader().setBool("isAmbient", isAmbient);
		cube.getShader().setBool("isDiffuse", isDiffuse);
		cube.getShader().setBool("isSpecular", isSpecular);

		cube.render();

		lightPos.x = lightSourceDistance * glm::sin((float)glfwGetTime() * lightSourceSpeed);
		lightPos.z = lightSourceDistance * glm::cos((float)glfwGetTime() * lightSourceSpeed);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));

		lamp.setModel(model);
		lamp.setView(view);
		lamp.setProjection(projection);

		lamp.render();

		gui.render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	gui.cleanup();
	glfwTerminate();
	return 0;
}

