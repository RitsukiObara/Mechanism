////=====================================================
////
//// メッシュモデルヘッダー [mesh_model.h]
//// Author：小原立暉
////
////=====================================================
//#ifndef _MESH_MODEL_H_			// このマクロ定義がされていない場合
//#define _MESH_MODEL_H_			// 二重インクルード防止のマクロを定義する
//
////*****************************************************
//// インクルードファイル
////*****************************************************
//#include "object.h"
//#include "objectX.h"
//
////-----------------------------------------------------
//// クラス定義(メッシュモデル)
////-----------------------------------------------------
//class CMeshModel : public CObject
//{
//public:		// 誰でもアクセスできる
//
//	CMeshModel();			// コンストラクタ
//	~CMeshModel();	// デストラクタ
//
//	// メンバ関数
//	HRESULT Init(void);		// 初期化処理
//	void Uninit(void);		// 終了処理
//	void Update(void);		// 更新処理
//	void Draw(void);		// 描画処理
//
//	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const CXFile::TYPE type);		// 情報の設定処理
//
//	void BindTexture(int nIdx);		// テクスチャの割り当て処理
//
//	// 静的メンバ関数
//	static CMeshModel* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const CXFile::TYPE type);		// 生成処理
//
//private:		// 自分だけアクセスできる
//
//	// メンバ関数
//	void SetMesh(const CXFile::TYPE type);		// メッシュの設定処理
//
//	// メンバ変数
//	D3DXVECTOR3 m_pos;		// 位置
//	D3DXVECTOR3 m_rot;		// 向き
//	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
//	int m_nTexIdx;			// テクスチャのインデックス
//	int m_nNumVtx;			// 総頂点数
//	bool m_bLightOff;		// ライティング状況
//};
//
//
//#endif