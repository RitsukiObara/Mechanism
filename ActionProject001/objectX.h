//============================================================
//
// Xファイルヘッダー [xfile.h]
// Author：小原立暉
//
//============================================================
#ifndef _XFILE_H_	// このマクロ定義がされていない場合
#define _XFILE_H_	// 二重インクルード防止のマクロを定義する

//------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// モデルの最小の頂点座標の初期値
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// モデルの最大の頂点座標の初期値
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// モデルサイズの初期値
#define INIT_PLAYER		(CXFile::TYPE_PLAYERPANTS)						// プレイヤーの最初の数字

//------------------------------------------------------------
// クラス定義(Xファイル)
//------------------------------------------------------------
class CXFile
{
public:			// 誰でもアクセスできる

	//************************************************************
	//	列挙型定義 (TYPE)
	//************************************************************
	enum TYPE
	{
		// 通常モデル
		TYPE_AIRPLANE = 0,		// 飛行機
		TYPE_SCREW,				// ネジ

		// 敵モデル
		TYPE_ITOCAN,			// イトキャン

		// プレイヤーモデル
		TYPE_PLAYERPANTS,		// 腰
		TYPE_PLAYERBODY,		// 体
		TYPE_PLAYERNECK,		// 首
		TYPE_PLAYERHEAD,		// 頭
		TYPE_PLAYERLEFTUPPER,	// 左上腕
		TYPE_PLAYERRIGHTUPPER,	// 右上腕
		TYPE_PLAYERLEFTARM,		// 左腕
		TYPE_PLAYERRIGHTARM,	// 右腕
		TYPE_PLAYERLEFTLEG,		// 左脚
		TYPE_PLAYERRIGHTLEG,	// 右脚
		TYPE_PLAYERLEFTSHIN,	// 左脛
		TYPE_PLAYERRIGHTSHIN,	// 右脛
		TYPE_PLAYERLEFTFOOT,	// 左足
		TYPE_PLAYERRIGHTFOOT,	// 右足

		// エディットモデル
		TYPE_MAX,				// 全モデルの総数
	};

	//************************************************************
	//	構造体定義 (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// メッシュ (頂点情報) へのポインタ
		LPD3DXBUFFER pBuffMat;					// マテリアルへのポインタ
		DWORD		 dwNumMat;					// マテリアルの数
		D3DXVECTOR3	 vtxMin;					// 最小の頂点座標
		D3DXVECTOR3	 vtxMax;					// 最大の頂点座標
		D3DXVECTOR3	 collsize;					// 当たり判定のサイズ
		float		 fRadius;					// 半径
		int			 m_nTexIdx[MAX_MATERIAL];	// テクスチャのインデックス
	};

	CXFile();			// コンストラクタ
	~CXFile();			// デストラクタ

	// メンバ関数
	static HRESULT Init(void);		// Xファイルの初期化処理
	static void Uninit(void);		// Xファイルの終了処理

	// セット・ゲット関数
	static SXFile GetXFile(TYPE type);	// Xファイルの取得処理

private:

	// メンバ関数
	static HRESULT LoadXFile(void);		// xファイルの読み込み
	static void SetCollision(void);		// 当たり判定の作成
	static HRESULT LoadTexture(void);	// テクスチャの読み込み

	// 静的メンバ変数
	static const char *c_apModelData[CXFile::TYPE_MAX];			// モデルの名前
	static SXFile m_apModel[CXFile::TYPE_MAX];					// モデルの情報
};

#endif