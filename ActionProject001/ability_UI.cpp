//============================================
//
// 時間処理[time.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "player.h"
#include "player_ability.h"
#include "player_act.h"
#include "ability_UI.h"
#include "object2D.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define BIGUI_SIZE			(D3DXVECTOR3(60.0f, 120.0f, 0.0f))		// 大きいUIのサイズ
#define SMALLUI_SIZE		(D3DXVECTOR3(40.0f, 80.0f, 0.0f))		// 小さいUIのサイズ
#define GROUND_COL			(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		// 下地のサイズ

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// テクスチャの名前
{
	"data\\TEXTURE\\HoverMark.png",			// ホバージェット
	"data\\TEXTURE\\SkyDashMark.png",		// 空中ダッシュ
	"data\\TEXTURE\\",						// グラウンドクエイク
	"data\\TEXTURE\\",						// スタードロップ
};

//========================
// コンストラクタ
//========================
CAbilityUI::CAbilityUI() : CObject(CObject::TYPE_ABILITYUI, CObject::PRIORITY_UI)
{
	for (int nCntUI = 0; nCntUI < GAGE_MAX; nCntUI++)
	{
		m_apObjectUI[nCntUI] = nullptr;		// ポリゴンの情報
	}

	for (int nCntTex = 0; nCntTex < CAbility::TYPE_MAX; nCntTex++)
	{
		m_aTexInfo[nCntTex].m_nTexIdx = NONE_TEXIDX;	// テクスチャの番号
		m_aTexInfo[nCntTex].m_fTexSizeY = 1.0f;			// テクスチャの縦サイズ
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
	for (int nCntTex = 0; nCntTex < CAbility::TYPE_MAX; nCntTex++)
	{
		m_aTexInfo[nCntTex].m_nTexIdx = CManager::Get()->GetTexture()->Regist(m_acTextureFileName[nCntTex]);		// テクスチャの登録処理
		m_aTexInfo[nCntTex].m_fTexSizeY = 1.0f;						// テクスチャの縦サイズ
	}

	// メモリを確保する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] == nullptr)
		{ // ポインタが NULL の場合

			// メモリを確保する
			m_apObjectUI[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ポインタが NULL じゃない場合

			// 警告文
			MessageBox(NULL, "能力UIのメモリが既に使われている！", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return E_FAIL;
		}

		if (m_apObjectUI[nCnt] != nullptr)
		{ // ポインタが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_apObjectUI[nCnt]->Init()))
			{ // 初期化処理に失敗した場合

				// 警告文
				MessageBox(NULL, "能力UIの初期化に失敗！", "警告！", MB_ICONWARNING);

				// 失敗を返す
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // 大技の場合

				// テクスチャの割り当て処理
				m_apObjectUI[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_HOVER].m_nTexIdx);
			}
			else
			{ // 小技の場合

				// テクスチャの割り当て処理
				m_apObjectUI[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_SKYDASH].m_nTexIdx);
			}
		}
		else
		{ // ポインタが　NULL の場合

			// 警告文
			MessageBox(NULL, "能力UIのメモリの確保に失敗！", "警告！", MB_ICONWARNING);

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
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // 時間のポインタが NULL じゃない場合

			// 終了処理
			m_apObjectUI[nCnt]->Uninit();
			m_apObjectUI[nCnt] = nullptr;
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
	// ローカル変数宣言
	CPlayer* player = CPlayer::Get();		// プレイヤーの情報を取得する

	switch (player->GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// アクロバットモード

		// サイズ変更処理
		Size(CAbility::TYPE_HOVER, CAbilityUI::GAGE_BIG_METER, HOVER_INTERVAL, (BIGUI_SIZE.y / HOVER_INTERVAL));			// ホバージェット
		Size(CAbility::TYPE_SKYDASH, CAbilityUI::GAGE_SMALL_METER, SKYDASH_INTERVAL, (SMALLUI_SIZE.y / SKYDASH_INTERVAL));	// 空中ダッシュ

		break;

	case CPlayer::MODE_MASSIVE:		// マッシブモード

		break;

	case CPlayer::MODE_REBOOT:		// リブートドライブモード

		break;
	}

	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		// 頂点座標の設定処理
		m_apObjectUI[nCnt]->SetVtxUnderHeightGage();
	}
}

//========================
// 描画処理
//========================
void CAbilityUI::Draw(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			// 描画処理
			m_apObjectUI[nCnt]->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CAbilityUI::SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apObjectUI[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // 大きいゲージの場合

				// 設定処理
				m_apObjectUI[nCnt]->SetPos(posBig);				// 位置設定
				m_apObjectUI[nCnt]->SetRot(NONE_D3DXVECTOR3);	// 向き設定
				m_apObjectUI[nCnt]->SetSize(BIGUI_SIZE);		// サイズ設定
			}
			else
			{ // 小さいゲージの場合

				// 設定処理
				m_apObjectUI[nCnt]->SetPos(posSmall);			// 位置設定
				m_apObjectUI[nCnt]->SetRot(NONE_D3DXVECTOR3);	// 向き設定
				m_apObjectUI[nCnt]->SetSize(SMALLUI_SIZE);		// サイズ設定
			}
			m_apObjectUI[nCnt]->SetLength();			// 長さ設定
			m_apObjectUI[nCnt]->SetAngle();				// 方向設定

			// 頂点情報の設定処理
			m_apObjectUI[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // 下地の場合

				// 頂点カラーの設定処理
				m_apObjectUI[nCnt]->SetVtxColor(GROUND_COL);
			}
		}
	}
}

//========================
// 生成処理
//========================
CAbilityUI* CAbilityUI::Create(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	// ローカルオブジェクトを生成
	CAbilityUI* pTime = nullptr;	// プレイヤーのインスタンスを生成

	if (pTime == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTime = new CAbilityUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (pTime != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTime->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "能力UIの初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTime->SetData(posBig, posSmall);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// オブジェクト2Dのポインタを返す
	return pTime;
}

//========================
// サイズ設定処理
//========================
void CAbilityUI::Size(const CAbility::TYPE type, const CAbilityUI::GAGE gage, const int nInterval, float fSizeMove)
{
	// ローカル変数宣言
	D3DXVECTOR3 size = m_apObjectUI[gage]->GetSize();				// 大技のサイズ
	int nCount = CPlayer::Get()->GetAbility()->GetInterval(type);	// カウント

	// サイズを設定する
	size.y = ((nInterval - nCount) * fSizeMove);
	m_aTexInfo[type].m_fTexSizeY = (float)((1.0f / nInterval) * nCount);

	// サイズを適用する
	m_apObjectUI[gage]->SetSize(size);
	
	// 下中心の縦のテクスチャ座標の設定処理
	m_apObjectUI[gage]->SetVtxTextureUnderHeight(m_aTexInfo[type].m_fTexSizeY);
}