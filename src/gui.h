#pragma once

// Imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


class GuiBase
{
public:
	void init(GLFWwindow* window)
	{
		// Setup Dear ImGui context
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		const char* glsl_version = "#version 330";
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void startFrame()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void render()
	{
		// ImGui Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void cleanup()
	{
		// imGui Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void setupTest()
	{
		// Our state
		static bool show_demo_window = false;
		static bool show_another_window = false;
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello World!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}

};

bool isAmbient = true;
bool isDiffuse = true;
bool isSpecular = true;

ImVec4 lightColor = ImVec4(0.5f, 0.f, 0.f, 1.f);


ImVec4 materialAmbient = ImVec4(1.0f, 0.5f, 0.31f, 1.f);
ImVec4 materialDiffuse = ImVec4(1.0f, 0.5f, 0.31f, 1.f);
ImVec4 materialSpecular = ImVec4(0.5f, 0.5f, 0.5f, 1.f);
float shininess = 32.f;

// Light Source Intensity
ImVec4 lightSourceAmbient = ImVec4(0.2f, 0.2f, 0.2f, 1.f);
ImVec4 lightSourceDiffuse = ImVec4(0.5f, 0.5f, 0.5f, 1.f);
ImVec4 lightSourceSpecular = ImVec4(1.0f, 1.0f, 1.0f, 1.f);

class Gui : public GuiBase
{
public:
	void phong()
	{
		// Our state
		static bool show_demo_window = false;
		
		if (show_demo_window)
		{
			ImGui::ShowDemoWindow(&show_demo_window);
		}

		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Phong Lighting Model");

			ImGui::Text("Press F to toggle freelook");
			extern bool freeLook;
			ImGui::Text("freeLook = %d", freeLook);

			ImGui::Text("");
			ImGui::Checkbox("Ambient", &isAmbient);
			ImGui::Checkbox("Diffuse", &isDiffuse);
			ImGui::Checkbox("Specular", &isSpecular);
			
			ImGui::Text("");
			ImGui::Text("Object Material");
			ImGui::ColorEdit3("Ambient", (float*)&materialAmbient);
			ImGui::ColorEdit3("Diffuse", (float*)&materialDiffuse);
			ImGui::ColorEdit3("Specular", (float*)&materialSpecular);
			ImGui::SliderFloat("shininess", &shininess, 0.0f, 100.0f);

			ImGui::Text("");
			ImGui::Text("Light Source Intensity");
			ImGui::SliderFloat("Ambient R", &lightSourceAmbient.x, 0.0f, 1.0f);
			ImGui::SliderFloat("Ambient G", &lightSourceAmbient.y, 0.0f, 1.0f);
			ImGui::SliderFloat("Ambient B", &lightSourceAmbient.z, 0.0f, 1.0f);

			ImGui::Text("");
			ImGui::SliderFloat("Diffuse R", &lightSourceDiffuse.x, 0.0f, 1.0f);
			ImGui::SliderFloat("Diffuse G", &lightSourceDiffuse.y, 0.0f, 1.0f);
			ImGui::SliderFloat("Diffuse B", &lightSourceDiffuse.z, 0.0f, 1.0f);

			ImGui::Text("");
			ImGui::SliderFloat("Specular R", &lightSourceSpecular.x, 0.0f, 1.0f);
			ImGui::SliderFloat("Specular G", &lightSourceSpecular.y, 0.0f, 1.0f);
			ImGui::SliderFloat("Specular B", &lightSourceSpecular.z, 0.0f, 1.0f);

			ImGui::Text("");
			extern float lightSourceSpeed;
			extern float lightSourceDistance;
			ImGui::Text("Light Source");
			ImGui::SliderFloat("Speed", &lightSourceSpeed, 0.0f, 10.0f);
			ImGui::SliderFloat("Distance", &lightSourceDistance, 0.0f, 5.0f);

			ImGui::Text("");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
				1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}
		
};