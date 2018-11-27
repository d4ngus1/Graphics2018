// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	//set the mesh to null
	landPlaneMesh = nullptr;
	heightMapShader = nullptr;
	moonSphereMesh = nullptr;
	waterPlaneMesh = nullptr;
	waterShader = nullptr;

	mesh = nullptr;
	shader = nullptr;
	specShader = nullptr;
	manipulation = nullptr;
	cubeMesh = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	textureMgr->loadTexture("heightMap", L"../res/Heightmap5.png");
	textureMgr->loadTexture("MoonMap", L"../res/wood.png");
	textureMgr->loadTexture("Water", L"../res/Water.jpg");

	// Create Mesh object and shader object
	landPlaneMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	heightMapShader = new HeightMapShader(renderer->getDevice(), hwnd);
	moonSphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	waterPlaneMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	waterShader = new WaterShader(renderer->getDevice(), hwnd);

	mesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	cubeMesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	shader = new LightShader(renderer->getDevice(), hwnd);
	specShader = new LightShaderSpecular(renderer->getDevice(), hwnd);
	manipulation = new Manipulation(renderer->getDevice(), hwnd);
	light = new Light;
	light->setDiffuseColour(0.1f, 0.1f, 0.1f, 1.0f);
	light->setAmbientColour(0.3f, 0.3f, 0.3f, 1.0f);
	light->setSpecularColour(0.0f, 1.0f, 1.0f, 1.0f);
	light->setSpecularPower(1);
	light->setDirection(0.0f, -1.0f, 0.0f);

	//set the default camera position
	CameraPositions(2);
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (landPlaneMesh)
	{
		delete landPlaneMesh;
		landPlaneMesh = 0;
	}
	if (heightMapShader)
	{
		delete heightMapShader;
		heightMapShader = 0;
	}
	if (moonSphereMesh)
	{
		delete moonSphereMesh;
		moonSphereMesh = 0;
	}
	if (waterPlaneMesh)
	{
		delete waterPlaneMesh;
		waterPlaneMesh = 0;
	}
	if (waterShader)
	{
		delete waterShader;
		waterShader = 0;
	}

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

	//send the land plane mesh to the height map shader
	landPlaneMesh->sendData(renderer->getDeviceContext());
	heightMapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("heightMap"), light, 25);
	heightMapShader->render(renderer->getDeviceContext(), landPlaneMesh->getIndexCount());
	//send the moon sphere mesh to the height map shader
	moonSphereMesh->sendData(renderer->getDeviceContext());
	heightMapShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("MoonMap"), light, 1);
	heightMapShader->render(renderer->getDeviceContext(), moonSphereMesh->getIndexCount());

	//send the water mesh to the water shader
	worldMatrix = XMMatrixTranslation(0.0f, 1.3f, 0.0f);
	waterPlaneMesh->sendData(renderer->getDeviceContext());
	waterShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture("Water"), light, manipulationValues.x, 0.622f, 1.245f, manipulationValues.w);
	waterShader->render(renderer->getDeviceContext(), waterPlaneMesh->getIndexCount());
	worldMatrix = XMMatrixTranslation(0.0f, -0.5f, 0.0f);

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
	ImGui::Text("Camera Pos: %.1f, %.1f, %.1f", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	ImGui::SliderFloat("time", &manipulationValues.x, 0, 10);
	ImGui::SliderFloat("height", &manipulationValues.y, 0, 10);
	ImGui::SliderFloat("frequency", &manipulationValues.z, 0, 100);
	ImGui::SliderFloat("speed", &manipulationValues.w, 0, 10);

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void App1::CameraPositions(int index)
{
	if (index == 1)
	{
		//top of mountain 
		camera->setPosition(44.7f, 29.3f, 22.4f);
	}
	if (index == 2)
	{
		//top of mountain 
		camera->setPosition(0.0f, 0.0f, 0.0f);
	}
}

