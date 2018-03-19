#include "TrianglePolygonListCollider.h"

using namespace NYLibrary;

/// <summary>
/// 全てのポリゴンと線で当たり判定を行う
/// </summary>
/// <param name="segment"></param>
void TrianglePolygonListCollider::Collision(SegmentCollider* segment)
{
	CheckSegment2AllTriangle(segment, this);
}


