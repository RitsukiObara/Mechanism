//===========================================
//
// ネジのメイン処理[screw.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "screw.h"
#include "screw_manager.h"
#include "useful.h"

#include "Particle.h"
#include "destruction.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define INIT_ROT		(D3DXVECTOR3(0.0f,0.0f,0.7f))			// ネジの向き
#define ROT_MOVE		(0.04f)									// ネジの向きの移動量
#define DSTR_SIZE		(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// 飛沫演出のサイズ
#define DSTR_COL		(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f))		// 飛沫演出の色
#define DSTR_LIFE		(6)										// 飛沫演出の寿命

//==============================
// コンストラクタ
//==============================
CScrew::CScrew() : CModel(CObject::TYPE_SCREW, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_pPrev = nullptr;		// 前のポインタ
	m_pNext = nullptr;		// 次のポインタ

	if (CScrewManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CScrewManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CScrew::~CScrew()
{

}

//============================
// 前のポインタの設定処理
//============================
void CScrew::SetPrev(CScrew* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CScrew::SetNext(CScrew* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CScrew* CScrew::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CScrew* CScrew::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CScrew::Init(void)
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
void CScrew::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CScrewManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CScrewManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//ブロックの更新処理
//========================================
void CScrew::Update(void)
{
	// 回転処理
	Cycle();
}

//=====================================
//ブロックの描画処理
//=====================================
void CScrew::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// ヒット処理
//=====================================
void CScrew::Hit(const D3DXVECTOR3& pos)
{
	// 終了処理
	Uninit();

	// パーティクルの生成
	CParticle::Create(pos, CParticle::TYPE_ITEMGET);

	// 撃破の生成
	CDestruction::Create(pos, DSTR_SIZE, DSTR_COL, CDestruction::TYPE_AIRY, DSTR_LIFE);
}

//=====================================
// 情報の設定処理
//=====================================
void CScrew::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(INIT_ROT);							// 向き
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// 拡大率
	SetFileData(CXFile::TYPE_SCREW);			// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CScrew* CScrew::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CScrew* pScrew = nullptr;	// インスタンスを生成

	if (pScrew == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pScrew = new CScrew;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (pScrew != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pScrew->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "ネジの初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pScrew->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// ネジのポインタを返す
	return pScrew;
}

//=======================================
// 回転処理
//=======================================
void CScrew::Cycle(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();		// 向きの設定処理

	// 向きを加算する
	rot.y += ROT_MOVE;

	// 向きを適用する
	SetRot(rot);
}