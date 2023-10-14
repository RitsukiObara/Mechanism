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
#include "debugproc.h"
#include "collpolygon.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define MOVE_DISTANCE		(1200.0f)							// 移動する距離
#define MOVE				(D3DXVECTOR3(3.0f, 0.0f, 0.0f))		// 移動量
#define CHECK_COUNT			(10)								// チェックするカウント数

//==============================
// コンストラクタ
//==============================
CItocan::CItocan() : CEnemy(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_state = STATE_STOP;		// 状態
	m_nStateCount = 0;			// 状態カウント
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

	// 全ての値をクリアする
	m_state = STATE_STOP;		// 状態
	m_nStateCount = 0;			// 状態カウント

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
	// 前回の位置を設定する
	SetPosOld(GetPos());

	if (m_nStateCount % CHECK_COUNT == 0)
	{ // 一定カウント数になった場合

		// プレイヤーの判定処理
		CheckPlayer();
	}

	// 状態の判定処理
	CheckState();

	switch (m_state)
	{
	case STATE_STOP:		// 停止状態

		break;

	case STATE_MOVE:		// 移動状態

		// 移動処理
		Move();

		break;
	}

	// 重力処理
	Gravity();

	// 起伏地面との当たり判定
	ElevationCollision();

	// 状態カウントを加算する
	m_nStateCount++;
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

	// 全ての値をクリアする
	m_state = STATE_STOP;			// 状態
	m_nStateCount = 0;			// 状態カウント

	// 情報の設定処理
	SetEnableStep(true);			// 踏みつけられる設定
	SetMove(MOVE);					// 移動量
}

//=======================================
// プレイヤーの判定処理
//=======================================
void CItocan::CheckPlayer(void)
{
	if (CPlayer::Get() != nullptr)
	{ // プレイヤーの情報がある場合

		// ローカル変数宣言
		D3DXVECTOR3 posPlayer = CPlayer::Get()->GetPos();	// プレイヤーの位置
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
}

//=======================================
// 状態の判定処理
//=======================================
void CItocan::CheckState(void)
{
	// ローカルポインタ宣言
	CPlayer* pPlayer = CPlayer::Get();		// プレイヤーの情報を取得する
	D3DXVECTOR3 pos = GetPos();				// 位置

	if (pPlayer != nullptr)
	{ // プレイヤーの情報がある場合

		if (fabsf(pos.x - pPlayer->GetPos().x) <= MOVE_DISTANCE)
		{ // 一定距離内の場合

			// 移動状態にする
			m_state = STATE_MOVE;
		}
		else
		{ // 上記以外

			// 位置を設定する
			pos = GetInitPos();

			// 前回の位置を設定する
			SetPosOld(GetInitPos());

			// 停止状態にする
			m_state = STATE_STOP;
		}
	}
	else
	{ // 上記以外

		// 停止状態にする
		m_state = STATE_STOP;
	}

	// 情報を適用する
	SetPos(pos);		// 位置
}

//=======================================
// 移動処理
//=======================================
void CItocan::Move(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き
	D3DXVECTOR3 move = GetMove();	// 移動量

	// 移動量を設定する
	pos.x += sinf(-rot.y) * move.x;

	// 位置を設定する
	SetPos(pos);
}