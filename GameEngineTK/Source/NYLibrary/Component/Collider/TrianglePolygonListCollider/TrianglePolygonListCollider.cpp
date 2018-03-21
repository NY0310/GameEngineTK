#include "TrianglePolygonListCollider.h"

using namespace NYLibrary;

TrianglePolygonListCollider::TrianglePolygonListCollider(std::string tag, Element * matrixObject)
	:Collider(tag, matrixObject)
{
	
}

void TrianglePolygonListCollider::Initialize()
{
	triangleList = matrixObject->GetPolygons();
	RegisterCollider();
}

void TrianglePolygonListCollider::Update()
{
	Collider::Update();
	collisionTriangle;
	inter = D3DXVECTOR3(0, 0, 0);
}

/// <summary>
/// 全てのポリゴンと線で当たり判定を行う
/// </summary>
/// <param name="segment"></param>
void TrianglePolygonListCollider::Collision(SegmentCollider* segment)
{
	CheckSegment2AllTriangle(segment, this);
}


