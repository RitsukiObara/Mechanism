//===================================
//
// ブロックヘッダー[block.h]
// Author 小原立暉
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(ブロック)
//-----------------------------------
class CBlock : public CModel
{
public:			// 誰でもアクセスできる

	CBlock();				// コンストラクタ
	~CBlock();				// デストラクタ

	// リスト構造関係
	void SetPrev(CBlock* pPrev);	// 前のポインタの設定処理
	void SetNext(CBlock* pNext);	// 後のポインタの設定処理
	CBlock* GetPrev(void) const;	// 前のポインタの設定処理
	CBlock* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);				// 情報の設定処理

	// 静的メンバ関数
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale);	// 生成処理

private:		// 自分だけアクセスできる

	// リスト構造関係
	CBlock* m_pPrev;	// 前へのポインタ
	CBlock* m_pNext;	// 次へのポインタ
};

#endif