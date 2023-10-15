//===========================================
//
// 敵のメイン処理[enemy.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "collision.h"
#include "useful.h"

#include "player.h"
#include "objectElevation.h"
#include "elevation_manager.h"

#include "itocan.h"

//==============================
// コンストラクタ
//==============================
CEnemy::CEnemy() : CModel(CObject::TYPE_ENEMY, CObject::PRIORITY_ENTITY)
{
	// コンストラクタの箱
	Box();
}

//==============================
// オーバーロードコンストラクタ
//==============================
CEnemy::CEnemy(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// コンストラクタの箱
	Box();
}

//==============================
// デストラクタ
//==============================
CEnemy::~CEnemy()
{

}

//==============================
// コンストラクタの箱
//==============================
void CEnemy::Box(void)
{
	// 全ての値をクリアする
	m_posInit = NONE_D3DXVECTOR3;	// 初期位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_bStep = false;				// 踏みつけ状況
	m_bCollision = true;			// 当たり判定を通るかどうか
	m_pPrev = nullptr;				// 前のポインタ
	m_pNext = nullptr;				// 次のポインタ

	if (CEnemyManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CEnemyManager::Get()->Regist(this);
	}
}

//============================
// 前のポインタの設定処理
//============================
void CEnemy::SetPrev(CEnemy* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CEnemy::SetNext(CEnemy* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CEnemy* CEnemy::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CEnemy* CEnemy::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CEnemy::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_posInit = NONE_D3DXVECTOR3;	// 初期位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_bStep = false;				// 踏みつけ状況
	m_bCollision = true;			// 当たり判定を通るかどうか

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CEnemy::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CEnemyManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CEnemyManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
//ブロックの描画処理
//=====================================
void CEnemy::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// ヒット処理
//=====================================
void CEnemy::Hit(void)
{

}

//=====================================
// 情報の設定処理
//=====================================
void CEnemy::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// 拡大率
	SetFileData(CXFile::TYPE_ITOCAN);			// モデルの情報

	// 全ての値を設定する
	m_posInit = pos;				// 初期位置
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_bStep = false;				// 踏みつけ状況
	m_bCollision = true;			// 当たり判定を通るかどうか
}

//=======================================
// 生成処理
//=======================================
CEnemy* CEnemy::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ローカルオブジェクトを生成
	CEnemy* pEnemy = nullptr;	// インスタンスを生成

	if (pEnemy == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case TYPE_ITOCAN:

			// インスタンスを生成
			pEnemy = new CItocan;

			break;

		default:

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;

			break;
		}
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return nullptr;
	}

	if (pEnemy != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEnemy->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "ネジの初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEnemy->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// ネジのポインタを返す
	return pEnemy;
}

//=======================================
// 移動量の設定処理
//=======================================
void CEnemy::SetMove(const D3DXVECTOR3& move)
{
	// 移動量を設定する
	m_move = move;
}

//=======================================
// 移動量の取得処理
//=======================================
D3DXVECTOR3 CEnemy::GetMove(void) const
{
	// 移動量を返す
	return m_move;
}

//=======================================
// 踏みつけ状況の設定処理
//=======================================
void CEnemy::SetEnableStep(const bool bStep)
{
	// 踏みつけ状況を設定する
	m_bStep = bStep;
}

//=======================================
// 踏みつけ状況の取得処理
//=======================================
bool CEnemy::IsStep(void) const
{
	// 踏みつけ状況を返す
	return m_bStep;
}

//=======================================
// 初期位置の取得処理
//=======================================
D3DXVECTOR3 CEnemy::GetInitPos(void) const
{
	// 初期位置を返す
	return m_posInit;
}

//=======================================
// 当たり判定状況の設定処理
//=======================================
void CEnemy::SetEnableCollision(const bool bColl)
{
	// 当たり判定状況を設定する
	m_bCollision = bColl;
}

//=======================================
// 当たり判定状況の取得処理
//=======================================
bool CEnemy::IsCollision(void) const
{
	// 当たり判定を返す
	return m_bCollision;
}

//=======================================
// 重力処理
//=======================================
void CEnemy::Gravity(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();			// 位置を取得する

	// 重力処理
	useful::Gravity(&m_move.y, pos, 0.5f);

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 起伏地面の当たり判定処理
//=======================================
bool CEnemy::ElevationCollision(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ
	bool bLand = false;						// 着地判定

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);
		
		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			// 重力を設定する
			m_move.y = 0.0f;

			// 着地判定を付ける
			bLand = true;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);

	// 着地判定を返す
	return bLand;
}