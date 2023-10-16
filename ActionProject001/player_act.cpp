//============================================
//
// プレイヤーの行動状態のメイン処理[player_act.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "player.h"
#include "motion.h"
#include "player_act.h"
#include "player_ability.h"
#include "ability_UI.h"
#include "useful.h"
#include "manager.h"
#include "input.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define CANNON_COUNT			(60)				// 飛ぶまでのカウント
#define ROT_Y_MOVE				(D3DX_PI * 0.1f)	// 向きの移動量(Y軸)
#define JUMP_MOVE				(20.0f)				// ジャンプの移動量
#define CANNON_Y_MOVE			(30.0f)				// 大砲のY軸の移動量
#define CANNON_Z_MOVE			(15.0f)				// 大砲のZ軸の移動量
#define PLAYER_ACROBAT_SPEED	(7.0f)				// アクロバット状態のスピード

// 重力関係
#define ACROBAT_GRAVITY		(-0.9f)					// アクロバットモードの重力
#define HOVER_GRAVITY		(0.8f)					// ホバー状態の重力
#define MASSIVE_GRAVITY		(-1.2f)					// マッシブモードの重力
#define FLY_GRAVITY			(-0.9f)					// フライ状態の重力

//============================================
// コンストラクタ
//============================================
CPlayerAct::CPlayerAct()
{
	// 全ての値をクリアする
	m_act = ACT_NONE;			// 状態
	m_nStateCount = 0;			// 状態カウント
	m_bFront = true;			// 前後状況
}

//============================================
// デストラクタ
//============================================
CPlayerAct::~CPlayerAct()
{

}

//============================================
// 初期化処理
//============================================
HRESULT CPlayerAct::Init(void)
{
	// 全ての値を初期化する
	m_act = ACT_NONE;			// 状態
	m_nStateCount = 0;			// 状態カウント
	m_bFront = true;			// 前後状況

	// 成功を返す
	return S_OK;
}

//============================================
// 終了処理
//============================================
void CPlayerAct::Uninit(void)
{
	// 自分のメモリを解放する
	delete this;
}

//============================================
// 更新処理
//============================================
void CPlayerAct::Update(CPlayer& player)
{
	switch (m_act)
	{
	case ACT_NONE:		// 通常状態

		// 操作処理
		Control(player);

		// 重力処理
		Gravity(player);

		// 能力操作処理
		Ability(player);

		// 向きの移動処理
		RotMove(player);

		// 移動処理
		Move(player);

		// 能力の更新処理
		player.GetAbility()->Update(player);

		// 能力UIの更新処理
		player.GetAbilityUI()->Update();

		break;

	case ACT_CANNON:	// 大砲準備状態

		// 大砲で向きを変える処理
		CannonRot(player);

		// 重力のリセット処理
		GravityReset(player);

		// 状態カウントを加算する
		m_nStateCount++;

		if (m_nStateCount % CANNON_COUNT == 0)
		{ // 状態カウントが一定数の場合

			// 大砲で飛ぶ処理
			FlyMove(player);

			// 飛んでいる状態にする
			SetAct(ACT_FLY);
		}

		break;

	case ACT_FLY:		// 飛んでいる状態

		{
			// ローカル変数宣言
			D3DXVECTOR3 pos = player.GetPos();			// 位置を取得する
			D3DXVECTOR3 move = player.GetMove();		// 移動量を取得する

			// 重力を加算する
			move.y += FLY_GRAVITY;

			// 移動量を設定する
			pos += move;

			// 位置を設定する
			player.SetPos(pos);

			// 移動量を設定する
			player.SetMove(move);
		}

		break;
	}
}

//============================================
// 情報の設定処理
//============================================
void CPlayerAct::SetData(void)
{
	// 全ての値を初期化する
	m_act = ACT_NONE;		// 状態
	m_nStateCount = 0;		// 状態カウント
	m_bFront = true;		// 前後関係
}

//============================================
// 状態の設定処理
//============================================
void CPlayerAct::SetAct(const ACT act)
{
	// 行動状態を設定する
	m_act = act;

	// 状態カウントを初期化する
	m_nStateCount = 0;
}

//============================================
// 状態の取得処理
//============================================
CPlayerAct::ACT CPlayerAct::GetAct(void) const
{
	// 行動状態を返す
	return m_act;
}

//============================================
// 前後状況の設定処理
//============================================
void CPlayerAct::SetFront(bool bFront)
{
	// 前後状況を設定する
	m_bFront = bFront;
}

//============================================
// 前後状況の取得処理
//============================================
bool CPlayerAct::GetFront(void) const
{
	// 前後状況を返す
	return m_bFront;
}

//============================================
// 生成処理
//============================================
CPlayerAct* CPlayerAct::Create(void)
{
	// ローカル変数宣言
	CPlayerAct* pAct = nullptr;		// 行動状態

	if (pAct == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pAct = new CPlayerAct;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pAct;
	}

	if (pAct != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAct->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "プレイヤーの行動の初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAct->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pAct;
}

//=======================================
// 操作処理
//=======================================
void CPlayerAct::Control(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 move = player.GetMove();		// 移動量
	D3DXVECTOR3 rotDest = player.GetRotDest();	// 目標の向き

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押した場合

		// モードごとのスピード処理
		ModeSpeed(player);

		// 移動の基本処理
		MoveProcess(player);

		// 右向き状況を true にする
		player.SetEnableRight(true);

		// 目標の向きを設定する
		rotDest.y = D3DX_PI * 0.5f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押した場合

		// モードごとのスピード処理
		ModeSpeed(player);

		// 移動の基本処理
		MoveProcess(player);

		// 右向き状況を false にする
		player.SetEnableRight(false);

		// 目標の向きを設定する
		rotDest.y = -D3DX_PI * 0.5f;
	}
	else
	{ // 上記以外

		// 速度を設定する
		player.SetSpeed(0.0f);

		// 移動状況を false にする
		player.SetEnableMove(false);

		if (player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_NEUTRAL)
		{ // 待機モーションじゃない場合

			// 待機モーションを設定する
			player.GetMotion()->Set(CPlayer::MOTIONTYPE_NEUTRAL);
		}
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true &&
		player.IsJump() == false)
	{ // SPACEキーを押した場合

		// ジャンプの移動量を設定する
		move.y = JUMP_MOVE;

		// ジャンプ状況を true にする
		player.SetEnableJump(true);
	}

	// 目標の向きを適用する
	player.SetRotDest(rotDest);

	// 移動量を適用する
	player.SetMove(move);
}

//=======================================
// 移動の基本処理
//=======================================
void CPlayerAct::MoveProcess(CPlayer& player)
{
	// 移動状況を true にする
	player.SetEnableMove(true);

	if (player.GetMotion()->GetType() != CPlayer::MOTIONTYPE_MOVE)
	{ // 移動モーションじゃない場合

		// 移動モーションを設定する
		player.GetMotion()->Set(CPlayer::MOTIONTYPE_MOVE);
	}
}

//=======================================
// モードごとのスピード処理
//=======================================
void CPlayerAct::ModeSpeed(CPlayer& player)
{
	switch (player.GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// アクロバットモード

		switch (player.GetAbility()->GetAbility())
		{
		case CAbility::ABILITY_JETDASH:		// ジェットダッシュ

			// 速度を設定する
			player.SetSpeed(0.0f);

			break;

		default:

			// 速度を設定する
			player.SetSpeed(PLAYER_ACROBAT_SPEED);

			break;
		}

		break;

	case CPlayer::MODE_MASSIVE:		// マッシブモード

		break;

	case CPlayer::MODE_REBOOT:		// リブートドライブモード

		break;
	}
}

//=======================================
// 能力操作処理
//=======================================
void CPlayerAct::Ability(CPlayer& player)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true)
	{ // Uキーを押した場合

		switch (player.GetMode())
		{
		case CPlayer::MODE_ACROBAT:		// アクロバットモード

			if (player.GetAbility()->GetPossible(CAbility::TYPE_HOVER) == true &&
				player.IsJump() == true)
			{ // ジャンプ状況が true の場合

				// ホバージェット状態にする
				player.GetAbility()->SetAbility(CAbility::ABILITY_HOVER);

				// 使用可能状況を false にする
				player.GetAbility()->SetPossible(CAbility::TYPE_HOVER, false);

				// 間隔カウントを設定する
				player.GetAbility()->SetInterval(CAbility::TYPE_HOVER, HOVER_INTERVAL);
			}

			break;

		case CPlayer::MODE_MASSIVE:		// マッシブモード

			break;

		case CPlayer::MODE_REBOOT:		// リブートドライブ

			break;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_I) == true)
	{ // Iキーを押した場合

		switch (player.GetMode())
		{
		case CPlayer::MODE_ACROBAT:		// アクロバットモード

			if (player.GetAbility()->GetPossible(CAbility::TYPE_JETDASH) == true)
			{ // ジャンプ状況が true の場合

				// ジェットダッシュ状態にする
				player.GetAbility()->SetAbility(CAbility::ABILITY_JETDASH);

				// 使用可能状況を false にする
				player.GetAbility()->SetPossible(CAbility::TYPE_JETDASH, false);

				// 間隔カウントを設定する
				player.GetAbility()->SetInterval(CAbility::TYPE_JETDASH, JETDASH_INTERVAL);
			}

			break;

		case CPlayer::MODE_MASSIVE:		// マッシブモード

			break;

		case CPlayer::MODE_REBOOT:		// リブートドライブ

			break;
		}
	}
}

//=======================================
// 移動処理
//=======================================
void CPlayerAct::Move(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = player.GetPos();		// 位置を取得する
	D3DXVECTOR3 rot = player.GetRot();		// 向きを取得する
	D3DXVECTOR3 move = player.GetMove();	// 移動量を取得する
	
	// 移動量を設定する
	move.x = sinf(rot.y) * player.GetSpeed();

	// 位置を設定する
	pos += move;

	// 位置を更新する
	player.SetPos(pos);
	player.SetMove(move);
}

//=======================================
// 重力処理
//=======================================
void CPlayerAct::Gravity(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 move = player.GetMove();		// 移動量を取得する

	switch (player.GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// アクロバットモード

		switch (player.GetAbility()->GetAbility())
		{
		case CAbility::ABILITY_NONE:

			// 重力を加算する
			move.y += ACROBAT_GRAVITY;

			break;

		case CAbility::ABILITY_HOVER:

			// 重力を加算する
			move.y = HOVER_GRAVITY;

			break;

		case CAbility::ABILITY_JETDASH:

			// 重力を加算する
			move.y = 0.0f;

			break;
		}

		break;

	case CPlayer::MODE_MASSIVE:		// マッシブモード

		// 重力を加算する
		move.y += MASSIVE_GRAVITY;

		break;

	case CPlayer::MODE_REBOOT:		// リブートドライブモード

		break;
	}

	// 移動量を適用する
	player.SetMove(move);
}

//=======================================
// 向きの移動処理
//=======================================
void CPlayerAct::RotMove(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = player.GetRot();				// 向きを取得する
	D3DXVECTOR3 rotDest = player.GetRotDest();		// 目的の向きを取得する

	if (rot.y > rotDest.y - ROT_Y_MOVE &&
		rot.y < rotDest.y + ROT_Y_MOVE)
	{ // 向きが一定数の範囲に入った場合

		// 向きを補正する
		rot.y = rotDest.y;
	}
	else
	{ // 上記以外

		if (player.IsRight() == true)
		{ // 右向き状況の場合

			// 向きを減算する
			rot.y -= ROT_Y_MOVE;
		}
		else
		{ // 上記以外

			// 向きを加算する
			rot.y += ROT_Y_MOVE;
		}

		// 向きを正規化する
		useful::RotNormalize(&rot.y);
	}

	// 向きを更新する
	player.SetRot(rot);
}

//============================================
// 大砲で向きを変える処理
//============================================
void CPlayerAct::CannonRot(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = player.GetRot();		// 向きを取得する

	// 向きを設定する
	rot.x = -D3DX_PI * 0.5f;

	if (m_bFront == true)
	{ // 手前にいる場合

		// 向きを設定する
		rot.y = 0.0f;
	}
	else
	{ // 奥にいる場合

		// 向きを設定する
		rot.y = D3DX_PI;
	}

	// 向きを更新する
	player.SetRot(rot);
}

//============================================
// 重力のリセット処理
//============================================
void CPlayerAct::GravityReset(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 move = player.GetMove();		// 移動量を取得する

	// 縦の移動量を設定する
	move.y = 0.0f;

	// 移動量を適用する
	player.SetMove(move);
}

//============================================
// 大砲で飛ぶ処理
//============================================
void CPlayerAct::FlyMove(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = player.GetRot();
	D3DXVECTOR3 move = player.GetMove();		// 移動量を取得する

	// 移動量を初期化する
	move.x = 0.0f;
	move.y = CANNON_Y_MOVE;
	move.z = cosf(rot.y) * CANNON_Z_MOVE;

	// 移動量を適用する
	player.SetMove(move);
}