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
		m_ItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// アイテムの位置
		m_MacchinaInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// マキナ草の位置
		m_EnemyInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// 敵の位置
		m_EnemyInfo.type[nCnt] = CEnemy::TYPE_ITOCAN;	// 敵の種類
		m_TableInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// 台の位置
		m_AirplaneInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// 飛行機の位置
		m_AirplaneInfo.bFront[nCnt] = false;			// 飛行機の向き
	}

	// 総数をクリアする
	m_ItemInfo.nNum = 0;				// アイテム
	m_MacchinaInfo.nNum = 0;			// マキナ草
	m_EnemyInfo.nNum = 0;				// 敵
	m_TableInfo.nNum = 0;				// 台
	m_AirplaneInfo.nNum = 0;			// 飛行機

	// 成功状況をクリアする
	m_ItemInfo.bSuccess = false;		// アイテム
	m_MacchinaInfo.bSuccess = false;	// マキナ草
	m_EnemyInfo.bSuccess = false;		// 敵
	m_TableInfo.bSuccess = false;		// 台
	m_AirplaneInfo.bSuccess = false;	// 飛行機
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
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_FILE_DATA; nCnt++)
	{
		m_ItemInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// アイテムの位置
		m_MacchinaInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// マキナ草の位置
		m_EnemyInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// 敵の位置
		m_EnemyInfo.type[nCnt] = CEnemy::TYPE_ITOCAN;	// 敵の種類
		m_TableInfo.pos[nCnt] = NONE_D3DXVECTOR3;		// 台の位置
		m_AirplaneInfo.pos[nCnt] = NONE_D3DXVECTOR3;	// 飛行機の位置
		m_AirplaneInfo.bFront[nCnt] = false;			// 飛行機の向き
	}

	// 総数をクリアする
	m_ItemInfo.nNum = 0;				// アイテム
	m_MacchinaInfo.nNum = 0;			// マキナ草
	m_EnemyInfo.nNum = 0;				// 敵
	m_TableInfo.nNum = 0;				// 台
	m_AirplaneInfo.nNum = 0;			// 飛行機

	// 成功状況をクリアする
	m_ItemInfo.bSuccess = false;		// アイテム
	m_MacchinaInfo.bSuccess = false;	// マキナ草
	m_EnemyInfo.bSuccess = false;		// 敵
	m_TableInfo.bSuccess = false;		// 台
	m_AirplaneInfo.bSuccess = false;	// 飛行機

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
	// ローカル変数宣言
	CMacchina* pScrew = CMacchinaManager::Get()->GetTop();		// 先頭のマキナ草を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen("data\\TXT\\Macchina.txt", "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pScrew != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_MACCHINA\n");	// マキナ草の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pScrew->GetPos().x, pScrew->GetPos().y, pScrew->GetPos().z);			// 位置を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_MACCHINA\n\n");		// マキナ草の設定の終了を書き込む

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
// 敵のセーブ処理
//===========================================
HRESULT CFile::SaveEnemy(void)
{
	// ローカル変数宣言
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// 先頭の敵を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen("data\\TXT\\Enemy.txt", "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pEnemy != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_ENEMY\n");		// 敵の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pEnemy->GetPos().x, pEnemy->GetPos().y, pEnemy->GetPos().z);			// 位置を書き込む

			fprintf(pFile, "\tTYPE = ");		// 種類の設定を書き込む
			fprintf(pFile, "%d\n", pEnemy->GetType());			// 種類を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_ENEMY\n\n");		// 敵の設定の終了を書き込む

			// 次のオブジェクトを代入する
			pEnemy = pEnemy->GetNext();
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
// 台のセーブ処理
//===========================================
HRESULT CFile::SaveTable(void)
{
	// ローカル変数宣言
	CTable* pTable = CTableManager::Get()->GetTop();		// 先頭の台を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen("data\\TXT\\Table.txt", "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pTable != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_TABLE\n");		// 台の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pTable->GetPos().x, pTable->GetPos().y, pTable->GetPos().z);			// 位置を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_TABLE\n\n");	// 台の設定の終了を書き込む

			// 次のオブジェクトを代入する
			pTable = pTable->GetNext();
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
// 飛行機のセーブ処理
//===========================================
HRESULT CFile::SaveAirplane(void)
{
	// ローカル変数宣言
	CAirplane* pAirplane = CAirplaneManager::Get()->GetTop();		// 先頭の飛行機を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen("data\\TXT\\Airplane.txt", "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pAirplane != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_AIRPLANE\n");	// 飛行機の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pAirplane->GetPos().x, pAirplane->GetPos().y, pAirplane->GetPos().z);			// 位置を書き込む

			fprintf(pFile, "\tFRONT = ");		// 前後状況の設定を書き込む
			fprintf(pFile, "%s\n", c_apBooleanDisp[(int)(pAirplane->GetFront())]);		// 前後状況を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_AIRPLANE\n\n");		// 飛行機の設定の終了を書き込む

			// 次のオブジェクトを代入する
			pAirplane = pAirplane->GetNext();
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