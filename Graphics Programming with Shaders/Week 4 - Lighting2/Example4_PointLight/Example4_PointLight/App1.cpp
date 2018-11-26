// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	mesh = nullptr;
	shader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);
	camera->setPosition(50, 125, 50);
	camera->setRotation(0, 0, 90);
	// Create Mesh object and shader object
	mesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	textureMgr->loadTexture("brick", L"../res/brick1.dds");
	shader = new LightShader(renderer->getDevice(), hwnd);
	light = new Light;
	light->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setPosition(50.0f, 10.0f, 50.0f);

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
}

void App1::inputMan()
{
	lightPos.x = light->getPosition().x;
	lightPos.y = light->getPosition().y;
	lightPos.z = light->getPosition().z;
	lightColour.x = light->getDiffuseColour().x;
	lightColour.y = light->getDiffuseColour().y;
	lightColour.z = light->getDiffuseColour().z;

	//in and out
	if (input->isKeyDown('Q')) lightPos.y += 1;
	if (input->isKeyDown('E')) lightPos.y -= 1;
	//left and right
	if (input->isKeyDown('D')) lightPos.x += 1;
	if (input->isKeyDown('A')) lightPos.x -= 1;
	//up and down
	if (input->isKeyDown('W')) lightPos.z += 1;
	if (input->isKeyDown('S')) lightPos.z -= 1;

	//red
	if (input->isKeyDown('R')) lightColour.x += 1;
	if (input->isKeyDown('T')) lightColour.x -= 1;
	//green
	if (input->isKeyDown('G')) lightColour.y += 1;
	if (input->isKeyDown('H')) lightColour.y -= 1;
	//blue
	if (input->isKeyDown('B')) lightColour.z += 1;
	if (input->isKeyDown('N')) lightColour.z -= 1;

	//update the light position
	light->setPosition(lightPos.x, lightPos.y, lightPos.z);
	//update the light colour 
	light->setDiffuseColour(lightColour.x, lightColour.y, lightColour.z, 1);
}

bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}
	
	inputMan();

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

	// Send geometry data, set shader parameters, render object with shader
	mesh->sendData(renderer->getDeviceContext());

	//this where the data gets sent to the gpu 
	shader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("brick"), light);
	shader->render(renderer->getDeviceContext(), mesh->getIndexCount());

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
	ImGui::Text("Press E to raise camera \nto see the plane being rendered");
	
	ImGui::Text("LightPosX: %.2f, LightPosY: %.2f, LightPosZ: %.2f", light->getPosition().x, light->getPosition().y, light->getPosition().z);
	ImGui::Text("LightRGBA: %.2f, %.2f, %.2f, %.2f", light->getDiffuseColour().x, light->getDiffuseColour().y, light->getDiffuseColour().z, 1);

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

