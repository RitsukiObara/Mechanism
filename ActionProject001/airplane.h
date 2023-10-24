//===================================
//
// 飛行船ヘッダー[airplane.h]
// Author 小原立暉
//
//===================================
#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(飛行船)
//-----------------------------------
class CAirplane : public CModel
{
public:			// 誰でもアクセスできる

	CAirplane();					// コンストラクタ
	~CAirplane();					// デストラクタ

	// リスト構造関係
	void SetPrev(CAirplane* pPrev);	// 前のポインタの設定処理
	void SetNext(CAirplane* pNext);	// 後のポインタの設定処理
	CAirplane* GetPrev(void) const;	// 前のポインタの設定処理
	CAirplane* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const bool bFront);				// 情報の設定処理

	// セット・ゲット関係
	bool GetFront(void) const;		// 前後状況の取得処理

	// 静的メンバ関数
	static CAirplane* Create(const D3DXVECTOR3& pos, const bool bFront);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	bool m_bFront;		// 前後状況

	// リスト構造関係
	CAirplane* m_pPrev;	// 前へのポインタ
	CAirplane* m_pNext;	// 次へのポインタ
};

#endif