# Phong Lighting Model Example

For information, see this wikipedia page:
https://en.wikipedia.org/wiki/Phong_reflection_model

## Generating Project / Compiling
The project is configured with CMake for Windows and MacOS.
Clone the project, then from project root directory run
```
mkdir build
cd build
cmake .. -G "generator"
```
If you are on MacOS, replace "generator" with "Xcode".
You can type "Cmake -G" to get list of generators for yor system.
Once your project is generated, you can open it in Xcode, for example, and should be able to build and run.

## Dependencies
* GLFW - https://www.glfw.org/
* GLAD - https://glad.dav1d.de/
* GLM - https://glm.g-truc.net/
* Dear ImGui - https://github.com/ocornut/imgui

## Screenshot
![Alt text](https://github.com/dvorontsov/phong-lighting-model-example/blob/master/screenshots/screenshot-1.PNG)

Inspired by https://learnopengl.com
