// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "TextureShader.h"
#include "ShadowShader.h"
#include "DepthShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void depthPass();
	void finalPass();
	void gui();

private:
	float shapeRotation; 
	XMMATRIX rotationMatrix, resultMatrix;

	TextureShader* textureShader;
	PlaneMesh* meshT;

	Light* light, *light2;
	Model* model;
	CubeMesh* cubeMesh;
	SphereMesh* sphereMesh;
	ShadowShader* shadowShader;
	DepthShader* depthShader;
	OrthoMesh* orthoMesh;
	RenderTexture* shadowMap;
};

#endif