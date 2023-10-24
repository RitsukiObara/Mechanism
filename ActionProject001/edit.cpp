// デバッグ版
#ifdef _DEBUG
//===========================================
//
// エディットのメイン処理[edit.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "input.h"
#include "edit.h"
#include "useful.h"
#include "debugproc.h"

#include "screw.h"
#include "screw_manager.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "enemy_manager.h"
#include "table.h"
#include "table_manager.h"
#include "airplane.h"
#include "airplane_manager.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NORMAL_SPEED		(16.0f)		// 通常時の速度
#define ADJUST_SPEED		(2.0f)		// 微調整時の速度
#define MACCHINA_SHIFT		(100.0f)	// マキナ草のずらす幅
#define NEAR_POS			(0.0f)		// 手前の位置
#define FAR_POS				(1000.0f)	// 奥行の位置

//==============================
// コンストラクタ
//==============================
CEdit::CEdit() : CModel(CObject::TYPE_EDIT, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_type = TYPE_ITEM;					// 種類
	m_enemyType = CEnemy::TYPE_ITOCAN;	// 敵の種類
	m_bFront = true;					// 奥行状況
	m_bAirplaneFront = true;			// 飛行機の向きの状況
}

//==============================
// デストラクタ
//==============================
CEdit::~CEdit()
{

}

//==============================
//ブロックの初期化処理
//==============================
HRESULT CEdit::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_type = TYPE_ITEM;					// 種類
	m_enemyType = CEnemy::TYPE_ITOCAN;	// 敵の種類
	m_bFront = true;					// 奥行状況
	m_bAirplaneFront = true;			// 飛行機の向きの状況

	// 値を返す
	return S_OK;
}

//========================================
//ブロックの終了処理
//========================================
void CEdit::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//========================================
//ブロックの更新処理
//========================================
void CEdit::Update(void)
{
	// 前後状況の設定処理
	Front();

	switch (m_type)
	{
	case CEdit::TYPE_ITEM:

		// アイテムエディットの処理
		ItemProcess();

		break;

	case CEdit::TYPE_MACCHINA:

		// マキナ草エディットの処理
		MacchinaProcess();

		break;

	case CEdit::TYPE_ENEMY:

		// 敵のエディット処理
		EnemyProcess();

		break;

	case CEdit::TYPE_TABLE:


		break;

	case CEdit::TYPE_AIRPLANE:

		// 飛行機のエディット処理
		AirplaneProcess();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 移動のインプット処理
	MoveInput();

	// 微調整移動のインプット処理
	AdjustMoveInput();

	// 種類の設定処理
	Type();

	// 移動処理
	Move();

	// 消去処理
	Delete();

	// 設置処理
	Set();

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n種類：%d\n手前状況：%d(0：奥/1：手前)\nW/A/S/Dキー：移動\nSPACEキー：種類変更\nENTERキー：手前状況設定\n0キー：設置\n9キー：消去\n", GetPos().x, GetPos().y, GetPos().z, m_type, m_bFront);
}

//=====================================
//ブロックの描画処理
//=====================================
void CEdit::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CEdit::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));	// 拡大率
	SetFileData(CXFile::TYPE_SCREW);			// モデルの情報

	// 全ての値を設定する
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_type = TYPE_ITEM;					// 種類
	m_enemyType = CEnemy::TYPE_ITOCAN;	// 敵の種類
	m_bFront = true;					// 奥行状況
	m_bAirplaneFront = true;			// 飛行機の向きの状況
}

//=======================================
// 生成処理
//=======================================
CEdit* CEdit::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEdit* pScrew = nullptr;	// インスタンスを生成

	if (pScrew == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pScrew = new CEdit;
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

			// 停止
			assert(false);

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
// アイテムエディットの処理
//=======================================
void CEdit::ItemProcess(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押している場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_1) == true)
		{ // 1キーを押している場合

			// 位置を設定する
			pos.z += NORMAL_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_2) == true)
		{ // 2キーを押している場合

			// 位置を設定する
			pos.z -= NORMAL_SPEED;
		}
	}
	else
	{ // 上記以外

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
		{ // 1キーを押した場合

			// 位置を設定する
			pos.z += ADJUST_SPEED;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2) == true)
		{ // 2キーを押した場合

			// 位置を設定する
			pos.z -= ADJUST_SPEED;
		}
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// マキナ草エディットの処理
//=======================================
void CEdit::MacchinaProcess(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	if (m_bFront == true)
	{ // 奥行状況が true の場合

		// 手前に置く
		pos.z = NEAR_POS + MACCHINA_SHIFT;
	}
	else
	{ // 上記以外

		// 奥に置く
		pos.z = FAR_POS + MACCHINA_SHIFT;
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 敵エディットの処理
//=======================================
void CEdit::EnemyProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1キーを押した場合

		// 敵の種類を切り替える
		m_enemyType = (CEnemy::TYPE)((m_enemyType + 1) % CEnemy::TYPE_MAX);
	}
}

//=======================================
// 飛行機エディットの処理
//=======================================
void CEdit::AirplaneProcess(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 rot = GetRot();		// 向きを取得する

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1キーを押した場合

		// 向き状況の設定処理
		m_bAirplaneFront = m_bAirplaneFront ? false : true;

		if (m_bAirplaneFront != true)
		{ // 前向き状況場合

			// 向きを設定する
			rot.y = D3DX_PI;
		}
		else
		{ // 上記以外

			// 向きを設定する
			rot.y = 0.0f;
		}
	}

	// 向きを適用する
	SetRot(rot);
}

//=======================================
// マキナ草の設定処理
//=======================================
void CEdit::SetMaccina(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置

	// 位置をずらす
	pos.z += MACCHINA_SHIFT;

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 移動処理
//=======================================
void CEdit::MoveInput(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左シフトキーを押していた場合

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // Wキーを押していた場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // Aキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * -0.25f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * -0.25f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // Dキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * 0.25f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * 0.25f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // 上記以外

			// 移動量を設定する
			m_move.x = sinf(0.0f) * NORMAL_SPEED;
			m_move.y = cosf(0.0f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // Sキーを押していた場合

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
		{ // Aキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * -0.75f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * -0.75f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
		{ // Dキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * 0.75f) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI * 0.75f) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // 上記以外

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI) * NORMAL_SPEED;
			m_move.y = cosf(D3DX_PI) * NORMAL_SPEED;
			m_move.z = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // Aキーを押した場合

		// 移動量を設定する
		m_move.x = sinf(D3DX_PI * -0.5f) * NORMAL_SPEED;
		m_move.y = cosf(D3DX_PI * -0.5f) * NORMAL_SPEED;
		m_move.z = 0.0f;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // Dキーを押した場合

		// 移動量を設定する
		m_move.x = sinf(D3DX_PI * 0.5f) * NORMAL_SPEED;
		m_move.y = cosf(D3DX_PI * 0.5f) * NORMAL_SPEED;
		m_move.z = 0.0f;
	}
	else
	{ // 上記以外

		// 移動量を設定する
		m_move = NONE_D3DXVECTOR3;
	}
}

//=======================================
// 微調整移動のインプット処理
//=======================================
void CEdit::AdjustMoveInput(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // 左CTRLキーを押していた場合

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true)
		{ // Wキーを押していた場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
			{ // Aキーを押した場合

				// 移動量を設定する
				m_move.x = sinf(D3DX_PI * -0.25f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * -0.25f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
			{ // Dキーを押した場合

				// 移動量を設定する
				m_move.x = sinf(D3DX_PI * 0.25f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * 0.25f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else
			{ // 上記以外

				// 移動量を設定する
				m_move.x = sinf(0.0f) * ADJUST_SPEED;
				m_move.y = cosf(0.0f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true)
		{ // Sキーを押していた場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
			{ // Aキーを押した場合

				// 移動量を設定する
				m_move.x = sinf(D3DX_PI * -0.75f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * -0.75f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
			{ // Dキーを押した場合

				// 移動量を設定する
				m_move.x = sinf(D3DX_PI * 0.75f) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI * 0.75f) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
			else
			{ // 上記以外

				// 移動量を設定する
				m_move.x = sinf(D3DX_PI) * ADJUST_SPEED;
				m_move.y = cosf(D3DX_PI) * ADJUST_SPEED;
				m_move.z = 0.0f;
			}
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
		{ // Aキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * -0.5f) * ADJUST_SPEED;
			m_move.y = cosf(D3DX_PI * -0.5f) * ADJUST_SPEED;
			m_move.z = 0.0f;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
		{ // Dキーを押した場合

			// 移動量を設定する
			m_move.x = sinf(D3DX_PI * 0.5f) * ADJUST_SPEED;
			m_move.y = cosf(D3DX_PI * 0.5f) * ADJUST_SPEED;
			m_move.z = 0.0f;
		}
		else
		{ // 上記以外

			// 移動量を設定する
			m_move = NONE_D3DXVECTOR3;
		}
	}
}

//=======================================
// 移動処理
//=======================================
void CEdit::Move(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	// 位置を更新する
	pos += m_move;

	// 位置が奇数の場合偶数にする
	pos.x += ((int)(pos.x) % 2 == 0) ? 0 : 1;
	pos.y += ((int)(pos.y) % 2 == 0) ? 0 : 1;

	// 位置を切り捨てする
	pos.x = floorf(pos.x);
	pos.y = floorf(pos.y);

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 種類処理
//=======================================
void CEdit::Type(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACEキーを押した場合

		// 種類を設定する
		m_type = (TYPE)((m_type + 1) % TYPE_MAX);

		switch (m_type)
		{
		case CEdit::TYPE_ITEM:

			// モデルの情報設定処理
			SetFileData(CXFile::TYPE_SCREW);

			break;

		case CEdit::TYPE_MACCHINA:

			// モデルの情報設定処理
			SetFileData(CXFile::TYPE_MACCHINA);

			// マキナ草の設定処理
			SetMaccina();

			break;

		case CEdit::TYPE_ENEMY:

			// モデルの情報設定処理
			SetFileData(CXFile::TYPE_ITOCAN);

			break;

		case CEdit::TYPE_TABLE:

			// モデルの情報設定処理
			SetFileData(CXFile::TYPE_TABLE);

			break;

		case CEdit::TYPE_AIRPLANE:

			// モデルの情報設定処理
			SetFileData(CXFile::TYPE_AIRPLANE);

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
}

//=======================================
// 奥行設定処理
//=======================================
void CEdit::Front(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // ENTERキーを押した場合

		// 前後状況を入れ替える
		m_bFront = m_bFront ? false : true;
	}

	if (m_bFront == true)
	{ // 奥行状況が true の場合

		// 手前に置く
		pos.z = NEAR_POS;
	}
	else
	{ // 上記以外

		// 奥に置く
		pos.z = FAR_POS;
	}

	// 位置を適用する
	SetPos(pos);
}

//=======================================
// 設定処理
//=======================================
void CEdit::Set(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0キーを押した場合

		switch (m_type)
		{
		case CEdit::TYPE_ITEM:

			// ネジの生成処理
			CScrew::Create(pos, NONE_D3DXVECTOR3, false);

			break;

		case CEdit::TYPE_MACCHINA:

			// マキナ草の生成処理
			CMacchina::Create(pos);

			break;

		case CEdit::TYPE_ENEMY:

			// 敵の生成処理
			CEnemy::Create(pos, m_enemyType);

			break;

		case CEdit::TYPE_TABLE:

			// 台の生成処理
			CTable::Create(pos);

			break;

		case CEdit::TYPE_AIRPLANE:

			// 飛行機の生成処理
			CAirplane::Create(pos, rot);

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
}

//=======================================
// 消去処理
//=======================================
void CEdit::Delete(void)
{
	switch (m_type)
	{
	case CEdit::TYPE_ITEM:

		// アイテムの消去処理
		DeleteItem();

		break;

	case CEdit::TYPE_MACCHINA:

		// マキナ草の消去処理
		DeleteMacchina();

		break;

	case CEdit::TYPE_ENEMY:

		// 敵の消去処理
		DeleteEnemy();

		break;

	case CEdit::TYPE_TABLE:

		// 台の消去処理
		DeleteTable();

		break;

	case CEdit::TYPE_AIRPLANE:

		// 飛行機の消去処理
		DeleteAirplane();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// 死亡判定処理
		CObject::DeathDecision(nCnt);
	}
}

//=======================================
// アイテムの消去処理
//=======================================
void CEdit::DeleteItem(void)
{
	// ローカル変数宣言
	CScrew* pScrew = CScrewManager::Get()->GetTop();		// アイテムのポインタ
	CScrew* pScrewNext;										// 次のアイテム

	while (pScrew != nullptr)
	{ // アイテムが NULL じゃない場合回す
		 
		// 次のアイテムを設定する
		pScrewNext = pScrew->GetNext();

		if (useful::RectangleCollisionXY(pScrew->GetPos(), GetPos(), pScrew->GetFileData().collsize, GetFileData().collsize, -pScrew->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), GetPos(), pScrew->GetFileData().collsize, GetFileData().collsize, -pScrew->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // 当たり判定が true の場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9キーを押した場合

				// アイテムを消す
				pScrew->Uninit();
			}
		}

		// 次のアイテムを代入する
		pScrew = pScrewNext;
	}
}

//=======================================
// マキナ草の消去処理
//=======================================
void CEdit::DeleteMacchina(void)
{
	// ローカル変数宣言
	CMacchina* pMacchina = CMacchinaManager::Get()->GetTop();		// マキナ草のポインタ
	CMacchina* pMacchinaNext;										// 次のマキナ草

	while (pMacchina != nullptr)
	{ // マキナ草が NULL じゃない場合回す
		 
		// 次のマキナ草を設定する
		pMacchinaNext = pMacchina->GetNext();

		if (useful::RectangleCollisionXY(pMacchina->GetPos(), GetPos(), pMacchina->GetFileData().collsize, GetFileData().collsize, -pMacchina->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pMacchina->GetPos(), GetPos(), pMacchina->GetFileData().collsize, GetFileData().collsize, -pMacchina->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // 当たり判定が true の場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9キーを押した場合

				// マキナ草を消す
				pMacchina->Uninit();
			}
		}

		// 次のマキナ草を代入する
		pMacchina = pMacchinaNext;
	}
}

//=======================================
// 敵の消去処理
//=======================================
void CEdit::DeleteEnemy(void)
{
	// ローカル変数宣言
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// 敵のポインタ
	CEnemy* pEnemyNext;										// 次の敵

	while (pEnemy != nullptr)
	{ // 敵が NULL じゃない場合回す
		 
		// 次の敵を設定する
		pEnemyNext = pEnemy->GetNext();

		if (useful::RectangleCollisionXY(pEnemy->GetPos(), GetPos(), pEnemy->GetFileData().collsize, GetFileData().collsize, -pEnemy->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pEnemy->GetPos(), GetPos(), pEnemy->GetFileData().collsize, GetFileData().collsize, -pEnemy->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // 当たり判定が true の場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9キーを押した場合

				// 敵を消す
				pEnemy->Uninit();
			}
		}

		// 次の敵を代入する
		pEnemy = pEnemyNext;
	}
}

//=======================================
// 台の消去処理
//=======================================
void CEdit::DeleteTable(void)
{
	// ローカル変数宣言
	CTable* pTable = CTableManager::Get()->GetTop();		// 台のポインタ
	CTable* pTableNext;										// 次の台

	while (pTable != nullptr)
	{ // 台が NULL じゃない場合回す
		 
		// 次の台を設定する
		pTableNext = pTable->GetNext();

		if (useful::RectangleCollisionXY(pTable->GetPos(), GetPos(), pTable->GetFileData().collsize, GetFileData().collsize, -pTable->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pTable->GetPos(), GetPos(), pTable->GetFileData().collsize, GetFileData().collsize, -pTable->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // 当たり判定が true の場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9キーを押した場合

				// 台を消す
				pTable->Uninit();
			}
		}

		// 次の台を代入する
		pTable = pTableNext;
	}
}

//=======================================
// 飛行機の消去処理
//=======================================
void CEdit::DeleteAirplane(void)
{
	// ローカル変数宣言
	CAirplane* pAirplane = CAirplaneManager::Get()->GetTop();		// 飛行機のポインタ
	CAirplane* pAirplaneNext;										// 次の飛行機

	while (pAirplane != nullptr)
	{ // 飛行機が NULL じゃない場合回す
		 
		// 次の飛行機を設定する
		pAirplaneNext = pAirplane->GetNext();

		if (useful::RectangleCollisionXY(pAirplane->GetPos(), GetPos(), pAirplane->GetFileData().collsize, GetFileData().collsize, -pAirplane->GetFileData().collsize, -GetFileData().collsize) == true &&
			useful::RectangleCollisionXZ(pAirplane->GetPos(), GetPos(), pAirplane->GetFileData().collsize, GetFileData().collsize, -pAirplane->GetFileData().collsize, -GetFileData().collsize) == true)
		{ // 当たり判定が true の場合

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_9) == true)
			{ // 9キーを押した場合

				// 飛行機を消す
				pAirplane->Uninit();
			}
		}

		// 次の飛行機を代入する
		pAirplane = pAirplaneNext;
	}
}

#endif