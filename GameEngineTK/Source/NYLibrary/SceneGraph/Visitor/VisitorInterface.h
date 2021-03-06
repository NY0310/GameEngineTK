/// <summary>
/// ビジタークラス
/// Yusuke Nakata
/// 2017/10/13
/// </summary>
#pragma once

#include <memory>

namespace NYLibrary
{
	class Node;
	class Leaf;
	//ビジターのインターフェイス
	class VisitorInterface
	{
	public:
		//コンストラクタ
		VisitorInterface() = default;
		//デストラクタ
		~VisitorInterface() = default;
		//コピーコンストラクタ使用不可
		VisitorInterface(const VisitorInterface&) = delete;
		//代入禁止
		VisitorInterface& operator=(const VisitorInterface&) = delete;
		//ノード専用の検索関数
		virtual void Visit(std::shared_ptr<NYLibrary::NodeAbstract> node) = 0;
		//リーフ専用の検索関数
		virtual void Visit(std::shared_ptr<NYLibrary::Leaf> leaf) = 0;

	};
}


