//============================================
//
// プレイヤーのメイン処理[player.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "player.h"
#include "player_act.h"
#include "player_ability.h"
#include "ability_UI.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "useful.h"
#include "texture.h"

#include "camera.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define STEPHIT_JUMP		(20.0f)		// 踏みつけたときのジャンプ力

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPlayer* CPlayer::m_pPlayer = nullptr;		// プレイヤーのポインタ

//=========================================
// コンストラクタ
//=========================================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;			// モーションの情報
	m_pAction = nullptr;			// プレイヤーの行動の情報
	m_pAbility = nullptr;			// 能力の情報
	m_pAbilityUI = nullptr;			// 能力UIの情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_mode = MODE_ACROBAT;			// モード
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_fSpeed = 0.0f;				// 速度
	m_bMove = false;				// 移動状況
	m_bRight = true;				// 右向き状況
	m_bJump = false;				// ジャンプ状況
}

//=========================================
// デストラクタ
//=========================================
CPlayer::~CPlayer()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(14);

	// データの設定処理
	CCharacter::SetData();

	if (m_pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		m_pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 警告文
		MessageBox(NULL, "プレイヤーのモーションのポインタが使われています！", "警告！", MB_ICONWARNING);
	}

	if (m_pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		m_pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		m_pMotion->Load(CMotion::TYPE_PLAYER);
	}
	else
	{ // ポインタが NULL じゃない場合

		// 警告文
		MessageBox(NULL, "プレイヤーのモーションのメモリが確保できませんでした！", "警告！", MB_ICONWARNING);
	}

	// モーションの設定処理
	m_pMotion->Set(MOTIONTYPE_NEUTRAL);

	// プレイヤーの行動状態を生成
	m_pAction = CPlayerAct::Create();

	// 能力の情報を生成
	m_pAbility = CAbility::Create();

	// 能力UIの情報を生成
	m_pAbilityUI = CAbilityUI::Create(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), D3DXVECTOR3(1140.0f, 600.0f, 0.0f));

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_mode = MODE_ACROBAT;			// モード
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_fSpeed = 0.0f;				// 速度
	m_bMove = false;				// 移動状況
	m_bRight = true;				// 右向き状況
	m_bJump = false;				// ジャンプ状況

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CPlayer::Uninit(void)
{
	// モーションのメモリを開放する
	delete m_pMotion;
	m_pMotion = nullptr;

	// 行動の終了処理
	m_pAction->Uninit();
	m_pAction = nullptr;

	// 能力の終了処理
	m_pAbility->Uninit();
	m_pAbility = nullptr;

	// 能力UIの終了処理
	m_pAbilityUI->Uninit();
	m_pAbilityUI = nullptr;

	// 終了処理
	CCharacter::Uninit();

	// プレイヤーを NULL にする
	m_pPlayer = nullptr;
}

//===========================================
// 更新処理
//===========================================
void CPlayer::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	// 行動の更新処理
	m_pAction->Update(*this);

	// モーションの更新処理
	m_pMotion->Update();

	// 起伏地面との当たり判定処理
	ElevationCollision();

	// 飛行機との当たり判定
	collision::AirplaneHit(*this);

	// ネジとの当たり判定
	collision::ScrewHit(*this);

	// 敵との当たり判定
	collision::EnemyHit(*this);

	// 敵とのめり込み判定処理
	collision::EnemyPenetrate(*this);

	// 影の位置向き設定処理
	CShadowCircle::SetPosRotXZ(m_nShadowIdx, GetPos(), GetRot());

	// 行動制限判定
	CollisionMagicWall();

	// プレイヤーの情報を表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n移動量：%f %f %f\nプレイヤーの状態：%d\nジャンプ状況：%d\n", GetPos().x, GetPos().y, GetPos().z, m_move.x, m_move.y, m_move.z, m_pAction->GetAct(), m_bJump);
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CPlayer::Draw(void)
{
	// 描画処理
	CCharacter::Draw();
}

//===========================================
// モーションの情報の設定処理
//===========================================
CMotion* CPlayer::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//===========================================
// アクションの情報の設定処理
//===========================================
CPlayerAct* CPlayer::GetAction(void) const
{
	// 行動状態の情報を返す
	return m_pAction;
}

//===========================================
// 能力の情報の設定処理
//===========================================
CAbility* CPlayer::GetAbility(void) const
{
	// 能力の情報を返す
	return m_pAbility;
}

//===========================================
// 能力UIの情報の取得処理
//===========================================
CAbilityUI* CPlayer::GetAbilityUI(void) const
{
	// 能力UIの情報を返す
	return m_pAbilityUI;
}

//===========================================
// 取得処理
//===========================================
CPlayer* CPlayer::Get(void)
{
	if (m_pPlayer != nullptr)
	{ // プレイヤーの情報がある場合

		// プレイヤーのポインタを返す
		return m_pPlayer;
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// プレイヤーのポインタを返す
		return m_pPlayer;
	}
}

//===========================================
// 生成処理
//===========================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos)
{
	if (m_pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		m_pPlayer = new CPlayer;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return m_pPlayer;
	}

	if (m_pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(m_pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "プレイヤーの初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		m_pPlayer->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return m_pPlayer;
}

//=======================================
// ヒット処理
//=======================================
void CPlayer::Hit(void)
{
	// 爆発パーティクルを生成
	CParticle::Create(GetPos(), CParticle::TYPE_FIRE);
}

//=======================================
// 踏みつけ時の処理
//=======================================
void CPlayer::StepHit(void)
{
	// 移動量を上げる
	m_move.y = STEPHIT_JUMP;
}

//=======================================
// 情報の設定処理
//=======================================
void CPlayer::SetData(const D3DXVECTOR3& pos)
{
	// 全ての値を初期化する
	SetPos(pos);			// 位置
	SetPosOld(pos);			// 前回の位置
	SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));			// 向き
	SetScale(NONE_SCALE);	// 拡大率

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_PLAYER + nCntData));	// データの設定処理
	}

	// ローカル変数宣言
	CShadowCircle* pShadow = nullptr;		// 影へのポインタ

	// 影の設定処理
	pShadow = CShadowCircle::Create(pos, GetRot(), 40.0f);

	if (pShadow != nullptr)
	{ // 影のポインタが NULL以外の場合

		// 影のインデックス設定
		m_nShadowIdx = pShadow->GetNumID();
	}
}

//=======================================
// 移動量の設定処理
//=======================================
void CPlayer::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 目標の向きの設定処理
//=======================================
void CPlayer::SetRotDest(const D3DXVECTOR3& rot)
{
	// 目標の向きを設定する
	m_rotDest = rot;
}

//=======================================
// 目標の向きの取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetRotDest(void) const
{
	// 目標の向きを返す
	return m_rotDest;
}

//=======================================
// 種類の設定処理
//=======================================
void CPlayer::SetMode(const MODE type)
{
	// モードを設定する
	m_mode = type;
}

//=======================================
// 種類の取得処理
//=======================================
CPlayer::MODE CPlayer::GetMode(void) const
{
	// モードを返す
	return m_mode;
}

//=======================================
// 速度の設定処理
//=======================================
void CPlayer::SetSpeed(float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CPlayer::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
}

//=======================================
// 移動状況の設定処理
//=======================================
void CPlayer::SetEnableMove(bool bMove)
{
	// 移動状況を設定する
	m_bMove = bMove;
}

//=======================================
// 移動状況の取得処理
//=======================================
bool CPlayer::IsMove(void) const
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// 右向き状況の設定処理
//=======================================
void CPlayer::SetEnableRight(bool bRight)
{
	// 右向き状況を設定する
	m_bRight = bRight;
}

//=======================================
// 右向き状況の取得処理
//=======================================
bool CPlayer::IsRight(void) const
{
	// 右向き状況を取得する
	return m_bRight;
}

//=======================================
// ジャンプ状況の設定処理
//=======================================
void CPlayer::SetEnableJump(bool bJump)
{
	// ジャンプ状況を設定する
	m_bJump = bJump;
}

//=======================================
// ジャンプ状況の取得処理
//=======================================
bool CPlayer::IsJump(void) const
{
	// ジャンプ状況を返す
	return m_bJump;
}

//=======================================
// 起伏地面の当たり判定処理
//=======================================
void CPlayer::ElevationCollision(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);
		
		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			// 重力を設定する
			m_move.y = 0.0f;

			// ジャンプ状況を false にする
			m_bJump = false;

			if (m_pAction->GetAct() == CPlayerAct::ACT_CANNON ||
				m_pAction->GetAct() == CPlayerAct::ACT_FLY)
			{ // 通常状態以外の場合

				// 通常状態の設定処理
				SetNone();

				if (m_pAction->GetFront() == true)
				{ // 前後状況を設定する

					// 後ろにする
					pos.z = 1000.0f;

					// 前後状況を設定する
					m_pAction->SetFront(false);
				}
				else
				{ // 上記以外

					// 後ろにする
					pos.z = 0.0f;

					// 前後状況を設定する
					m_pAction->SetFront(true);
				}
			}
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}

//=======================================
// 着地時の通常状態の設定処理
//=======================================
void CPlayer::SetNone(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();		// 向きを取得する

	// 通常状態にする
	m_pAction->SetAct(CPlayerAct::ACT_NONE);

	// 移動量を設定する
	m_move.z = 0.0f;

	// 向きを設定する
	rot.x = 0.0f;
	rot.z = 0.0f;

	if (m_bRight == true)
	{ // 右向き状況が true の場合

		// 右を向かせる
		rot.y = D3DX_PI * 0.5f;
	}
	else
	{ // 上記以外

		// 左を向かせる
		rot.y = -D3DX_PI * 0.5f;
	}

	// 情報の設定処理
	SetRot(rot);			// 向きを設定する
}

//=======================================
// 移動制限判定
//=======================================
void CPlayer::CollisionMagicWall(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	if (pos.z >= 1000.0f)
	{ // 位置が一定以上になった場合

		// 位置を補正する
		pos.z = 1000.0f;
	}

	if (pos.z <= 0.0f)
	{ // 位置を一定以下になった場合

		// 位置を補正する
		pos.z = 0.0f;
	}

	// 位置を適用する
	SetPos(pos);
}