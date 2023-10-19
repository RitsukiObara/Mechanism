//============================================
//
// 能力のUIヘッダー[ability_UI.h]
// Author：小原立暉
//
//============================================
#ifndef _ABILITY_UI_H_					// このマクロ定義がされていなかったら
#define _ABILITY_UI_H_					// 2重インクルード防止のマクロを定義する
//********************************************
// インクルードファイル
//********************************************
#include "object.h"
#include "player_ability.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CBillboard;			// ビルボード

//--------------------------------------------
// クラス定義(能力UI)
//--------------------------------------------
class CAbilityUI : public CObject
{
public:				// 誰でもアクセスできる

	CAbilityUI();			// コンストラクタ
	~CAbilityUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3 pos);					// 情報の設定処理

	// 静的メンバ変数
	static CAbilityUI* Create(const D3DXVECTOR3 pos);		// 生成処理

private:			// 自分だけアクセスできる

	// メンバ関数
	void PossibleColor(void);	// 使用状況の設定処理
	void PosChase(void);		// 位置追尾処理

	// メンバ変数
	CBillboard* m_apAbilityUI[TYPE_MAX];	// 能力の情報

	// 静的メンバ変数
	static const char* m_acTextureFileName[CAbility::TYPE_MAX];		// テクスチャの名前
};

#endif