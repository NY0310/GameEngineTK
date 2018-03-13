/// <summary>
/// GameObjectNode
/// 2017/10/13
/// Yusuke Nakata
/// </summary>

#include "GameObjectNode.h"

using namespace std;
using namespace NYLibrary;
//::GameObjectNode::GameObjectNode(shared_ptr<GameObjectInterface>&& gameobject)
//	:Node()
//{
//	gameObject  = move(gameobject);
//}

void RootGameObjectNode::LoopInitialize()
{
	for (auto& child : children) {
		child->LoopInitialize();
	}
}

void NYLibrary::RootGameObjectNode::LoopCreateAddChild()
{
	for (auto& child : children) {
		child->LoopCreateAddChild();
	}

}

void RootGameObjectNode::LoopUpdate()
{
	for (auto& child : children) {
		child->LoopUpdate();
	}

}

void RootGameObjectNode::LoopRender()
{
	for (auto& child : children) {
		child->LoopRender();
	}
}

void RootGameObjectNode::LoopFinalize()
{
	for (auto& child : children) {
		child->LoopFinalize();
	}

}


/// <summary>
/// �m�[�h�𕡐�����(�ċN�֐�)
/// </summary>
/// <returns>���������m�[�h</returns>
shared_ptr<NodeAbstract> RootGameObjectNode::Clone()
{

	auto clone = make_shared<RootGameObjectNode>(*this);

	// ���X�g���N���A����
	clone->GetChildren().clear();

	for (auto& child : children)
	{
		clone->AddChild(child->Clone());
	}
	return clone;


}







/// <summary>
/// GameObjectNode
/// 2017/10/13
/// Yusuke Nakata
/// </summary>

void GameObjectNodeEmpty::LoopCreateAddChild()
{
	this->CreateAddChild();
	for (auto& child : children) {
		child->LoopCreateAddChild();
	}
}

void GameObjectNodeEmpty::LoopInitialize()
{
	this->Initialize();
	for (auto& child : children) {
		child->LoopInitialize();
	}
}

void GameObjectNodeEmpty::LoopUpdate()
{
	this->Update();
	for (auto& child : children) {
		child->LoopUpdate();
	}

}

void GameObjectNodeEmpty::LoopRender()
{
	this->Render();
	for (auto& child : children) {
		child->LoopRender();
	}

}

void GameObjectNodeEmpty::LoopFinalize()
{
	this->Finalize();
	for (auto& child : children) {
		child->LoopFinalize();
	}

}


/// <summary>
/// �m�[�h�𕡐�����(�ċN�֐�)
/// </summary>
/// <returns>���������m�[�h</returns>
shared_ptr<NodeAbstract>  GameObjectNodeEmpty::Clone()
{

	auto clone = make_shared<GameObjectNodeEmpty>(*this);

	// ���X�g���N���A����
	clone->GetChildren().clear();

	for (auto& child : children)
	{
		clone->AddChild(child->Clone());
	}
	return clone;


}




void GameObjectNode::LoopUpdate()
{
	this->Update();
	this->Calc();
	for (auto& child : children) {
		child->LoopUpdate();
	}

}