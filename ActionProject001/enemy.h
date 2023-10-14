//===================================
//
// 敵ヘッダー[enemy.h]
// Author 小原立暉
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(敵)
//-----------------------------------
class CEnemy : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_ITOCAN = 0,		// イトキャン
		TYPE_MAX				// この列挙型の総数
	};

	CEnemy();							// コンストラクタ
	CEnemy(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// オーバーロードコンストラクタ
	virtual ~CEnemy();					// デストラクタ
	void Box(void);						// コンストラクタの箱

	// リスト構造関係
	void SetPrev(CEnemy* pPrev);	// 前のポインタの設定処理
	void SetNext(CEnemy* pNext);	// 後のポインタの設定処理
	CEnemy* GetPrev(void) const;	// 前のポインタの設定処理
	CEnemy* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void) = 0;	// 更新処理
	virtual void Draw(void);		// 描画処理

	virtual void Hit(void);			// ヒット処理
	virtual void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理

	void SetEnableStep(const bool bStep);		// 踏みつけ状況の設定処理
	bool IsStep(void) const;					// 踏みつけ状況の取得処理

	D3DXVECTOR3 GetInitPos(void) const;			// 初期位置の取得処理

	// その他の関数
	void Gravity(void);				// 重力処理
	bool ElevationCollision(void);	// 起伏地面の当たり判定処理

	// 静的メンバ関数
	static CEnemy* Create(const D3DXVECTOR3& pos, const TYPE type);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	D3DXVECTOR3 m_posInit;	// 初期位置
	D3DXVECTOR3 m_move;		// 移動量
	bool m_bStep;			// 踏みつけ状況

	// リスト構造関係
	CEnemy* m_pPrev;	// 前へのポインタ
	CEnemy* m_pNext;	// 次へのポインタ
};

#endif