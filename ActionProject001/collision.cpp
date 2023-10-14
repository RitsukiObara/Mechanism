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
	CScrew* pScrew = nullptr;	// 影のポインタ
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// プレイヤーの位置
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// 最大値
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// 最小値
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// 最大値
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// 最小値

	// オブジェクトのポインタを取得する
	pScrew = CScrewManager::Get()->GetTop();

	while (pScrew != nullptr)
	{ // オブジェクトのが NULL じゃない限り回す

		if (useful::RectangleCollisionXY(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // 矩形の当たり判定が true の場合

			// ヒット処理
			pScrew->Hit(pScrew->GetPos());

			// この先の処理を行わない
			return;
		}

		// 次のオブジェクトを代入する
		pScrew = pScrew->GetNext();
	}
}