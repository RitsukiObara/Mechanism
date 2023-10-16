//============================================
//
// プレイヤーの能力ヘッダー[player_ability.h]
// Author：小原立暉
//
//============================================
#ifndef _PLAYER_ABILITY_H_					// このマクロ定義がされていなかったら
#define _PLAYER_ABILITY_H_					// 2重インクルード防止のマクロを定義する

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CPlayer;			// プレイヤー

//--------------------------------------------
// クラス(プレイヤーの能力クラス)
//--------------------------------------------
class CAbility
{
public:			// 誰でもアクセスできる

	// 列挙型定義(能力)
	enum ABILITY
	{
		ABILITY_NONE = 0,		// 無状態
		ABILITY_HOVER,			// ホバージェット
		ABILITY_JETDASH,		// ジェットダッシュ
		ABILITY_MAX				// この列挙型の総数
	};

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_HOVER = 0,			// ホバージェット
		TYPE_JETDASH,			// ジェットダッシュ
		TYPE_GROUNDQUAKE,		// グラウンドクエイク
		TYPE_STARDROP,			// スタードロップ
		TYPE_MAX				// この列挙型の総数
	};

	CAbility();				// コンストラクタ
	~CAbility();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(CPlayer& player);		// 更新処理

	void SetData(void);		// 情報の設定処理

	// セット・ゲット関数
	void SetAbility(const ABILITY ability);		// 能力の設定処理
	ABILITY GetAbility(void) const;				// 能力の取得処理
	void SetPossible(const TYPE type, const bool bPossible);		// 可能状況の設定処理
	bool GetPossible(const TYPE type);								// 可能状況の取得処理
	void SetInterval(const TYPE type, const int nCount);			// 間隔カウントの設定処理
	int GetInterval(const TYPE type) const;							// 間隔カウントの取得処理

	// 静的メンバ関数
	static CAbility* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void HoverJet(CPlayer& player);		// ホバージェット処理
	void SkyDash(CPlayer& player);		// ジェットダッシュ処理

	void Interval(void);				// 間隔カウント処理

	// メンバ変数
	ABILITY m_ability;					// 能力
	int m_nAblCount;					// 能力カウント
	int m_aIntervalCount[TYPE_MAX];		// 間隔カウント
	bool m_aPossible[TYPE_MAX];			// 能力の使用状況
};

#endif