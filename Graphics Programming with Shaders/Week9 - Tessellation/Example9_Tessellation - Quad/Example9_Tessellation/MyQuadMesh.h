#pragma once

#include "DXF.h"

using namespace DirectX;

class MyQuadMesh : public BaseMesh
{
public:
	MyQuadMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~MyQuadMesh();

	virtual void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
protected:
	void initBuffers(ID3D11Device* device);

private:
	void CreatePlane(VertexType_Colour* vertices, unsigned long* indices);
};



