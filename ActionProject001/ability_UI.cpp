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
#define SHIFT				(40.0f)									// ずらす幅
#define GROUND_COL			(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		// 下地のサイズ

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CAbilityUI::m_acTextureFileName[CAbility::TYPE_MAX] = 			// テクスチャの名前
{
	"data\\TEXTURE\\HoverMark.png",			// ホバージェット
	"data\\TEXTURE\\SkyDashMark.png",		// ジェットダッシュ
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
		m_apAcrobat[nCntUI] = nullptr;			// アクロバットの情報
		m_apMassive[nCntUI] = nullptr;			// マッシブの情報
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

	// アクロバットの生成処理
	if (FAILED(AcrobatCreate()))
	{ // 生成に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// マッシブの生成処理
	if (FAILED(MassiveCreate()))
	{ // 生成に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
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
		if (m_apAcrobat[nCnt] != nullptr)
		{ // アクロバットのポインタが NULL じゃない場合

			// 終了処理
			m_apAcrobat[nCnt]->Uninit();
			m_apAcrobat[nCnt] = nullptr;
		}

		if (m_apMassive[nCnt] != nullptr)
		{ // アクロバットのポインタが NULL じゃない場合

			// 終了処理
			m_apMassive[nCnt]->Uninit();
			m_apMassive[nCnt] = nullptr;
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
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		// 頂点座標の設定処理
		m_apAcrobat[nCnt]->SetVtxUnderHeightGage();
		m_apMassive[nCnt]->SetVtxUnderHeightGage();
	}
}

//========================
// 描画処理
//========================
void CAbilityUI::Draw(void)
{
	switch (CPlayer::Get()->GetMode())
	{
	case CPlayer::MODE_ACROBAT:		// アクロバットモード

		// マッシブの描画処理
		DrawMassive();

		// アクロバットの描画処理
		DrawAcrobat();

		break;

	case CPlayer::MODE_MASSIVE:		// マッシブモード

		// アクロバットの描画処理
		DrawAcrobat();

		// マッシブの描画処理
		DrawMassive();

		break;

	case CPlayer::MODE_REBOOT:		// リブートドライブモード

		break;
	}
}

//========================
// アクロバットの描画処理
//========================
void CAbilityUI::DrawAcrobat(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			// 描画処理
			m_apAcrobat[nCnt]->Draw();
		}
	}
}

//========================
// マッシブの描画処理
//========================
void CAbilityUI::DrawMassive(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			// 描画処理
			m_apMassive[nCnt]->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CAbilityUI::SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	// アクロバットの設定処理
	SetDataAcrobat(posBig, posSmall);

	// マッシブの設定処理
	SetDataMassive(posBig, posSmall);
}

//========================
// アクロバットの設定処理
//========================
void CAbilityUI::SetDataAcrobat(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // 大きいゲージの場合

				// 設定処理
				m_apAcrobat[nCnt]->SetPos(posBig);			// 位置設定
				m_apAcrobat[nCnt]->SetSize(BIGUI_SIZE);		// サイズ設定
			}
			else
			{ // 小さいゲージの場合

				// 設定処理
				m_apAcrobat[nCnt]->SetPos(posSmall);		// 位置設定
				m_apAcrobat[nCnt]->SetSize(SMALLUI_SIZE);	// サイズ設定
			}

			m_apAcrobat[nCnt]->SetRot(NONE_D3DXVECTOR3);	// 向き設定
			m_apAcrobat[nCnt]->SetLength();					// 長さ設定
			m_apAcrobat[nCnt]->SetAngle();					// 方向設定

			// 頂点情報の設定処理
			m_apAcrobat[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // 下地の場合

				// 頂点カラーの設定処理
				m_apAcrobat[nCnt]->SetVtxColor(GROUND_COL);
			}
		}
	}
}

//========================
// マッシブの設定処理
//========================
void CAbilityUI::SetDataMassive(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall)
{
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] != nullptr)
		{ // 番号のポインタが NULL じゃない場合

			if (nCnt <= GAGE::GAGE_BIG_METER)
			{ // 大きいゲージの場合

				// 設定処理
				m_apMassive[nCnt]->SetPos(D3DXVECTOR3(posBig.x + SHIFT, posBig.y, 0.0f));			// 位置設定
				m_apMassive[nCnt]->SetSize(BIGUI_SIZE);		// サイズ設定
			}
			else
			{ // 小さいゲージの場合

				// 設定処理
				m_apMassive[nCnt]->SetPos(D3DXVECTOR3(posSmall.x + SHIFT, posSmall.y, 0.0f));		// 位置設定
				m_apMassive[nCnt]->SetSize(SMALLUI_SIZE);	// サイズ設定
			}

			m_apMassive[nCnt]->SetRot(NONE_D3DXVECTOR3);	// 向き設定
			m_apMassive[nCnt]->SetLength();					// 長さ設定
			m_apMassive[nCnt]->SetAngle();					// 方向設定

			// 頂点情報の設定処理
			m_apMassive[nCnt]->SetVtxUnderHeightGage();

			if (nCnt % 2 == 0)
			{ // 下地の場合

				// 頂点カラーの設定処理
				m_apMassive[nCnt]->SetVtxColor(GROUND_COL);
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
		pAblt->SetData(posBig, posSmall);
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
// アクロバットの生成処理
//========================
HRESULT CAbilityUI::AcrobatCreate(void)
{
	// メモリを確保する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apAcrobat[nCnt] == nullptr)
		{ // ポインタが NULL の場合

			// メモリを確保する
			m_apAcrobat[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ポインタが NULL じゃない場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}

		if (m_apAcrobat[nCnt] != nullptr)
		{ // ポインタが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_apAcrobat[nCnt]->Init()))
			{ // 初期化処理に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // 大技の場合

				// テクスチャの割り当て処理
				m_apAcrobat[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_HOVER].m_nTexIdx);
			}
			else
			{ // 小技の場合

				// テクスチャの割り当て処理
				m_apAcrobat[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_JETDASH].m_nTexIdx);
			}
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
// マッシブの生成処理
//========================
HRESULT CAbilityUI::MassiveCreate(void)
{
	// メモリを確保する
	for (int nCnt = 0; nCnt < GAGE_MAX; nCnt++)
	{
		if (m_apMassive[nCnt] == nullptr)
		{ // ポインタが NULL の場合

			// メモリを確保する
			m_apMassive[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ポインタが NULL じゃない場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}

		if (m_apMassive[nCnt] != nullptr)
		{ // ポインタが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_apMassive[nCnt]->Init()))
			{ // 初期化処理に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}

			if (nCnt <= GAGE_BIG_METER)
			{ // 大技の場合

				// テクスチャの割り当て処理
				m_apMassive[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_GROUNDQUAKE].m_nTexIdx);
			}
			else
			{ // 小技の場合

				// テクスチャの割り当て処理
				m_apMassive[nCnt]->BindTexture(m_aTexInfo[CAbility::TYPE_STARDROP].m_nTexIdx);
			}
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