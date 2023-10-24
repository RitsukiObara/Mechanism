//============================================
//
// ファイルヘッダー[file.h]
// Author：小原立暉
//
//============================================
#ifndef _FILE_H_			//このマクロ定義がされていなかったら
#define _FILE_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "enemy.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// ファイルのデータの最大数

//--------------------------------------------
// クラス(ファイル読み込みクラス)
//--------------------------------------------
class CFile
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_ITEM = 0,		// アイテム
		TYPE_MACCHINA,		// マキナ草
		TYPE_ENEMY,			// 敵
		TYPE_TABLE,			// 台
		TYPE_AIRPLANE,		// 飛行機
		TYPE_MAX			// この列挙型の総数
	};

	// 構造体定義(アイテムの情報)
	struct SItemInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// 位置
		int nNum;							// 総数
		bool bSuccess;						// 成功状況
	};

	// 構造体定義(マキナ草の情報)
	struct SMacchinaInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// 位置
		int nNum;							// 総数
		bool bSuccess;						// 成功状況
	};

	// 構造体定義(敵の情報)
	struct SEnemyInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// 位置
		CEnemy::TYPE type[MAX_FILE_DATA];	// 種類
		int nNum;							// 総数
		bool bSuccess;						// 成功状況
	};

	// 構造体定義(台の情報)
	struct STableInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// 位置
		int nNum;							// 総数
		bool bSuccess;						// 成功状況
	};

	// 構造体定義(飛行機の情報)
	struct SAirplaneInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];		// 位置
		bool bFront[MAX_FILE_DATA];			// 前後状況
		int nNum;							// 総数
		bool bSuccess;						// 成功状況
	};

	CFile();					// コンストラクタ
	~CFile();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理

	HRESULT Save(const TYPE type);	// セーブ処理
	HRESULT Load(const TYPE type);	// ロード処理

private:		// 自分のみアクセスできる

	// メンバ関数(セーブ関係)
	HRESULT SaveItem(void);			// アイテムのセーブ処理
	HRESULT SaveMacchina(void);		// マキナ草のセーブ処理
	HRESULT SaveEnemy(void);		// 敵のセーブ処理
	HRESULT SaveTable(void);		// 台のセーブ処理
	HRESULT SaveAirplane(void);		// 飛行機のセーブ処理

	// メンバ関数(ロード関係)
	HRESULT LoadItem(void);			// アイテムのロード処理
	HRESULT LoadMacchina(void);		// マキナ草のロード処理
	HRESULT LoadEnemy(void);		// 敵のロード処理
	HRESULT LoadTable(void);		// 台のロード処理
	HRESULT LoadAirplane(void);		// 飛行機のロード処理

	// メンバ変数
	SItemInfo m_ItemInfo;			// アイテムの情報
	SMacchinaInfo m_MacchinaInfo;	// マキナ草の情報
	SEnemyInfo m_EnemyInfo;			// 敵の情報
	STableInfo m_TableInfo;			// 台の情報
	SAirplaneInfo m_AirplaneInfo;	// 飛行機の情報

	// 静的メンバ変数
	static const char* c_apBooleanDisp[2];			// bool型の表示
};

#endif