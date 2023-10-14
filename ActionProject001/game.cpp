//============================================
//
// ゲームのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"

#include "score.h"
#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "airplane.h"
#include "objectElevation.h"
#include "player.h"
#include "screw.h"
#include "enemy.h"

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CGame::STATE CGame::m_GameState = CGame::STATE_FINISH;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント

//=========================================
// コンストラクタ
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_FINISH;	// 状態
}

//=========================================
// デストラクタ
//=========================================
CGame::~CGame()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CGame::Init(void)
{
	// テキスト読み込み処理
	CElevation::TxtSet();

	//if (m_pField == NULL)
	//{ // フィールドへのポインタが NULL の場合

	//	// フィールドの設定処理
	//	m_pField = CField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1000.0f, 0.0f, 1000.0f));
	//}

	// シーンの初期化
	CScene::Init();

	// プレイヤーを生成する
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 飛行機の生成
	CAirplane::Create(D3DXVECTOR3(2000.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	CAirplane::Create(D3DXVECTOR3(1800.0f, 100.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ネジの生成処理
	CScrew::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
	CScrew::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f));
	CScrew::Create(D3DXVECTOR3(1100.0f, 300.0f, 0.0f));

	// 敵の生成処理
	CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), CEnemy::TYPE_ITOCAN);

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CGame::Uninit(void)
{
	// ポインタを NULL にする
	m_pPause = nullptr;			// ポーズ

	// 情報を初期化する
	m_GameState = STATE_FINISH;	// ゲームの進行状態

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CGame::Update(void)
{
	// ポーズ処理
	Pause();

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// レンダラーの更新
		CManager::Get()->GetRenderer()->Update();
	}

	// 遷移処理
	//Transition();

	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CGame::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CGame::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // ポーズへのポインタが NULL の場合

		// ポーズの生成処理
		m_pPause = CPause::Create();
	}

	// スタート状態にする
	m_GameState = STATE_FINISH;

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
}

//======================================
// ポーズ処理
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true)
	{ // Pキーを押した場合

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // フェード無し状態かつ、終了以外の場合

			if (m_pPause->GetPause() == false)
			{ // ポーズが false だった場合

				// ポーズ状況を true にする
				m_pPause->SetPause(true);
			}
			else
			{ // ポーズが true だった場合

				// ポーズ状況を false にする
				m_pPause->SetPause(false);
			}

			// 決定音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// 遷移処理
//======================================
void CGame::Transition(void)
{
	if (m_GameState == STATE_FINISH)
	{ // ゲームが終了状態の場合

		// 終了カウントを加算する
		m_nFinishCount++;

		if (m_nFinishCount % 80 == 0)
		{ // 終了カウントが一定数を超えた場合

			// リザルトに遷移する
			CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
		}
	}
}

//======================================
// ポーズの取得処理
//======================================
CPause* CGame::GetPause(void)
{
	// ポーズの情報を返す
	return m_pPause;
}

//======================================
// ゲームの進行状態の設定処理
//======================================
void CGame::SetState(const STATE state)
{
	// ゲームの進行状態を設定する
	m_GameState = state;
}

//======================================
// ゲームの進行状態の取得処理
//======================================
CGame::STATE CGame::GetState(void)
{
	// ゲームの進行状態を返す
	return m_GameState;
}

//======================================
// ポーズのNULL化処理
//======================================
void CGame::DeletePause(void)
{
	// ポーズのポインタを NULL にする
	m_pPause = nullptr;
}