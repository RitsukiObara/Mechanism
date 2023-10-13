//=====================================================
//
// メッシュフィールドヘッダー [mesh_field.h]
// Author：小原立暉
//
//=====================================================
#ifndef _MESH_FIELD_H_			// このマクロ定義がされていない場合
#define _MESH_FIELD_H_			// 二重インクルード防止のマクロを定義する

//*****************************************************
// インクルードファイル
//*****************************************************
#include "Objectmesh.h"

//-----------------------------------------------------
// クラス定義(メッシュ)
//-----------------------------------------------------
class CMeshField : public CMesh
{
public:		// 誰でもアクセスできる

	CMeshField();			// コンストラクタ
	~CMeshField();	// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

private:		// 自分だけアクセスできる

};


#endif