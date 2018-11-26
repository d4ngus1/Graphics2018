// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	mesh = nullptr;
	shader = nullptr;
	specShader = nullptr;
	planeMesh = nullptr;
	manipulation = nullptr;
	cubeMesh = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	textureMgr->loadTexture("brick", L"../res/brick1.dds");

	// Create Mesh object and shader object
	mesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	planeMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	cubeMesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	shader = new LightShader(renderer->getDevice(), hwnd);
	specShader = new LightShaderSpecular(renderer->getDevice(), hwnd);
	manipulation = new Manipulation(renderer->getDevice(), hwnd);
	light = new Light;
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setAmbientColour(1.1f, 1.1f, 1.1f, 1.0f);
	light->setSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setSpecularPower(50);
	light->setDirection(1.0f, 0.0f, 0.0f);

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (mesh)
	{
		delete mesh;
		mesh = 0;
	}

	if (shader)
	{
		delete shader;
		shader = 0;
	}

	if (specShader)
	{
		delete specShader;
		specShader = 0;
	}

	if (manipulation)
	{
		delete manipulation;
		manipulation = 0;
	}

	if (planeMesh)
	{
		delete planeMesh;
		planeMesh = 0;
	}

	if (cubeMesh)
	{
		delete cubeMesh;
		cubeMesh = 0;
	}
}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();
	projectionMatrix = renderer->getProjectionMatrix();

	//plane mesh
	planeMesh->sendData(renderer->getDeviceContext());

	//cube
	//cubeMesh->sendData(renderer->getDeviceContext());

	// Send geometry data, set shader parameters, render object with shader
	//mesh->sendData(renderer->getDeviceContext());
	//specShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("brick"), light);
	//specShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	manipulation->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("brick"), light, manipulationValues.x, manipulationValues.y, manipulationValues.z,manipulationValues.w);
	manipulation->render(renderer->getDeviceContext(), cubeMesh->getIndexCount());

	

	// Render GUI
	gui();

	// Swap the buffers
	renderer->endScene();

	return true;
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	ImGui::SliderFloat("time", &manipulationValues.x, 0, 10);
	ImGui::SliderFloat("height", &manipulationValues.y, 0, 10);
	ImGui::SliderFloat("frequency", &manipulationValues.z, 0, 10);
	ImGui::SliderFloat("speed", &manipulationValues.w, 0, 10);


	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

