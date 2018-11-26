#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class LightShaderSpecular : public BaseShader
{
private:
	struct LightBufferType
	{
		
		XMFLOAT4 diffuse;
		XMFLOAT4 specularColour;
		XMFLOAT4 ambientColour;
		XMFLOAT4 diffuseColour;
		XMFLOAT3 lightDirection;
		float specularPower;
		
	};

public:
	LightShaderSpecular(ID3D11Device* device, HWND hwnd);
	~LightShaderSpecular();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light);

private:
	void initShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11Buffer * cameraBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* lightBuffer;
};

