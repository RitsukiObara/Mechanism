//===================================
//
// イトキャンヘッダー[itocan.h]
// Author 小原立暉
//
//===================================
#ifndef _ITOCAN_H_
#define _ITOCAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "enemy.h"

//-----------------------------------
// クラス定義(イトキャン)
//-----------------------------------
class CItocan : public CEnemy
{
public:			// 誰でもアクセスできる

	CItocan();					// コンストラクタ
	~CItocan();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void Hit(void);			// ヒット処理
	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void CheckPlayer(void);			// プレイヤーの判定処理
};

#endif