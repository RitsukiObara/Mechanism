//===========================================
//
// イトキャンのメイン処理[itocan.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "itocan.h"
#include "collision.h"
#include "useful.h"

#include "player.h"

//==============================
// コンストラクタ
//==============================
CItocan::CItocan() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{

}

//==============================
// デストラクタ
//==============================
CItocan::~CItocan()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CItocan::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CItocan::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//========================================
//ブロックの更新処理
//========================================
void CItocan::Update(void)
{
	// プレイヤーの判定処理
	CheckPlayer();

	// 重力処理
	Gravity();

	// 起伏地面との当たり判定
	ElevationCollision();
}

//=====================================
//ブロックの描画処理
//=====================================
void CItocan::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=====================================
// ヒット処理
//=====================================
void CItocan::Hit(void)
{

}

//=====================================
// 情報の設定処理
//=====================================
void CItocan::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	CEnemy::SetData(pos);
}

//=======================================
// プレイヤーの判定処理
//=======================================
void CItocan::CheckPlayer(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// プレイヤーの位置を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	D3DXVECTOR3 rot = GetRot();		// 向きを取得する

	if (posPlayer.x >= pos.x)
	{ // プレイヤーの位置が自身よりも右にいる場合

		// 向きを設定する
		rot.y = -D3DX_PI * 0.5f;
	}
	else
	{ // 上記以外

		// 向きを設定する
		rot.y = D3DX_PI * 0.5f;
	}

	// 向きを設定する
	SetRot(rot);
}