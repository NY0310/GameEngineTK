/***************************************************************************
*|
*|	概要　　衝突判定ライブラリ
*|　作成者　GS2 16 中田湧介
*|　作成日　2017//
*|___________________________________________________________________________
****************************************************************************/
#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>


//球
class Sphere
{
public:
	//中心座標
	DirectX::SimpleMath::Vector3 Center;
	//半径
	float Radius;
	//コンストラクタ
	Sphere() {
		//デフォルトの背景を1メートルにする
		Radius = 1.0f;
	}
};


//線分
class Segment
{
public:
	//始点座標
	DirectX::SimpleMath::Vector3 Start;
	//終了地点
	DirectX::SimpleMath::Vector3 End;
};

//三角形
class Triangle
{
public:
	//頂点の座標
	DirectX::SimpleMath::Vector3 P0;
	DirectX::SimpleMath::Vector3 P1;
	DirectX::SimpleMath::Vector3 P2;
	//法線ベクトル
	DirectX::SimpleMath::Vector3 Normal;
private:
};


bool CheckSpere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
void ComputeTriangle(const DirectX::SimpleMath::Vector3 & a, const DirectX::SimpleMath::Vector3 & b, const DirectX::SimpleMath::Vector3 & _p2, Triangle* c);

bool CheckSphere2Triangle(const Sphere & _sphere, const Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
