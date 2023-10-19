//============================================
//
// 能力UIの処理[ability_UI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "player.h"
#include "player_ability.h"
#include "ability_UI.h"
#include "objectbillboard.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define UI_SIZE				(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// 大きいUIのサイズ
#define SHIFT				(D3DXVECTOR3(65.0f, 130.0f, 0.0f))		// ずらす幅
#define GROUND_COL			(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f))		// 下地のサイズ

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// テクスチャの名前
{
	"data\\TEXTURE\\HoverMark.png",			// ホバージェット
	"data\\TEXTURE\\SkyDashMark.png",		// ジェットダッシュ
	"data\\TEXTURE\\",						// グラウンドクエイク
};

//========================
// コンストラクタ
//========================
CAbilityUI::CAbilityUI() : CObject(CObject::TYPE_ABILITYUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCntUI = 0; nCntUI < CAbility::TYPE_MAX; nCntUI++)
	{
		m_apAbilityUI[nCntUI] = nullptr;	// 能力UIの情報
	}
}

//========================
// デストラクタ
//========================
CAbilityUI::~CAbilityUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CAbilityUI::Init(void)
{
	// メモリを確保する
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] == nullptr)
		{ // ポインタが NULL の場合

			// メモリを確保する
			m_apAbilityUI[nCnt] = new CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ポインタが NULL じゃない場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}

		if (m_apAbilityUI[nCnt] != nullptr)
		{ // ポインタが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_apAbilityUI[nCnt]->Init()))
			{ // 初期化処理に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}

			// テクスチャの割り当て処理
			m_apAbilityUI[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(m_acTextureFileName[nCnt]));
		}
		else
		{ // ポインタが　NULL の場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CAbilityUI::Uninit(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // 能力UIが NULL じゃない場合

			// 終了処理
			m_apAbilityUI[nCnt]->Uninit();
			m_apAbilityUI[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CAbilityUI::Update(void)
{
	// 使用状況の設定処理
	PossibleColor();

	// 位置追尾処理
	PosChase();
}

//========================
// 描画処理
//========================
void CAbilityUI::Draw(void)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // 情報が NULL じゃない場合

			// 描画処理
			m_apAbilityUI[nCnt]->DrawLightOff();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CAbilityUI::SetData(const D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			// 情報を設定する
			m_apAbilityUI[nCnt]->SetPos(D3DXVECTOR3(pos.x - (SHIFT.x * (nCnt - 1)), pos.y + SHIFT.y, pos.z));		// 位置設定
			m_apAbilityUI[nCnt]->SetSize(UI_SIZE);		// サイズ設定

			// 頂点情報の設定処理
			m_apAbilityUI[nCnt]->SetVertex();
		}
	}
}

//========================
// 生成処理
//========================
CAbilityUI* CAbilityUI::Create(const D3DXVECTOR3 pos)
{
	// ローカルオブジェクトを生成
	CAbilityUI* pAblt = nullptr;	// プレイヤーのインスタンスを生成

	if (pAblt == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pAblt = new CAbilityUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pAblt != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAblt->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAblt->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 能力UIのポインタを返す
	return pAblt;
}

//========================
// 使用状況の設定処理
//========================
void CAbilityUI::PossibleColor(void)
{
	// ローカル変数宣言
	CAbility* pAblt = CPlayer::Get()->GetAbility();		// 能力の情報

	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (pAblt->GetPossible((CAbility::TYPE)(nCnt)) == true)
		{ // ホバージェットが使用できる場合

			// 色を設定する
			m_apAbilityUI[nCnt]->SetVtxColor(NONE_D3DXCOLOR);
		}
		else
		{ // 上記以外

			// 色を設定する
			m_apAbilityUI[nCnt]->SetVtxColor(GROUND_COL);
		}
	}
}

//========================
// 位置追尾処理
//========================
void CAbilityUI::PosChase(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = CPlayer::Get()->GetPos();

	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_apAbilityUI[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			// 情報を設定する
			m_apAbilityUI[nCnt]->SetPos(D3DXVECTOR3(pos.x + (SHIFT.x * (nCnt - 1)), pos.y + SHIFT.y, pos.z));		// 位置設定
		}
	}
}