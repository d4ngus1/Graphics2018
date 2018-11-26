#pragma once

#include "DXF.h"

using namespace DirectX;

class QuadMeshClass : public BaseMesh
{
public:
	QuadMeshClass(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~QuadMeshClass();

	virtual void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top = D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
protected:
	void initBuffers(ID3D11Device* device);

private:
	void CreatePlane(VertexType_Colour* vertices, unsigned long* indices);
};

