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

#include "pause.h"
#include "edit.h"
#include "debugproc.h"
#include "sound.h"

#include "airplane.h"
#include "objectElevation.h"
#include "player.h"
#include "screw.h"
#include "enemy.h"
#include "table.h"
#include "macchina.h"
#include "game_score.h"
#include "goal.h"
#include "skybox.h"

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント

// デバッグ版
#ifdef _DEBUG

CEdit* CGame::m_pEdit = nullptr;			// エディットの情報
bool CGame::m_bEdit = false;				// エディット状態かどうか

#endif

//=========================================
// コンストラクタ
//=========================================
CGame::CGame() : CScene(TYPE_NONE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pPause = nullptr;			// ポーズ
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_START;	// 状態

// デバッグ版
#ifdef _DEBUG

	m_pEdit = nullptr;			// エディット
	m_bEdit = false;			// エディット状況
#endif

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

	// スカイボックスの生成処理
	CSkyBox::Create();

	// シーンの初期化
	CScene::Init();

	// プレイヤーを生成する
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 飛行機の生成
	CAirplane::Create(D3DXVECTOR3(2000.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

	// ネジの生成処理
	CScrew::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(1100.0f, 300.0f, 0.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 200.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 300.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 400.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 650.0f, 500.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 600.0f, 600.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 500.0f, 700.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 400.0f, 800.0f), NONE_D3DXVECTOR3, false);
	CScrew::Create(D3DXVECTOR3(2000.0f, 300.0f, 900.0f), NONE_D3DXVECTOR3, false);

	// 敵の生成処理
	CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 0.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_ITOCAN);
	CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(-1500.0f, 0.0f, 0.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(-2000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);
	CEnemy::Create(D3DXVECTOR3(3000.0f, 0.0f, 1000.0f), CEnemy::TYPE_MACHIDORI);

	CTable::Create(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
	CTable::Create(D3DXVECTOR3(1500.0f, 200.0f, 0.0f));
	CTable::Create(D3DXVECTOR3(-1000.0f, 300.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(-1200.0f, 350.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(2000.0f, 300.0f, 1000.0f));
	CTable::Create(D3DXVECTOR3(2200.0f, 350.0f, 1000.0f));

	// スコアを生成する
	CGameScore::Create(D3DXVECTOR3(70.0f,500.0f,0.0f),NONE_D3DXVECTOR3,D3DXVECTOR3(25.0f,35.0f,0.0f));

	// マキナ草の生成
	CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(3000.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(3200.0f, 0.0f, 100.0f));
	CMacchina::Create(D3DXVECTOR3(2000.0f, 0.0f, 1100.0f));
	CMacchina::Create(D3DXVECTOR3(-3000.0f, 0.0f, 1100.0f));

	// ゴールの生成
	CGoal::Create(D3DXVECTOR3(4000.0f, 300.0f, 1000.0f));

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態

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

// デバッグ版
#ifdef _DEBUG

	m_pEdit = nullptr;			// エディット

#endif

	// 情報を初期化する
	m_GameState = STATE_START;	// ゲームの進行状態

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

// デバッグ版
#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7キーを押した場合

		// エディット状況を入れ替える
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // エディット状況が true の場合

			if (m_pEdit == nullptr)
			{ // エディットが NULL じゃない場合

				// エディットを生成する
				m_pEdit = CEdit::Create(NONE_D3DXVECTOR3);
			}
			else
			{ // 上記以外

				// 停止
				assert(false);
			}
		}
		else
		{ // 上記以外

			if (m_pEdit != nullptr)
			{ // エディット状況が NULL じゃない場合

				// 終了処理
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // 上記以外

				// 停止
				assert(false);
			}
		}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_PLAY:

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_GOAL:



		break;

	case CGame::STATE_LEAVE:

		break;

	case CGame::STATE_FINISH:

		// 遷移処理
		Transition();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // エディット状況が true の場合

		if (m_pEdit != nullptr)
		{ // エディットが NULL じゃない場合

			// エディットの更新処理
			m_pEdit->Update();
		}
	}
	else
	{ // 上記以外

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// レンダラーの更新
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// レンダラーの更新
		CManager::Get()->GetRenderer()->Update();
	}

#endif

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
	m_GameState = STATE_PLAY;

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
	// 終了カウントを加算する
	m_nFinishCount++;

	if (m_nFinishCount % 80 == 0)
	{ // 終了カウントが一定数を超えた場合

		// リザルトに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
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

// デバッグ版
#ifdef _DEBUG
//======================================
// エディットの取得処理
//======================================
CEdit* CGame::GetEdit(void)
{
	// エディットの情報を返す
	return m_pEdit;
}

//======================================
// エディット状況の取得処理
//======================================
bool CGame::IsEdit(void)
{
	// エディット状況を返す
	return m_bEdit;
}

#endif