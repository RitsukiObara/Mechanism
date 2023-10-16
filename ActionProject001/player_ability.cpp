//============================================
//
// プレイヤーの能力のメイン処理[player_ability.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "player.h"
#include "motion.h"
#include "player_ability.h"
#include "useful.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define HOVER_COUNT		(100)				// ホバー状態のカウント
#define JETDASH_COUNT	(20)				// ジェットダッシュ状態のカウント
#define JETDASH_SPEED	(30.0f)				// ジェットダッシュ時のスピード

//============================================
// コンストラクタ
//============================================
CAbility::CAbility()
{
	// 全ての値をクリアする
	m_ability = ABILITY_NONE;		// 能力
	m_nAblCount = 0;				// カウント

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPossible[nCnt] = true;			// 能力の使用状況
		m_aIntervalCount[nCnt] = 0;			// 間隔カウント
	}
}

//============================================
// デストラクタ
//============================================
CAbility::~CAbility()
{

}

//============================================
// 初期化処理
//============================================
HRESULT CAbility::Init(void)
{
	// 全ての値を初期化する
	m_ability = ABILITY_NONE;		// 能力
	m_nAblCount = 0;				// カウント

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPossible[nCnt] = true;			// 能力の使用状況
		m_aIntervalCount[nCnt] = 0;			// 間隔カウント
	}

	// 成功を返す
	return S_OK;
}

//============================================
// 終了処理
//============================================
void CAbility::Uninit(void)
{
	// 自分のメモリを解放する
	delete this;
}

//============================================
// 更新処理
//============================================
void CAbility::Update(CPlayer& player)
{
	switch (m_ability)
	{
	case ABILITY_NONE:		// 無状態

		// カウントを初期化する
		m_nAblCount = 0;

		break;

	case ABILITY_HOVER:		// ホバージェット

		// ホバージェット処理
		HoverJet(player);

		break;

	case ABILITY_JETDASH:	// ジェットダッシュ

		// ジェットダッシュ処理
		SkyDash(player);

		break;
	}

	// 間隔カウント処理
	Interval();
}

//============================================
// 情報の設定処理
//============================================
void CAbility::SetData(void)
{
	// 全ての値を設定する
	m_ability = ABILITY_NONE;		// 能力
	m_nAblCount = 0;				// カウント
}

//============================================
// 能力の設定処理
//============================================
void CAbility::SetAbility(const ABILITY ability)
{
	// 能力を設定する
	m_ability = ability;

	// カウントを初期化する
	m_nAblCount = 0;
}

//============================================
// 能力の取得処理
//============================================
CAbility::ABILITY CAbility::GetAbility(void) const
{
	// 能力を返す
	return m_ability;
}

//========================
// 可能状況の設定処理
//========================
void CAbility::SetPossible(const TYPE type, const bool bPossible)
{
	// 可能状況を設定する
	m_aPossible[type] = bPossible;
}

//========================
// 可能状況の取得処理
//========================
bool CAbility::GetPossible(const TYPE type)
{
	// 可能状況を返す
	return m_aPossible[type];
}

//============================================
// 間隔カウントの設定処理
//============================================
void CAbility::SetInterval(const TYPE type, const int nCount)
{
	// 間隔カウントを設定する
	m_aIntervalCount[type] = nCount;
}

//============================================
// 間隔カウントの取得処理
//============================================
int CAbility::GetInterval(const TYPE type) const
{
	// 間隔カウントを返す
	return m_aIntervalCount[type];
}

//============================================
// 生成処理
//============================================
CAbility* CAbility::Create(void)
{
	// ローカル変数宣言
	CAbility* pAbility = nullptr;		// 行動状態

	if (pAbility == nullptr)
	{ // オブジェクトが NULL の場合

		// メモリを確保する
		pAbility = new CAbility;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// NULL を返す
		return pAbility;
	}

	if (pAbility != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pAbility->Init()))
		{ // 初期化に失敗した場合

			// 警告文
			MessageBox(NULL, "プレイヤーの能力の初期化に失敗！", "警告！", MB_ICONWARNING);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pAbility->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// NULL を返す
		return nullptr;
	}

	// 能力のポインタを返す
	return pAbility;
}

//============================================
// ホバージェット処理
//============================================
void CAbility::HoverJet(CPlayer& player)
{
	// ジャンプ状態にする
	player.SetEnableJump(true);

	// カウントを加算する
	m_nAblCount++;

	if (m_nAblCount >= HOVER_COUNT)
	{ // カウントが一定数以上の場合

		// カウントを初期化する
		m_nAblCount = 0;

		// 無能力状態にする
		m_ability = ABILITY_NONE;
	}
}

//============================================
// ジェットダッシュ処理
//============================================
void CAbility::SkyDash(CPlayer& player)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = player.GetPos();		// 位置を取得する
	D3DXVECTOR3 rot = player.GetRot();		// 向きを取得する

	// 位置を設定する
	pos.x += sinf(rot.y) * JETDASH_SPEED;

	// カウントを加算する
	m_nAblCount++;

	if (m_nAblCount >= JETDASH_COUNT)
	{ // カウントが一定数以上の場合

		// カウントを初期化する
		m_nAblCount = 0;

		// 無能力状態にする
		m_ability = ABILITY_NONE;
	}

	// 位置を適用する
	player.SetPos(pos);
}

//============================================
// 間隔カウント処理
//============================================
void CAbility::Interval(void)
{
	for (int nCnt = 0; nCnt < CAbility::TYPE_MAX; nCnt++)
	{
		if (m_aPossible[nCnt] == false)
		{ // 能力状況が false の場合

			// 間隔カウント減算する
			m_aIntervalCount[nCnt]--;

			if (m_aIntervalCount[nCnt] <= 0)
			{ // 間隔カウントが 0 以上になった場合

				// 間隔カウントを 0 にする
				m_aIntervalCount[nCnt] = 0;

				// 使用可能状況を true にする
				m_aPossible[nCnt] = true;
			}
		}
	}
}