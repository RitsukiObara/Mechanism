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
class CObject2D;				// 2Dポリゴン

//--------------------------------------------
// クラス定義(能力UI)
//--------------------------------------------
class CAbilityUI : public CObject
{
public:				// 誰でもアクセスできる

	// 列挙型定義(ポリゴン)
	enum GAGE
	{
		GAGE_BIG_GROUND = 0,	// 大技の下地
		GAGE_BIG_METER,			// 大技のメーター
		GAGE_SMALL_GROUND,		// 小技の下地
		GAGE_SMALL_METER,		// 小技のメーター
		GAGE_MAX				// この列挙型の総数
	};

	// 構造体定義(テクスチャ関係の情報)
	struct STexInfo
	{
		int m_nTexIdx;			// テクスチャの番号
		float m_fTexSizeY;		// テクスチャの縦サイズ
	};

	CAbilityUI();			// コンストラクタ
	~CAbilityUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理
	void DrawAcrobat(void);	// アクロバットの描画処理
	void DrawMassive(void);	// マッシブの描画処理

	void SetData(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);				// 情報の設定処理
	void SetDataAcrobat(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);		// アクロバットの設定処理
	void SetDataMassive(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);		// マッシブの設定処理

	// 静的メンバ変数
	static CAbilityUI* Create(const D3DXVECTOR3& posBig, const D3DXVECTOR3& posSmall);	// 生成処理

private:			// 自分だけアクセスできる

	// メンバ関数
	HRESULT AcrobatCreate(void);		// アクロバットの生成処理
	HRESULT MassiveCreate(void);		// マッシブの生成処理
	void Size(const CAbility::TYPE type, CObject2D& pData, const int nInterval, float fSizeMove);		// サイズ設定処理

	// メンバ変数
	CObject2D* m_apAcrobat[GAGE_MAX];			// アクロバットの情報
	CObject2D* m_apMassive[GAGE_MAX];			// マッシブの情報
	STexInfo m_aTexInfo[CAbility::TYPE_MAX];	// テクスチャの情報

	// 静的メンバ変数
	static const char* m_acTextureFileName[CAbility::TYPE_MAX];		// テクスチャの名前
};

#endif