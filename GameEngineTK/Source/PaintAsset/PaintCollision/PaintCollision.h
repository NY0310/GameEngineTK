#pragma once
#include <vector>
#include "../../NYLibrary/Math/Math.h"
#include "../../NYLibrary/Collision/Collision.h"
#include "../../NYLibrary/Camera/FollowCamera.h"

using namespace NYLibrary;
class PaintCollision
{
public:
	PaintCollision() = default;
	~PaintCollision() = default;
	void SetTriangles(const std::vector<Triangle>& triandles) { this->triangles = triandles; }
	void SetWorldMatrix(D3DXMATRIX worldmatrix) { worldMatrix = worldmatrix; };
	bool IntersectSegment(Segment* segment, D3DXVECTOR2 & uv);
	bool IntersectSphere(Sphere* sphere, D3DXVECTOR2 & uv);
private:
	//bool IntersectSphere(const Sphere & sphere);
	std::vector<Triangle> triangles;
	D3DXMATRIX worldMatrix;
	FollowCamera* camera = FollowCamera::GetInstance();
	DirectX::SimpleMath::Vector4 MatrixTimes(const DirectX::SimpleMath::Matrix & matrix, const DirectX::SimpleMath::Vector4 & vector);

};

