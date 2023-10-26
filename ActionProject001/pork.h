//===================================
//
// ポークヘッダー[pork.h]
// Author 小原立暉
//
//===================================
#ifndef _PORK_H_
#define _PORK_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CSignBoard;		// 看板

//-----------------------------------
// クラス定義(ポーク)
//-----------------------------------
class CPork : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_HOVER = 0,		// ホバー
		TYPE_DASH,			// ダッシュ
		TYPE_QUAKE,			// グラウンドクエイク
		TYPE_MAX			// この列挙型の総数
	};

	CPork();				// コンストラクタ
	~CPork();				// デストラクタ

	// リスト構造関係
	void SetPrev(CPork* pPrev);	// 前のポインタの設定処理
	void SetNext(CPork* pNext);	// 後のポインタの設定処理
	CPork* GetPrev(void) const;	// 前のポインタの設定処理
	CPork* GetNext(void) const;	// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	// 静的メンバ関数
	static CPork* Create(const D3DXVECTOR3& pos, const TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CSignBoard* m_pSignBoard;		// 看板のポインタ

	// リスト構造関係
	CPork* m_pPrev;	// 前へのポインタ
	CPork* m_pNext;	// 次へのポインタ
};

#endif