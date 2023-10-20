//===========================================
//
// ゴールのメイン処理[goal.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "goal.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define CYCLE_COUNT		(40)			// 向きが変わるカウント

//==============================
// コンストラクタ
//==============================
CGoal::CGoal() : CObject(CObject::TYPE_GOAL, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		m_aGoal[nCnt] = nullptr;	// ゴールの変数
	}
	m_type = TYPE_PUNCH;			// 種類
	m_state = STATE_CYCLE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_fRotDest = 0.0f;				// 目標の向き
}

//==============================
// デストラクタ
//==============================
CGoal::~CGoal()
{

}

//==============================
// ゴールの初期化処理
//==============================
HRESULT CGoal::Init(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		if (m_aGoal[nCnt] == nullptr)
		{ // オブジェクトが NULL の場合

			// インスタンスを生成
			m_aGoal[nCnt] = new CModel(TYPE_NONE, PRIORITY_PLAYER);
		}
		else
		{ // オブジェクトが NULL じゃない場合

			// 停止
			assert(false);

			// 失敗 を返す
			return E_FAIL;
		}

		if (m_aGoal[nCnt] != nullptr)
		{ // オブジェクトが NULL じゃない場合

			// 初期化処理
			if (FAILED(m_aGoal[nCnt]->Init()))
			{ // 初期化に失敗した場合

				// 停止
				assert(false);

				// 失敗 を返す
				return E_FAIL;
			}
		}
		else
		{ // オブジェクトが NULL の場合

			// 停止
			assert(false);

			// 失敗 を返す
			return E_FAIL;
		}
	}

	// 全ての値を初期化する
	m_type = TYPE_PUNCH;			// 種類
	m_state = STATE_CYCLE;			// 状態
	m_nStateCount = 0;				// 状態カウント
	m_fRotDest = 0.0f;				// 目標の向き

	// 成功を返す
	return S_OK;
}

//========================================
// ゴールの終了処理
//========================================
void CGoal::Uninit(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// 終了処理
		m_aGoal[nCnt]->Uninit();
		m_aGoal[nCnt] = nullptr;
	}

	// 本体の終了処理
	Release();

	// ゴールの消去処理
	CGame::DeleteGoal();
}

//========================================
// ゴールの更新処理
//========================================
void CGoal::Update(void)
{
	switch (m_state)
	{
	case CGoal::STATE_CYCLE:		// 回転状態

			// 向きの決定処理
		RotDecide(&m_fRotDest);

		// 向きの補正処理
		RotCorrect();

		// 状態カウントを加算する
		m_nStateCount++;

		if (m_nStateCount % CYCLE_COUNT == 0)
		{ // 状態カウントが一定数になった場合

			// 種類を変える
			m_type = (TYPE)((m_type + 1) % TYPE::TYPE_MAX);
		}

		break;

	case CGoal::STATE_STOP:			// 停止状態


		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=====================================
// ゴールの描画処理
//=====================================
void CGoal::Draw(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// 描画処理
		m_aGoal[nCnt]->Draw();
	}
}

//=====================================
// ヒット処理
//=====================================
void CGoal::Hit(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = m_aGoal[MODEL_POINT]->GetRot();		// 向きを取得する

	// 向きの決定処理
	RotDecide(&rot.y);

	// 向きを適用する
	m_aGoal[MODEL_POINT]->SetRot(rot);

	// 停止状態にする
	m_state = STATE_STOP;

	// 状態カウントを初期化する
	m_nStateCount = 0;
}

//=====================================
// 情報の設定処理
//=====================================
void CGoal::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// 情報の設定処理
		m_aGoal[nCnt]->SetPos(pos);									// 位置
		m_aGoal[nCnt]->SetPosOld(pos);								// 前回の位置
		m_aGoal[nCnt]->SetRot(NONE_D3DXVECTOR3);					// 向き
		m_aGoal[nCnt]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));		// 拡大率

		// モデルの情報
		switch (nCnt)
		{
		case MODEL_BODY:			// 本体

			m_aGoal[nCnt]->SetFileData(CXFile::TYPE_GOAL);

			break;

		case MODEL_POINT:			// 得点

			m_aGoal[nCnt]->SetFileData(CXFile::TYPE_GOALPOINT);

			break;
		}
	}

	// 全ての値を設定する
	m_type = TYPE_PUNCH;			// 種類
	m_nStateCount = 0;				// 状態カウント
	m_fRotDest = 0.0f;				// 目標の向き
}

//=======================================
// モデルの設定処理
//=======================================
CModel* CGoal::GetModel(const MODEL model)
{
	// モデルの情報を返す
	return m_aGoal[model];
}

//=======================================
// 生成処理
//=======================================
CGoal* CGoal::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CGoal* pGoal = nullptr;		// インスタンスを生成

	if (pGoal == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pGoal = new CGoal;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pGoal != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pGoal->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pGoal->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ゴールのポインタを返す
	return pGoal;
}

//=======================================
// 向きの決定処理
//=======================================
void CGoal::RotDecide(float* m_fRot)
{
	switch (m_type)
	{
	case CGoal::TYPE_PUNCH:		// パンチ

		*m_fRot = 0.0f;

		break;

	case CGoal::TYPE_SMALL_R:	// +1000

		*m_fRot = -D3DX_PI * 0.5f;

		break;

	case CGoal::TYPE_BIG:		// +2000

		*m_fRot = D3DX_PI;

		break;

	case CGoal::TYPE_SMALL_L:	// +1000

		*m_fRot = D3DX_PI* 0.5f;

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// 向きの補正処理
//=======================================
void CGoal::RotCorrect(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = m_aGoal[MODEL_POINT]->GetRot();		// 向きを取得する

	// 向きの正規化
	useful::RotCorrect(m_fRotDest, &rot.y, 0.5f);

	// 向きを適用する
	m_aGoal[MODEL_POINT]->SetRot(rot);
}