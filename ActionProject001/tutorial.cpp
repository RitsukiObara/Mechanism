//============================================
//
// チュートリアル画面のメイン処理[tutorial.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "tutorial.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "fade.h"
#include "Objectmesh.h"
#include "sound.h"

//=========================================
// コンストラクタ
//=========================================
CTutorial::CTutorial() : CScene(TYPE_NONE, PRIORITY_BG)
{

}

//=========================================
// デストラクタ
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CTutorial::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CMesh::TxtSet();

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CTutorial::Uninit(void)
{
	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CTutorial::Update(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTERキーを押した場合

		if (CManager::Get()->GetSound() != nullptr)
		{ // サウンドが NULL じゃない場合

			// スキップ円の出現音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SKIPCIRCLE);
		}
	}

	// ゲームモードにする
	CManager::Get()->GetFade()->SetFade(MODE_GAME);
}

//======================================
//描画処理
//======================================
void CTutorial::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CTutorial::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);
}