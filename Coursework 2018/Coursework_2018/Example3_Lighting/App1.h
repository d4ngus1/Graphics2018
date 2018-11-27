// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "LightShader.h"
#include "LightShaderSpecular.h"
#include "Manipulation.h"
#include "Timer.h"
#include "HeightMapShader.h"
#include "WaterShader.h"


class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);
	void CameraPositions(int index);
	bool frame();

protected:
	bool render();
	void gui();

private:
	//plane mesh for height map 
	PlaneMesh* landPlaneMesh;
	HeightMapShader* heightMapShader;
	//sphere mesh for the moon 
	SphereMesh* moonSphereMesh;
	//plane mesh for the water 
	PlaneMesh* waterPlaneMesh;
	WaterShader* waterShader;

	LightShader* shader;
	LightShaderSpecular * specShader;
	Manipulation* manipulation;
	XMFLOAT4 manipulationValues;
	SphereMesh* mesh;
	CubeMesh* cubeMesh;
	Light* light;

	int frequency = 1;
};

#endif