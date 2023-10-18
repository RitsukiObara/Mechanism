//============================================
//
// コンボ処理[combo.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "number.h"
#include "combo.h"
#include "combo_circle.h"
#include "texture.h"
#include "useful.h"

// マクロ定義
#define SCORE_TEXTURE		"data\\TEXTURE\\Number.png"					// 数値のテクスチャ
#define LIMIT_POS			(D3DXVECTOR3(1080.0f, 70.0f, 0.0f))			// コンボ制限の位置
#define LIMIT_SIZE			(40.0f)										// コンボ制限のサイズ
#define LIMIT_DISTANCE		(25.0f)										// コンボ制限の距離
#define LIMIT_DIVI			(96)										// コンボ制限の分割数
#define COMBO_POS			(D3DXVECTOR3(900.0f, 70.0f, 0.0f))			// コンボの数値の位置
#define COMBO_SIZE			(D3DXVECTOR3(20.0f, 30.0f, 0.0f))			// コンボの数値のサイズ
#define COMBO_SHIFT			(40.0f)										// コンボの数値のずらす幅

//========================
// コンストラクタ
//========================
CCombo::CCombo() : CObject(TYPE_COMBO, PRIORITY_UI)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// 数字の情報
		m_apNumber[nCnt] = nullptr;
	}
	m_pTimeLimit = nullptr;		// コンボの制限
	m_nCombo = 0;				// コンボ数
}

//========================
// デストラクタ
//========================
CCombo::~CCombo()
{

}

//========================
// 初期化処理
//========================
HRESULT CCombo::Init(void)
{
	// 全ての値を初期化する
	m_nCombo = 0;		// コンボ数
 
	// コンボの生成処理
	if (FAILED(CreateCombo()))
	{ // 失敗した場合
		
		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// コンボ制限の生成処理
	if (FAILED(CreateLimit()))
	{ // 失敗した場合

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
void CCombo::Uninit(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// 数字の終了処理
		m_apNumber[nCnt]->Uninit();
	}

	// コンボ制限の終了処理
	m_pTimeLimit->Uninit();

	// 数字の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CCombo::Update(void)
{
	// 計算処理
	Calculate();

	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// テクスチャ座標の設定処理
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_apNumber[nCnt]->GetNumber());
	}

	// コンボの制限円の更新処理
	m_pTimeLimit->Update();
}

//========================
// 描画処理
//========================
void CCombo::Draw(void)
{
	if (m_pTimeLimit != nullptr)
	{ // コンボ制限が NULL じゃない場合

		// 描画処理
		m_pTimeLimit->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // 数字が NULL じゃない場合

			// 描画処理
			m_apNumber[nCnt]->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CCombo::SetData(void)
{
	// コンボの情報の設定処理
	SetDataCombo();
}

//========================
// コンボの情報の設定処理
//========================
void CCombo::SetDataCombo(void)
{
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		// 設定処理
		m_apNumber[nCnt]->SetPos(D3DXVECTOR3(COMBO_POS.x + (nCnt * COMBO_SHIFT), COMBO_POS.y, 0.0f));				// 位置設定
		m_apNumber[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き設定
		m_apNumber[nCnt]->SetSize(COMBO_SIZE);			// サイズ設定
		m_apNumber[nCnt]->SetLength();					// 長さ設定
		m_apNumber[nCnt]->SetAngle();					// 方向設定

		m_apNumber[nCnt]->SetType(CNumber::TYPE_DECIMAL);	// 番号の種類
		m_apNumber[nCnt]->SetNumber(0);					// 番号を設定する

		// 頂点情報の設定処理
		m_apNumber[nCnt]->SetVertex();

		// テクスチャの設定処理(アニメーションバージョン)
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, 0);
	}
}

//========================
// コンボの生成処理
//========================
HRESULT CCombo::CreateCombo(void)
{
	// メモリを確保する
	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{ // ポインタが NULL の場合

			// メモリを確保する
			m_apNumber[nCnt] = new CNumber(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ポインタが NULL じゃない場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}

		if (m_apNumber[nCnt] != nullptr)
		{ // ポインタが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_apNumber[nCnt]->Init()))
			{ // 初期化処理に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}

			// テクスチャの割り当て処理
			m_apNumber[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(SCORE_TEXTURE));
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
// コンボ制限の生成処理
//========================
HRESULT CCombo::CreateLimit(void)
{
	if (m_pTimeLimit == nullptr)
	{ // ポインタが NULL の場合

		// メモリを確保する
		m_pTimeLimit = CComboCircle::Create(LIMIT_POS, LIMIT_SIZE, LIMIT_DISTANCE, LIMIT_DIVI);
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	if (m_pTimeLimit != nullptr)
	{ // ポインタが NULL じゃない場合

		// テクスチャの割り当て処理
		m_pTimeLimit->BindTexture(CManager::Get()->GetTexture()->Regist(nullptr));
	}
	else
	{ // ポインタが　NULL の場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//========================
// 計算処理
//========================
void CCombo::Calculate(void)
{
	// ローカル変数宣言
	int aNum[MAX_COMBO_DIGIT];		// 数値

	// 10進数への計算処理
	useful::DecimalCalculation(MAX_COMBO_DIGIT, m_nCombo, &aNum[0]);

	for (int nCnt = 0; nCnt < MAX_COMBO_DIGIT; nCnt++)
	{
		//値の計算
		m_apNumber[nCnt]->SetNumber(aNum[nCnt]);
	}
}

//========================
// コンボの設定処理
//========================
void CCombo::SetCombo(const int nCombo)
{
	// コンボ数を設定する
	m_nCombo = nCombo;
}

//========================
// コンボの取得処理
//========================
int CCombo::GetCombo(void) const
{
	// コンボを返す
	return m_nCombo;
}

//========================
// コンボの加算処理
//========================
void CCombo::AddCombo(void)
{
	// コンボを設定する
	m_nCombo++;

	// 頂点のリセット処理
	m_pTimeLimit->ResetNumVtx();
}

//========================
// 生成処理
//========================
CCombo* CCombo::Create(void)
{
	// ローカルオブジェクトを生成
	CCombo* pScrew = nullptr;	// プレイヤーのインスタンスを生成

	if (pScrew == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pScrew = new CCombo;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pScrew->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pScrew->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ネジUIのポインタを返す
	return pScrew;
}