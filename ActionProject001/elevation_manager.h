//============================================
//
// 起伏マネージャーヘッダー[out_ball_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _ELEVATION_MANAGER_H_		// このマクロ定義がされていなかったら
#define _ELEVATION_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMeshElevation;		// 起伏

//--------------------------------------------
// クラス(起伏マネージャークラス)
//--------------------------------------------
class CElevationManager
{
public:				// 誰でもアクセスできる

	CElevationManager();			// コンストラクタ
	~CElevationManager();			// デストラクタ

	// メンバ関数
	void Regist(CMeshElevation* pThis);		// 登録処理
	void Uninit(void);						// 終了処理
	
	CMeshElevation* GetTop(void);				// 先頭の取得処理
	void Pull(CMeshElevation* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CElevationManager* Create(void);		// 生成処理
	static CElevationManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CMeshElevation* m_pTop;		// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CElevationManager* m_pManager;		// マネージャーの変数
};

#endif