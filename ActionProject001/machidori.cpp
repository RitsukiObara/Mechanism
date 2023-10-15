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
#include "machidori.h"
#include "useful.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "player.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define MOVE_DISTANCE			(1400.0f)								// 移動する距離
#define COLLISION_SIZE			(D3DXVECTOR3(40.0f, 93.0f, 44.0f))		// 当たり判定のサイズ
#define ROT_MOVE				(0.05f)									// 向きの移動量
#define ADD_HEIGHT				(300.0f)								// 追加する高さ
#define CURVE_HEIGHT			(50.0f)									// 浮き沈みの差

//==============================
// コンストラクタ
//==============================
CMachidori::CMachidori() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_state = STATE_FLY;	// 状態
	m_fCurveRot = 0.0f;		// カーブ用向き
	m_bRight = true;		// 前回の右向き状況
}

//==============================
// デストラクタ
//==============================
CMachidori::~CMachidori()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CMachidori::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_state = STATE_FLY;	// 状態
	m_fCurveRot = 0.0f;		// カーブ用向き
	m_bRight = true;		// 前回の右向き状況

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CMachidori::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//========================================
//ブロックの更新処理
//========================================
void CMachidori::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_FLY:

		// 起伏地面の当たり判定
		Elevation();

		// 高さの設定処理
		Height();

		// プレイヤーの判定処理
		CheckPlayer();

		// 移動処理
		Move();

		break;

	case STATE_STANDBY:

		break;

	case STATE_ATTACK:

		break;
	}
}

//=====================================
//ブロックの描画処理
//=====================================
void CMachidori::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=====================================
// ヒット処理
//=====================================
void CMachidori::Hit(void)
{

}

//=====================================
// 情報の設定処理
//=====================================
void CMachidori::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	CEnemy::SetData(pos);

	// モデルの情報を設定する
	SetFileData(CXFile::TYPE_MACHIDORI);

	// 全ての値を設定する
	m_state = STATE_FLY;	// 状態
	m_fCurveRot = 0.0f;		// カーブ用向き

	// 情報の設定処理
	SetEnableStep(true);			// 踏みつけられる設定
	SetCollSize(COLLISION_SIZE);	// 当たり判定のサイズ

	// 前回の左右状況の設定処理
	SetRightOld();
}

//=====================================
// プレイヤーの判断処理
//=====================================
void CMachidori::CheckPlayer(void)
{
	if (CPlayer::Get() != nullptr)
	{ // プレイヤーの情報がある場合

		// ローカル変数宣言
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// プレイヤーの位置
		D3DXVECTOR3 pos = GetPos();		// 位置を取得する
		D3DXVECTOR3 move = GetMove();	// 移動量を取得する

		if (posPlayer.x >= pos.x)
		{ // プレイヤーの位置が自身よりも右にいる場合

			// 向きを設定する
			move.x = 2.0f;

			if (m_bRight == false)
			{ // 前回が左向きの場合

				// スタンバイ状態にする
				m_state = STATE_STANDBY;
			}
		}
		else
		{ // 上記以外

			// 向きを設定する
			move.x = -2.0f;

			if (m_bRight == true)
			{ // 前回が右向きの場合

				// スタンバイ状態にする
				m_state = STATE_STANDBY;
			}
		}

		// 移動量を適用する
		SetMove(move);
	}
}

//=====================================
// 移動処理
//=====================================
void CMachidori::Move(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();			// 位置を取得する
	D3DXVECTOR3 move = GetMove();		// 移動量を取得する

	// 位置を設定する
	pos.x += move.x;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
// 高さ設定処理
//=====================================
void CMachidori::Height(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する

	// カーブ用の向きを加算する
	m_fCurveRot += ROT_MOVE;

	// 向きの正規化
	useful::RotNormalize(&m_fCurveRot);

	// 位置を設定する
	pos.y += sinf(m_fCurveRot) * CURVE_HEIGHT + ADD_HEIGHT;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
// 起伏地面の当たり判定
//=====================================
void CMachidori::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		// 高さを設定する
		pos.y = fHeight;

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// 前回の左右状況の設定処理
//=====================================
void CMachidori::SetRightOld(void)
{
	if (CPlayer::Get() != nullptr)
	{ // プレイヤーの情報がある場合

		// ローカル変数宣言
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// プレイヤーの位置
		D3DXVECTOR3 pos = GetPos();		// 位置を取得する

		if (posPlayer.x >= pos.x)
		{ // プレイヤーの位置が自身よりも右にいる場合

			// 右に設定する
			m_bRight = true;
		}
		else
		{ // 上記以外

			// 左に設定する
			m_bRight = false;
		}
	}
}