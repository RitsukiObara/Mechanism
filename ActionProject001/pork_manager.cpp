//============================================
//
// ポークマネージャー処理[pork_manager.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "pork.h"
#include "pork_manager.h"

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPorkManager* CPorkManager::m_pManager = nullptr;			// プレイヤーの変数

//============================
// コンストラクタ
//============================
CPorkManager::CPorkManager()
{
	// 全ての値をクリアする
	m_pTop = nullptr;		// 先頭のオブジェクト
	m_nNumAll = 0;			// 起伏の数
}

//============================
// 登録処理
//============================
void CPorkManager::Regist(CPork* pThis)
{
	if (m_pTop == nullptr)
	{ // オブジェクトが NULL の場合

		// 先頭のポインタに自分自身を代入
		m_pTop = pThis;

		// 前のオブジェクトへのポインタを設定する
		pThis->SetPrev(nullptr);

		// 次のオブジェクトへのポインタを設定する
		pThis->SetNext(nullptr);
	}
	else
	{ // 上記以外

		// ローカルポインタを宣言
		CPork* pObject = m_pTop;			// 先頭のオブジェクト

		while (pObject->GetNext() != nullptr)
		{ // オブジェクトがある限り回る

			// 次のオブジェクトを代入する
			pObject = pObject->GetNext();
		}

		// 比較オブジェクトの次のオブジェクトに自分自身を代入する
		pObject->SetNext(pThis);

		// 次のオブジェクトに NULL を入れる
		pThis->SetNext(nullptr);

		// 現在の比較オブジェクトを自分の前のオブジェクトに設定する
		pThis->SetPrev(pObject);
	}

	// 総数を加算する
	m_nNumAll++;
}

//============================
// 終了処理
//============================
void CPorkManager::Uninit(void)
{
	// ローカル変数宣言
	CPork* pObj = nullptr;		// 現在のオブジェクトのポインタ

	// オブジェクトを代入する
	pObj = m_pTop;

	while (pObj != nullptr)
	{ // オブジェクトと引数が一致していない限り回す

		// 引き抜き処理
		m_pManager->Pull(pObj);

		// 次のオブジェクトを代入する
		pObj = pObj->GetNext();
	}

	// マネージャーのメモリを解放する
	delete m_pManager;
	m_pManager = nullptr;
}

//============================
// デストラクタ
//============================
CPorkManager::~CPorkManager()
{

}

//===========================================
// オブジェクトの取得処理
//===========================================
CPork* CPorkManager::GetTop(void)
{
	// オブジェクトの情報を渡す
	return m_pTop;
}

//===========================================
// リスト構造の引き抜き処理
//===========================================
void CPorkManager::Pull(CPork* pThis)
{
	// ローカル変数宣言
	CPork* pObj = nullptr;		// 現在のオブジェクトのポインタ

	// オブジェクトを代入する
	pObj = m_pTop;

	while (pObj != pThis)
	{ // オブジェクトと引数が一致していない限り回す

		// 次のオブジェクトを代入する
		pObj = pObj->GetNext();
	}

	if (pObj->GetPrev() != nullptr)
	{ // 前のオブジェクトが NULL じゃない場合

		// リスト構造から自分を抜き出す
		pObj->GetPrev()->SetNext(pObj->GetNext());
	}

	if (pObj->GetNext() != nullptr)
	{ // 次のオブジェクトが NULL じゃない場合

		// リスト構造から自分を抜き出す
		pObj->GetNext()->SetPrev(pObj->GetPrev());
	}

	if (pObj == m_pTop)
	{ // 先頭だった場合

		// 先頭のポインタを引き渡す
		m_pTop = pObj->GetNext();
	}

	// 総数を減算する
	m_nNumAll--;
}

//============================
//生成処理
//============================
CPorkManager* CPorkManager::Create(void)
{
	if (m_pManager == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		m_pManager = new CPorkManager;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// オブジェクトのポインタを返す
		return m_pManager;
	}

	if (m_pManager != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// オブジェクトのポインタを返す
		return m_pManager;
	}
	else
	{ // オブジェクトが NULL の場合

		// オブジェクトを返す
		return nullptr;
	}
}

//============================
// 取得処理
//============================
CPorkManager* CPorkManager::Get(void)
{
	// マネージャーのポインタを返す
	return m_pManager;
}