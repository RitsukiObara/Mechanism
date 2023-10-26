//===========================================
//
// ポークのメイン処理[pork.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "pork.h"
#include "pork_manager.h"
#include "useful.h"

#include "signboard.h"

//==============================
// コンストラクタ
//==============================
CPork::CPork() : CModel(CObject::TYPE_PORK, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pSignBoard = nullptr;	// 看板のポインタ

	m_pPrev = nullptr;		// 前へのポインタ
	m_pNext = nullptr;		// 次へのポインタ

	if (CPorkManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CPorkManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CPork::~CPork()
{

}

//============================
// 前のポインタの設定処理
//============================
void CPork::SetPrev(CPork* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CPork::SetNext(CPork* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CPork* CPork::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CPork* CPork::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CPork::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pSignBoard = nullptr;		// 看板のポインタ

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CPork::Uninit(void)
{
	if (m_pSignBoard != nullptr)
	{ // 看板が存在する場合

		// 終了処理
		m_pSignBoard->Uninit();
		m_pSignBoard = nullptr;
	}

	// 終了処理
	CModel::Uninit();

	if (CPorkManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CPorkManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CPork::Update(void)
{
	//if (m_pSignBoard != nullptr)
	//{ // 看板が NULL じゃない場合

	//	D3DXVECTOR3 rot = m_pSignBoard->GetRot();

	//	rot.y = D3DX_PI;

	//	m_pSignBoard->SetRot(rot);
	//}
}

//=====================================
//ブロックの描画処理
//=====================================
void CPork::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CPork::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetPosOld(pos);								// 前回の位置
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// 拡大率
	SetFileData(CXFile::TYPE_PORK);				// モデルの情報

	if (m_pSignBoard == nullptr)
	{ // 看板のポインタが NULL の場合

		// 看板の生成処理
		m_pSignBoard = CSignBoard::Create(pos);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}
}

//=======================================
// 生成処理
//=======================================
CPork* CPork::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ローカルオブジェクトを生成
	CPork* pPork = nullptr;	// インスタンスを生成

	if (pPork == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pPork = new CPork;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPork != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPork->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPork->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ポークのポインタを返す
	return pPork;
}