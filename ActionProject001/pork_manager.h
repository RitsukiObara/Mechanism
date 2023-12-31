//============================================
//
// ポークマネージャーヘッダー[pork_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _PORK_MANAGER_H_		// このマクロ定義がされていなかったら
#define _PORK_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CPork;		// ポーク

//--------------------------------------------
// クラス(ポークマネージャークラス)
//--------------------------------------------
class CPorkManager
{
public:				// 誰でもアクセスできる

	CPorkManager();			// コンストラクタ
	~CPorkManager();			// デストラクタ

	// メンバ関数
	void Regist(CPork* pThis);		// 登録処理
	void Uninit(void);						// 終了処理
	
	CPork* GetTop(void);				// 先頭の取得処理
	void Pull(CPork* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CPorkManager* Create(void);		// 生成処理
	static CPorkManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CPork* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CPorkManager* m_pManager;		// マネージャーの変数
};

#endif