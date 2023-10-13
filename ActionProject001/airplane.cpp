//===========================================
//
// 飛行機のメイン処理[airplane.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CAirplane::CAirplane() : CModel(CObject::TYPE_AIRPLANE, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pPrev = nullptr;		// 前のアウトボールへのポインタ
	m_pNext = nullptr;		// 次のアウトボールへのポインタ

	if (CAirplaneManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CAirplaneManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CAirplane::~CAirplane()
{

}

//============================
// 前のポインタの設定処理
//============================
void CAirplane::SetPrev(CAirplane* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CAirplane::SetNext(CAirplane* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CAirplane* CAirplane::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CAirplane* CAirplane::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CAirplane::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CAirplane::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CAirplaneManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CAirplaneManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CAirplane::Update(void)
{

}

//=====================================
//ブロックの描画処理
//=====================================
void CAirplane::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CAirplane::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(rot);								// 向き
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// 拡大率
	SetFileData(CXFile::TYPE_AIRPLANE);			// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CAirplane* CAirplane::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CAirplane* pAirplane = nullptr;	// インスタンスを生成

	if (pAirplane == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pAirplane = new CAirplane;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (pAirplane != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAirplane->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "飛行機の初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAirplane->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// 飛行機のポインタを返す
	return pAirplane;
}