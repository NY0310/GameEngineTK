#include "CollisitionManager.h"

using namespace std;

/// <summary>
/// CollisitionManagerを取得する
/// </summary>
/// <returns>CollisitionManager</returns>
CollisitionManager * CollisitionManager::GetInstance()
{
	if (!collisitionManager)
	{
		collisitionManager = make_unique<CollisitionManager>();
	}
	return collisitionManager.get();
}
