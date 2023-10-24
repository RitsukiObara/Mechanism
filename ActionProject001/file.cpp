//============================================
//
// ファイルのメイン処理[file.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "screw.h"
#include "screw_manager.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "table.h"
#include "table_manager.h"
#include "airplane.h"
#include "airplane_manager.h"

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool型の表示
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// コンストラクタ
//===========================================
CFile::CFile()
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_pItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// アイテムの位置
	}

	m_pItemInfo.nNum = 0;				// 総数
	m_pItemInfo.bSuccess = false;		// 成功状況
}

//===========================================
// デストラクタ
//===========================================
CFile::~CFile()
{

}

//===========================================
// セーブ処理
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_ITEM:			// アイテム

		// アイテムのセーブ処理
		if (FAILED(SaveItem()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MACCHINA:		// マキナ草

		// マキナ草のセーブ処理
		if (FAILED(SaveMacchina()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_ENEMY:		// 敵

		// 敵のセーブ処理
		if(FAILED(SaveEnemy()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TABLE:		// 台

		// テーブルのセーブ処理
		if(FAILED(SaveTable()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_AIRPLANE:		// 飛行機

		// 飛行機のセーブ処理
		if (FAILED(SaveAirplane()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ロード処理
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_ITEM:			// アイテム

		// アイテムのロード処理
		if(FAILED(LoadItem()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MACCHINA:		// マキナ草

		// マキナ草のロード処理
		if(FAILED(LoadMacchina()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_ENEMY:		// 敵

		// 敵のロード処理
		if(FAILED(LoadEnemy()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TABLE:		// 台

		// 台のロード処理
		if(FAILED(LoadTable()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_AIRPLANE:		// 飛行機

		// 飛行機のロード処理
		if (FAILED(LoadAirplane()))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 結果を返す
	return S_OK;
}

//===========================================
// 初期化処理
//===========================================
HRESULT CFile::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_pItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// アイテムの位置
	}

	m_pItemInfo.nNum = 0;				// 総数
	m_pItemInfo.bSuccess = false;		// 成功状況

	// 成功を返す
	return S_OK;
}

//===========================================
// 終了処理
//===========================================
void CFile::Uninit(void)
{
	
}

//===========================================
// アイテムのセーブ処理
//===========================================
HRESULT CFile::SaveItem(void)
{
	// ローカル変数宣言
	CScrew* pScrew = CScrewManager::Get()->GetTop();		// 先頭のネジを代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen("data\\TXT\\Screw.txt", "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pScrew != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_SCREW\n");		// ネジの設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pScrew->GetPos().x, pScrew->GetPos().y, pScrew->GetPos().z);			// 位置を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_SCREW\n\n");			// ネジの設定の終了を書き込む

			// 次のオブジェクトを代入する
			pScrew = pScrew->GetNext();
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// マキナ草のセーブ処理
//===========================================
HRESULT CFile::SaveMacchina(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 敵のセーブ処理
//===========================================
HRESULT CFile::SaveEnemy(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 台のセーブ処理
//===========================================
HRESULT CFile::SaveTable(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 飛行機のセーブ処理
//===========================================
HRESULT CFile::SaveAirplane(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// アイテムのロード処理
//===========================================
HRESULT CFile::LoadItem(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// マキナ草のロード処理
//===========================================
HRESULT CFile::LoadMacchina(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 敵のロード処理
//===========================================
HRESULT CFile::LoadEnemy(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 台のロード処理
//===========================================
HRESULT CFile::LoadTable(void)
{
	// 成功を返す
	return S_OK;
}

//===========================================
// 飛行機のロード処理
//===========================================
HRESULT CFile::LoadAirplane(void)
{
	// 成功を返す
	return S_OK;
}