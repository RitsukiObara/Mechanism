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

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STOP = 0,			// 停止状態
		STATE_MOVE,				// 移動状態
		STATE_MAX				// この列挙型の総数
	};

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
	void CheckState(void);			// 状態の判定処理
	void Move(void);				// 移動処理

	// メンバ変数
	STATE m_state;					// 状態
	int m_nStateCount;				// 状態カウント
};

#endif