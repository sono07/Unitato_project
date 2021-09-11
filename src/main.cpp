#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h> 
#include <SDL.h>
#include <SDL_image.h>

#include <chrono>
#include <vector>
#include <sstream>

#include "../include/fileio.h"
#include "../include/Shader.h"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/Mesh.h"
#include "../include/Model.h"
#include "../include/Logger.h"
#include "../include/Texture.h"
#include "../include/Math.h"
#include "../include/Camera.h"
#include "../include/Light.h"

/// <summary>
/// Initializes renderer context as the application window, OpenGL, ImGuI
/// </summary>
/// <param name="window">| Address of the pointer which points to the SDL_Window object</param>
/// <param name="GLContext">| Address of the OpenGL contexts for SDL</param>
/// <param name="windowSurface">| Address of the pointer which points to the SDL_Surface object of the window</param>
/// <param name="imGuiIO">| Address of the ImGuiIO object which initializes the intermediate debug window</param>
/// <returns>True or false whether the initialization was successful or not</returns>
bool Init(SDL_Window*& window, SDL_GLContext& GLContext, SDL_Surface*& windowSurface, ImGuiIO& imGuiIO);

/// <summary>
/// Destroys renderer context as the application window, OpenGL, ImGuI and exits the application
/// </summary>
/// <param name="window">| Address of the pointer which points to the SDL_Window object</param>
/// <param name="GLContext">| Address of the OpenGL contexts for SDL</param>
/// <param name="exited">| Reference to a bool parameter which signals whether the program should exit or not</param>
void Quit(SDL_Window*& window, SDL_GLContext& GLContext, bool& exited);

/// <summary>
/// Mouse movement handler function.
/// </summary>
/// <param name="w">| The weight of the window</param>
/// <param name="h">| The height of the window</param>
/// <param name="direction">| The direction we will set for the Camera target</param>
/// <param name="mousePosX">| The X position of the mouse</param>
/// <param name="mousePosY">| The Y position of the mouse</param>
/// <param name="isFirstMouseMove">| Boolean that determinates if it's the first movement of the mouse since we running the window</param>
/// <param name="mouseSensitivity">| Sensitivity of the mouse</param>
/// <param name="yaw">| The yaw value represents the magnitude we're looking to the left or to the right</param>
/// <param name="pitch">| The pitch is the angle that depicts how much we're looking up or down</param>
void MouseCallback(float w, float h, std::tuple<float, float, float>& direction, int& mousePosX, int& mousePosY, bool& isFirstMouseMove, float mouseSensitivity, float& yaw, float& pitch);

Logger MainLog;

enum class ATTRIBUTE_TYPE
{
	VERTEX = 0,
	UV = 1,
	NORMAL = 2
};

int main(int argc, char* argv[])
{
	bool SHOULD_CLOSE = false;
	bool isFirstMouseMove = true;

	SDL_Window* window = nullptr;
	SDL_Surface* windowSurface = nullptr;
	SDL_GLContext GLContext = nullptr;
	SDL_Event event;
	ImGuiIO imGuiIO;

	if (!Init(window, GLContext, windowSurface, imGuiIO))
	{
		MainLog.Error("Init could not be initialized");
		return false;
	}

	//std::chrono::high_resolution_clock::time_point lastFrame = std::chrono::high_resolution_clock::now();

	VertexBuffer VBO;
	VertexArray VAO;

	Camera camera(std::make_tuple(0.0f, 0.0f, 0.5f), std::make_tuple(0.0f, 0.0f, 0.0f), 45.0f);
	Light light(std::make_tuple(1.0f, 1.0f, 1.0f), std::make_tuple(1.0f, 1.0f, 1.0f), std::make_tuple(0.0f, 0.0f, 0.0f), 0.5f);

	camera.CreateViewMatrix();
	camera.CreateProjectionMatrix(static_cast<float>(windowSurface->w), static_cast<float>(windowSurface->h));

	std::shared_ptr<Texture> texture = std::make_shared<Texture>("./textures/metal.png", windowSurface->format);
	
	std::shared_ptr<Mesh> screwMesh = std::make_shared<Mesh>("./models/anya2.obj");

	Shader shader("./src/shader.vs", "./src/shader.fs");

	Model model(screwMesh, texture);
	model.BindTexture();

	std::vector<float> scaleVector = { 1.0f, 1.0f, 1.0f };
	std::vector<float> rotateVector = { 0.0f, 0.0f, 0.0f };
	std::vector<float> translationVector = { 0.0f, 0.0f, 0.0f };

	//model.ScaleModelMatrix(scaleVector.at(0), scaleVector.at(1), scaleVector.at(2));
	//model.RotateModelMatrix(rotateVector.at(0), rotateVector.at(1), rotateVector.at(2));
	model.TranslateModelMatrix(translationVector.at(0), translationVector.at(1), translationVector.at(2));
	
	//Send MVP to shader
	shader.SetUniformMat4x4f("uModelMatrix", model.GetModelMatrix());
	shader.SetUniformMat4x4f("uViewMatrix", camera.GetViewMatrix());
	shader.SetUniformMat4x4f("uProjectionMatrix", camera.GetProjectionMatrix());

	VAO.Bind();
	VBO.Bind();
	VAO.Fill(model.GetMesh()->GetDataBuffer());

	glVertexAttribPointer((GLuint)ATTRIBUTE_TYPE::VERTEX, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
	glEnableVertexAttribArray((GLuint)ATTRIBUTE_TYPE::VERTEX);
	glVertexAttribPointer((GLuint)ATTRIBUTE_TYPE::UV, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray((GLuint)ATTRIBUTE_TYPE::UV);
	glVertexAttribPointer((GLuint)ATTRIBUTE_TYPE::NORMAL, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray((GLuint)ATTRIBUTE_TYPE::NORMAL);
	
	int mousePosX, mousePosY;
	//std::chrono::high_resolution_clock::time_point currentFrame = std::chrono::high_resolution_clock::now();
	//float deltaTime = static_cast<float>((std::chrono::duration_cast<std::chrono::microseconds>(currentFrame - lastFrame).count())) / 1000000;
	float cameraSpeed = 0.01f;
	const float mouseSensitivity = 0.1f;
	std::tuple<float, float, float> direction;
	float yaw = -90.0f;
	float pitch = 0.0f;

	while (!SHOULD_CLOSE)
	{
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			switch (event.type)
			{
			case SDL_MOUSEMOTION: {
				if (event.motion.state & SDL_BUTTON_RMASK)
				{
					SDL_GetMouseState(&mousePosX, &mousePosY);
					MouseCallback(windowSurface->w, windowSurface->h, direction, mousePosX, mousePosY, isFirstMouseMove, mouseSensitivity, yaw, pitch);
					camera.SetCamTarget(Math::Normalize(direction));
				}
				break;
			}
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_q: cameraSpeed = cameraSpeed + 0.01;
					std::cout << "speed: " << cameraSpeed << std:: endl;  break;
				case SDLK_e: cameraSpeed = abs(cameraSpeed - 0.01);
					std::cout << "speed: " << cameraSpeed << std::endl; break;
				case SDLK_w: camera.MoveCamWD(std::make_tuple(0.0f, 0.0f, std::get<2>(camera.GetTarget()) * cameraSpeed));
					break;
				case SDLK_a: camera.MoveCamAS(std::make_tuple(std::get<0>(Math::Normalize(Math::Cross(camera.GetTarget(), camera.GetUp()))) * cameraSpeed, 0.0f, 0.0f));
					break;
				case SDLK_s: camera.MoveCamAS(std::make_tuple(0.0f, 0.0f, std::get<2>(camera.GetTarget()) * cameraSpeed));
					break;
				case SDLK_d: camera.MoveCamWD(std::make_tuple(std::get<0>(Math::Normalize(Math::Cross(camera.GetTarget(), camera.GetUp()))) * cameraSpeed, 0.0f, 0.0f));
					break;
				case SDLK_ESCAPE: Quit(window, GLContext, SHOULD_CLOSE); break;
				}
			}
		}
		
		shader.SetUniformMat4x4f("uViewMatrix", camera.GetViewMatrix());
		shader.SetUniformVec3f("uLightPos", light.GetPosition());
		shader.SetUniformVec3f("uLightColor", light.GetColor());
		shader.SetUniformVec3f("uViewPos", camera.GetPosition());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		glDrawArrays(GL_TRIANGLES, 0, model.GetMesh()->GetNumOfTriangles());

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Look At: [%.3f], [%.3f], [%.3f]", camera.GetViewMatrix()(0,2), camera.GetViewMatrix()(1, 2), camera.GetViewMatrix()(2, 2));

		if (ImGui::Button("Set Fullscreen Mode", ImVec2(150.0f, 30.0f)) == 1) { SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); }; ImGui::SameLine();
		if (ImGui::Button("Set Windowed Mode", ImVec2(150.0f, 30.0f)) == 1) { SDL_SetWindowFullscreen(window, 0); };

		ImGui::SliderFloat("Scale on X", &scaleVector.at(0), 0.1f, 2.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("Scale on Y", &scaleVector.at(1), 0.1f, 2.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("Scale on Z", &scaleVector.at(2), 0.1f, 2.0f, "%.2f", 1.0f);
		ImGui::SliderFloat("Rotate on X", &rotateVector.at(0), -360.0f, 360.0f, "%.0f deg", 1.0f);
		ImGui::SliderFloat("Rotate on Y", &rotateVector.at(1), -360.0f, 360.0f, "%.0f deg", 1.0f);
		ImGui::SliderFloat("Rotate on Z", &rotateVector.at(2), -360.0f, 360.0f, "%.0f deg", 1.0f);
		ImGui::SliderFloat("Translate on X", &translationVector.at(0), -0.5f, 0.5f, "%.2f", 1.0f);
		ImGui::SliderFloat("Translate on Y", &translationVector.at(1), -0.5f, 0.5f, "%.2f", 1.0f);
		ImGui::SliderFloat("Translate on Z", &translationVector.at(2), -0.5f, 0.5f, "%.2f", 1.0f);

		if(ImGui::Button("Update Model Matrix", ImVec2(150.0f, 30.0f)) == 1) 
		{ 
			model.ScaleModelMatrix(scaleVector.at(0), scaleVector.at(1), scaleVector.at(2));
			model.RotateModelMatrix(rotateVector.at(0), rotateVector.at(1), rotateVector.at(2));
			model.TranslateModelMatrix(translationVector.at(0), translationVector.at(1), translationVector.at(2));
			MainLog.Trace("Model matrix after translation: ", model.GetModelMatrix());
		};
		ImGui::SameLine();
		if (ImGui::Button("Set Model Matrix", ImVec2(150.0f, 30.0f)) == 1) { glUniformMatrix4fv(glGetUniformLocation(shader.GetProgramID(), "uModelMatrix"), 1, GL_FALSE, (float*)model.GetModelMatrix().GetData()); MainLog.Trace("a", model.GetModelMatrix()); };

		if (ImGui::Button("Quit", ImVec2(60.0f, 30.0f)) == 1) { Quit(window, GLContext, SHOULD_CLOSE); break; };

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}

	return 0;
}

bool Init(SDL_Window*& window, SDL_GLContext& GLContext, SDL_Surface*& windowSurface, ImGuiIO& imGuiIO)
{
	std::vector<std::pair<std::string, double>> config;
	ReadConfig("config.ini", config);

	auto sizeXit = std::find_if(config.begin(), config.end(), [](std::pair<std::string, double>& element) { return element.first == "WindowSizeX"; });
	auto sizeYit = std::find_if(config.begin(), config.end(), [](std::pair<std::string, double>& element) { return element.first == "WindowSizeY"; });
	auto isFullscreenit = std::find_if(config.begin(), config.end(), [](std::pair<std::string, double>& element) { return element.first == "WindowedMode"; });
	auto isVSyncit = std::find_if(config.begin(), config.end(), [](std::pair<std::string, double>& element) { return element.first == "VSync"; });

	unsigned int windowSizeX = sizeXit->second;
	unsigned int windowSizeY = sizeYit->second;
	bool isFullScreen = !isFullscreenit->second;
	bool isVSync = isVSyncit->second;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("Unitato Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	GLContext = SDL_GL_CreateContext(window);

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		MainLog.Error("SDL_image could not initialize!");
		return false;
	}
	else
	{
		windowSurface = SDL_GetWindowSurface(window);
	}

	glViewport(0, 0, windowSizeX, windowSizeY);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(isVSync);

	SDL_SetWindowFullscreen(window, isFullScreen);
	SDL_ShowCursor(SDL_DISABLE);

	MainLog.Info("SDL initialized successfully!");

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		MainLog.Error("Glew could not initialize!");
		return false;
	}
	MainLog.Info("Glew initialized successfully!");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	imGuiIO = ImGui::GetIO(); (void)imGuiIO;

	if ((ImGui_ImplSDL2_InitForOpenGL(window, GLContext) && ImGui_ImplOpenGL3_Init()) == false)
	{
		MainLog.Error("ImGui could not been initialized!");
		return false;
	}
	ImGui::StyleColorsDark();
	MainLog.Info("ImGui initialized successfully!");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

void Quit(SDL_Window*& window, SDL_GLContext& GLContext, bool& exited)
{
	MainLog.Info("Shutting down ImGui ...");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	MainLog.Info("Deleting OpenGL Context ...");
	SDL_GL_DeleteContext(GLContext);

	MainLog.Info("Deleting SDL Context ...");
	SDL_DestroyWindow(window);
	SDL_Quit();

	exited = true;
}

void MouseCallback(float w, float h, std::tuple<float, float, float>& direction, int& mousePosX, int& mousePosY, bool& isFirstMouseMove, float mouseSensitivity, float& yaw, float& pitch)
{
	SDL_WarpMouseInWindow(NULL, (w / 2), (h / 2));
	float lastX = w / 2, lastY = h / 2;

	if (isFirstMouseMove)
	{
		lastX = mousePosX;
		lastY = mousePosY;
		isFirstMouseMove = false;
	}

	float xOffset = mousePosX - lastX;
	float yOffset = lastY - mousePosY;
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;
	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	direction = { cos(Math::ToRadian(yaw)) * cos(Math::ToRadian(pitch)), sin(Math::ToRadian(pitch)), sin(Math::ToRadian(yaw)) * cos(Math::ToRadian(pitch)) };
	direction = Math::Normalize(direction);
}