////======================================================================================================================
////
////	メッシュモデル処理 [mesh_model.cpp]
////	Author：小原立暉
////
////======================================================================================================================
////**********************************************************************************************************************
////	インクルードファイル
////**********************************************************************************************************************
//#include "manager.h"
//#include "mesh_model.h"
//#include "texture.h"
//#include "renderer.h"
//
////================================
//// コンストラクタ
////================================
//CMeshModel::CMeshModel() : CObject(CObject::TYPE_MESH, CObject::PRIORITY_BG)
//{
//	// 全ての値をクリアする
//	m_nNumVtx = 0;			// 総頂点数
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
//	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));	// ワールドマトリックス
//	m_pVtxBuff = nullptr;							// 頂点バッファのポインタ
//	m_nTexIdx = NONE_TEXIDX;						// テクスチャのインデックス
//	m_bLightOff = false;							// ライティング状況
//}
//
////================================
//// デストラクタ
////================================
//CMeshModel::~CMeshModel()
//{
//
//}
//
////================================
//// 初期化処理
////================================
//HRESULT CMeshModel::Init(void)
//{
//	// ポインタを宣言
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスへのポインタ
//
//	// 頂点バッファの生成
//	if (FAILED(pDevice->CreateVertexBuffer
//	( // 引数
//		sizeof(VERTEX_3D) * m_nNumVtx,	// 必要頂点数
//		D3DUSAGE_WRITEONLY,				// 使用方法
//		FVF_VERTEX_3D,					// 頂点フォーマット
//		D3DPOOL_MANAGED,				// メモリの指定
//		&m_pVtxBuff,					// 頂点バッファへのポインタ
//		NULL
//	)))
//	{ // 頂点の生成に失敗した場合
//
//		// 失敗を返す
//		return E_FAIL;
//	}
//
//	// 成功を返す
//	return S_OK;
//}
//
////================================
//// 終了処理
////================================
//void CMeshModel::Uninit(void)
//{
//	if (m_pVtxBuff != nullptr)
//	{ // 頂点バッファの破棄
//
//		m_pVtxBuff->Release();
//		m_pVtxBuff = nullptr;
//	}
//
//	// 破棄処理
//	Release();
//}
//
////================================
//// 更新処理
////================================
//void CMeshModel::Update(void)
//{
//
//}
//
////================================
//// 描画処理
////================================
//void CMeshModel::Draw(void)
//{
//	// デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;			// 計算用マトリックス
//	D3DXMATRIX mtxView;						// ビューマトリックス取得用
//
//	// カリングの設定
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//	// 頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ワールドマトリックスの初期化
//	D3DXMatrixIdentity(&m_mtxWorld);
//
//	// 向きを反映
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	// 位置を反映
//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	// ワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	// 頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0,
//		m_pVtxBuff,									// 頂点バッファへのポインタ
//		0,
//		sizeof(VERTEX_3D));							// 頂点情報構造体のサイズ
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nTexIdx));
//
//	// ポリゴンの描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// プリミティブの種類
//		0,											// 描画する最初の頂点インデックス
//		m_nNumVtx - 2);								// 描画するプリミティブ数
//
//	// カリングの設定
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//}
//
////================================
//// 情報の設定処理
////================================
//void CMeshModel::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, CXFile::TYPE type)
//{
//	// ローカル変数宣言
//	CXFile::SXFile file = CXFile::GetXFile(type);		// ファイルの情報を取得する
//
//	// モデルの頂点数を取得
//	m_nNumVtx = file.pMesh->GetNumVertices();
//
//	// 位置を設定する
//	m_pos = pos;
//
//	// 向きを設定する
//	m_rot = rot;
//}
//
////================================
//// テクスチャの割り当て処理
////================================
//void CMeshModel::BindTexture(int nIdx)
//{
//	// テクスチャを割り当てる
//	m_nTexIdx = nIdx;
//}
//
////================================
//// 生成処理
////================================
//CMeshModel* CMeshModel::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, CXFile::TYPE type)
//{
//	// ローカルオブジェクトを生成
//	CMeshModel* pMesh = nullptr;	// オブジェクト3Dのインスタンスを生成
//
//	if (pMesh == nullptr)
//	{ // オブジェクトが NULL の場合
//
//		// オブジェクトを生成
//		pMesh = new CMeshModel;
//	}
//	else
//	{ // オブジェクトが NULL じゃない場合
//
//		// NULL を返す
//		return nullptr;
//	}
//
//	if (pMesh != nullptr)
//	{ // オブジェクトが NULL じゃない場合
//
//		// 情報の設定処理
//		pMesh->SetData(pos, rot, type);
//
//		// 初期化処理
//		if (FAILED(pMesh->Init()))
//		{ // 初期化処理に失敗した場合
//
//			// NULL を返す
//			return nullptr;
//		}
//
//		// メッシュの設定処理
//		pMesh->SetMesh(type);
//
//		// テクスチャの割り当て処理
//		pMesh->BindTexture(CManager::GetTexture()->Regist(nullptr));
//	}
//	else
//	{ // オブジェクトが NULL の場合
//
//		// NULL を返す
//		return nullptr;
//	}
//
//	// オブジェクト3Dのポインタを返す
//	return pMesh;
//}
//
////================================
//// メッシュの設定処理
////================================
//void CMeshModel::SetMesh(const CXFile::TYPE type)
//{
//	// 変数を宣言
//	CXFile::SXFile file = CXFile::GetXFile(type);		// ファイルの情報を取得する
//	DWORD       dwSizeFVF;								// モデルの頂点フォーマットのサイズ
//	BYTE        *pVtxBuff;								// モデルの頂点バッファへのポインタ
//	D3DXVECTOR3 vtx;									// モデルの頂点座標
//	VERTEX_3D *pVtx;							// 頂点情報へのポインタ
//
//	// 頂点バッファをロックし、頂点情報へのポインタを取得
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	// モデルの頂点数を取得
//	m_nNumVtx = file.pMesh->GetNumVertices();
//
//	// モデルの頂点フォーマットのサイズを取得
//	dwSizeFVF = D3DXGetFVFVertexSize(file.pMesh->GetFVF());
//
//	// モデルの頂点バッファをロック
//	file.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
//	{ // モデルの頂点数分繰り返す
//
//		// モデルの頂点座標を代入
//		vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//		// 頂点座標の設定
//		pVtx[0].pos = vtx;
//
//		// 法線ベクトルの設定
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		// 頂点カラーの設定
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// テクスチャ座標の設定
//		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx++;				// 頂点データを進める
//
//		// 頂点フォーマットのサイズ分ポインタを進める
//		pVtxBuff += dwSizeFVF;
//	}
//
//	// モデルの頂点バッファをアンロック
//	file.pMesh->UnlockVertexBuffer();
//
//	// 頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//}