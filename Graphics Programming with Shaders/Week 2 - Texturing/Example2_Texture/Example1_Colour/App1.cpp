// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"


App1::App1()
{
	mesh = nullptr;
	newMesh = nullptr;
	textureShader = nullptr;
	newTextureShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	textureMgr->loadTexture("brick", L"../res/brick1.dds");
	textureMgr->loadTexture("bunny", L"../res/bunny.png");

	// Create Mesh object and shader object
	mesh = new TexturedQuad(renderer->getDevice(), renderer->getDeviceContext());
	textureShader = new TextureShader(renderer->getDevice(), hwnd);

	//creates the second quad
	newMesh = new TexturedQuad(renderer->getDevice(), renderer->getDeviceContext());
	newTextureShader = new TextureShader(renderer->getDevice(), hwnd);
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

	//release the new quad
	if (newMesh)
	{
		delete newMesh;
		newMesh = 0;
	}

	if (textureShader)
	{
		delete textureShader;
		textureShader = 0;
	}

	if (newTextureShader)
	{
		delete newTextureShader;
		newTextureShader = 0;
	}
}


bool App1::frame()
{
	bool result;
	
	//rotates the shape
	rotate += 0.1f;
	//constant rotate
	constantRotate = XMMatrixRotationRollPitchYaw(0.0, 0.0, rotate);
	
	//keyboard controls 
	if(input->isKeyDown('K'))
	{
		rotate2 += 1;
		//input->SetKeyUp('k');
	}
	if (input->isKeyDown('L'))
	{
		rotate2 -= 1;
		//input->SetKeyUp('l');
	}

	//controlled rotate to be passed in
	controlledRotate = XMMatrixRotationRollPitchYaw(0.0, 0.0, rotate2);

	//rotates and moves
	fullMove = XMMatrixMultiply(controlledRotate, newQuadPosition);

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
	//translation for moving it across two 
	newQuadPosition = XMMatrixTranslation(4.0, 0.0, 0.0);
	

	// Send geometry data, set shader parameters, render object with shader
	mesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), constantRotate, viewMatrix, projectionMatrix, textureMgr->getTexture("bunny"));
	textureShader->render(renderer->getDeviceContext(), mesh->getIndexCount());

	//new geometry for new quad
	newMesh->sendData(renderer->getDeviceContext());
	newTextureShader->setShaderParameters(renderer->getDeviceContext(), fullMove, viewMatrix, projectionMatrix, textureMgr->getTexture("brick"));
	newTextureShader->render(renderer->getDeviceContext(), mesh->getIndexCount());

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

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

