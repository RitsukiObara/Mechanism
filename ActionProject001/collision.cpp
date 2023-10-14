//===========================================
//
// 当たり判定のメイン処理[collision.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "player.h"
#include "player_act.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "screw.h"
#include "screw_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "useful.h"

//===============================
// マクロ定義
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// 僅かな誤差を埋めるためのマクロ定義(突っかかり防止)
#define AIRPLANE_COLL_RADIUS			(55.0f)			// 飛行機の当たり判定時の半径
#define PLAYER_SIZE						(D3DXVECTOR3(20.0f,70.0f,20.0f))	// プレイヤーのサイズ
#define PLAYER_HALF_HEIGHT				(PLAYER_SIZE.y / 2)					// プレイヤーの高さの半分
#define SCREW_COLL_RADIUS				(20.0f)			// ネジの当たり判定時の半径

//===============================
// 丸影の起伏地面の当たり判定処理
//===============================
void collision::ShadowElevCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ローカル変数宣言
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// 影のポインタ
	CElevation* pMesh = nullptr;			// メッシュのポインタ
	D3DXVECTOR3 posShadow = pos;				// 影の位置

	if (pShadow != nullptr)
	{ // 影のポインタが NULL じゃなかった場合

		// オブジェクトのポインタを取得する
		pMesh = CElevationManager::Get()->GetTop();

		while (pMesh != nullptr)
		{ // オブジェクトのが NULL じゃない限り回す

			// 影の位置を設定する
			posShadow.y = pMesh->ElevationCollision(posShadow);

			// 次のオブジェクトを代入する
			pMesh = pMesh->GetNext();
		}

		// 位置を設定する
		pShadow->SetPos(posShadow);
	}
}

//===============================
// プレイヤーと飛行機との当たり判定
//===============================
void collision::AirplaneHit(CPlayer& player)
{
	// ローカル変数宣言
	CAirplane* pAirplane = nullptr;	// 影のポインタ
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// プレイヤーの位置
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// 最大値
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// 最小値
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// 最大値
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// 最小値

	// オブジェクトのポインタを取得する
	pAirplane = CAirplaneManager::Get()->GetTop();

	while (pAirplane != nullptr)
	{ // オブジェクトのが NULL じゃない限り回す

		if (useful::RectangleCollisionXY(pAirplane->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pAirplane->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // 矩形の当たり判定が true の場合

			if (player.GetAction()->GetAct() != CPlayerAct::ACT_CANNON &&
				player.GetAction()->GetAct() != CPlayerAct::ACT_FLY)
			{ // 状態が大砲待機以外の場合

				// プレイヤーの位置を設定する
				player.SetPos(pAirplane->GetPos());

				// 状態の設定処理
				player.GetAction()->SetAct(CPlayerAct::ACT_CANNON);
			}

			// この先の処理を抜け出す
			return;
		}

		// 次のオブジェクトを代入する
		pAirplane = pAirplane->GetNext();
	}
}

//===============================
// プレイヤーとネジとの当たり判定
//===============================
void collision::ScrewHit(CPlayer& player)
{
	// ローカル変数宣言
	CScrew* pScrew = CScrewManager::Get()->GetTop();	// ネジのポインタ
	CScrew* pScrewNext = nullptr;						// 次のネジのポインタ
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// プレイヤーの位置
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// 最大値
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// 最小値
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// 最大値
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// 最小値

	while (pScrew != nullptr)
	{ // オブジェクトのが NULL じゃない限り回す

		// 次のネジの情報を取得する
		pScrewNext = pScrew->GetNext();

		if (useful::RectangleCollisionXY(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // 矩形の当たり判定が true の場合

			// ヒット処理
			pScrew->Hit(pScrew->GetPos());
		}

		// 次のオブジェクトを代入する
		pScrew = pScrewNext;
	}
}

//===============================
// プレイヤーと敵との当たり判定
//===============================
void collision::EnemyHit(CPlayer& player)
{
	// ローカル変数宣言
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// 敵の情報
	CEnemy* pEnemyNext = nullptr;							// 次の敵の情報
	D3DXVECTOR3 pos = player.GetPos();						// プレイヤーの位置
	D3DXVECTOR3 posOld = player.GetPosOld();				// プレイヤーの前回の位置

	while (pEnemy != nullptr)
	{ // 敵の情報が NULL じゃない場合

		// 敵の情報を取得する
		pEnemyNext = pEnemy->GetNext();

		if (pEnemy->GetPos().z + pEnemy->GetFileData().collsize.z >= pos.z &&
			pEnemy->GetPos().z - pEnemy->GetFileData().collsize.z <= pos.z)
		{ // 敵とZ軸が合っている場合

			if (posOld.y >= pEnemy->GetPosOld().y + pEnemy->GetFileData().vtxMax.y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMax.y &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMin.x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMax.x)
			{ // 上からの当たり判定

				if (pEnemy->IsStep() == true)
				{ // 踏みつけられるの場合

					// 敵のヒット処理
					pEnemy->Hit();

					// 踏みつけ時の処理
					player.StepHit();
				}
				else
				{ // 上記以外

					// プレイヤーのヒット処理
					player.Hit();
				}
			}
			else if (posOld.y + PLAYER_SIZE.y <= pEnemy->GetPosOld().y + pEnemy->GetFileData().vtxMin.y &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMin.y &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMin.x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMax.x)
			{ // 下からの当たり判定

				// プレイヤーのヒット処理
				player.Hit();
			}
			else if (posOld.x + PLAYER_SIZE.x <= pEnemy->GetPosOld().x + pEnemy->GetFileData().vtxMin.x &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMin.x &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMin.y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMax.y)
			{ // 左からの当たり判定

				// プレイヤーのヒット処理
				player.Hit();
			}
			else if (posOld.x - PLAYER_SIZE.x >= pEnemy->GetPosOld().x + pEnemy->GetFileData().vtxMax.x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetFileData().vtxMax.x &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMin.y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetFileData().vtxMax.y)
			{ // 右からの当たり判定

				// プレイヤーのヒット処理
				player.Hit();
			}
		}

		// 次のオブジェクトを代入する
		pEnemy = pEnemyNext;
	}
}