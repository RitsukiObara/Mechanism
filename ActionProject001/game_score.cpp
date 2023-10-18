//============================================
//
// ゲームのスコア処理[game_score.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "game_score.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//========================
// コンストラクタ
//========================
CGameScore::CGameScore() : CScore(TYPE_GAMESCORE, PRIORITY_UI)
{

}

//========================
// デストラクタ
//========================
CGameScore::~CGameScore()
{

}

//========================
// 初期化処理
//========================
HRESULT CGameScore::Init(void)
{
	if (FAILED(CScore::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CGameScore::Uninit(void)
{
	// 終了処理
	CScore::Uninit();
}

//========================
// 更新処理
//========================
void CGameScore::Update(void)
{
	// 更新処理
	CScore::Update();
}

//========================
// 描画処理
//========================
void CGameScore::Draw(void)
{
	// 描画処理
	CScore::Draw();
}

//========================
// 情報の設定処理
//========================
void CGameScore::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size)
{
	// 情報を設定処理
	CScore::SetData(pos, rot, size);
}