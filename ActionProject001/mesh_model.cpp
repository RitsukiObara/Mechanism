////======================================================================================================================
////
////	���b�V�����f������ [mesh_model.cpp]
////	Author�F��������
////
////======================================================================================================================
////**********************************************************************************************************************
////	�C���N���[�h�t�@�C��
////**********************************************************************************************************************
//#include "manager.h"
//#include "mesh_model.h"
//#include "texture.h"
//#include "renderer.h"
//
////================================
//// �R���X�g���N�^
////================================
//CMeshModel::CMeshModel() : CObject(CObject::TYPE_MESH, CObject::PRIORITY_BG)
//{
//	// �S�Ă̒l���N���A����
//	m_nNumVtx = 0;			// �����_��
//	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
//	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));	// ���[���h�}�g���b�N�X
//	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�̃|�C���^
//	m_nTexIdx = NONE_TEXIDX;						// �e�N�X�`���̃C���f�b�N�X
//	m_bLightOff = false;							// ���C�e�B���O��
//}
//
////================================
//// �f�X�g���N�^
////================================
//CMeshModel::~CMeshModel()
//{
//
//}
//
////================================
//// ����������
////================================
//HRESULT CMeshModel::Init(void)
//{
//	// �|�C���^��錾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
//
//	// ���_�o�b�t�@�̐���
//	if (FAILED(pDevice->CreateVertexBuffer
//	( // ����
//		sizeof(VERTEX_3D) * m_nNumVtx,	// �K�v���_��
//		D3DUSAGE_WRITEONLY,				// �g�p���@
//		FVF_VERTEX_3D,					// ���_�t�H�[�}�b�g
//		D3DPOOL_MANAGED,				// �������̎w��
//		&m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
//		NULL
//	)))
//	{ // ���_�̐����Ɏ��s�����ꍇ
//
//		// ���s��Ԃ�
//		return E_FAIL;
//	}
//
//	// ������Ԃ�
//	return S_OK;
//}
//
////================================
//// �I������
////================================
//void CMeshModel::Uninit(void)
//{
//	if (m_pVtxBuff != nullptr)
//	{ // ���_�o�b�t�@�̔j��
//
//		m_pVtxBuff->Release();
//		m_pVtxBuff = nullptr;
//	}
//
//	// �j������
//	Release();
//}
//
////================================
//// �X�V����
////================================
//void CMeshModel::Update(void)
//{
//
//}
//
////================================
//// �`�揈��
////================================
//void CMeshModel::Draw(void)
//{
//	// �f�o�C�X�̎擾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
//	D3DXMATRIX mtxView;						// �r���[�}�g���b�N�X�擾�p
//
//	// �J�����O�̐ݒ�
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//
//	// ���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_3D);
//
//	// ���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtxWorld);
//
//	// �����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	// �ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	// ���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0,
//		m_pVtxBuff,									// ���_�o�b�t�@�ւ̃|�C���^
//		0,
//		sizeof(VERTEX_3D));							// ���_���\���̂̃T�C�Y
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nTexIdx));
//
//	// �|���S���̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
//		0,											// �`�悷��ŏ��̒��_�C���f�b�N�X
//		m_nNumVtx - 2);								// �`�悷��v���~�e�B�u��
//
//	// �J�����O�̐ݒ�
//	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
//}
//
////================================
//// ���̐ݒ菈��
////================================
//void CMeshModel::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, CXFile::TYPE type)
//{
//	// ���[�J���ϐ��錾
//	CXFile::SXFile file = CXFile::GetXFile(type);		// �t�@�C���̏����擾����
//
//	// ���f���̒��_�����擾
//	m_nNumVtx = file.pMesh->GetNumVertices();
//
//	// �ʒu��ݒ肷��
//	m_pos = pos;
//
//	// ������ݒ肷��
//	m_rot = rot;
//}
//
////================================
//// �e�N�X�`���̊��蓖�ď���
////================================
//void CMeshModel::BindTexture(int nIdx)
//{
//	// �e�N�X�`�������蓖�Ă�
//	m_nTexIdx = nIdx;
//}
//
////================================
//// ��������
////================================
//CMeshModel* CMeshModel::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, CXFile::TYPE type)
//{
//	// ���[�J���I�u�W�F�N�g�𐶐�
//	CMeshModel* pMesh = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�
//
//	if (pMesh == nullptr)
//	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
//
//		// �I�u�W�F�N�g�𐶐�
//		pMesh = new CMeshModel;
//	}
//	else
//	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
//
//		// NULL ��Ԃ�
//		return nullptr;
//	}
//
//	if (pMesh != nullptr)
//	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
//
//		// ���̐ݒ菈��
//		pMesh->SetData(pos, rot, type);
//
//		// ����������
//		if (FAILED(pMesh->Init()))
//		{ // �����������Ɏ��s�����ꍇ
//
//			// NULL ��Ԃ�
//			return nullptr;
//		}
//
//		// ���b�V���̐ݒ菈��
//		pMesh->SetMesh(type);
//
//		// �e�N�X�`���̊��蓖�ď���
//		pMesh->BindTexture(CManager::GetTexture()->Regist(nullptr));
//	}
//	else
//	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
//
//		// NULL ��Ԃ�
//		return nullptr;
//	}
//
//	// �I�u�W�F�N�g3D�̃|�C���^��Ԃ�
//	return pMesh;
//}
//
////================================
//// ���b�V���̐ݒ菈��
////================================
//void CMeshModel::SetMesh(const CXFile::TYPE type)
//{
//	// �ϐ���錾
//	CXFile::SXFile file = CXFile::GetXFile(type);		// �t�@�C���̏����擾����
//	DWORD       dwSizeFVF;								// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y
//	BYTE        *pVtxBuff;								// ���f���̒��_�o�b�t�@�ւ̃|�C���^
//	D3DXVECTOR3 vtx;									// ���f���̒��_���W
//	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^
//
//	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	// ���f���̒��_�����擾
//	m_nNumVtx = file.pMesh->GetNumVertices();
//
//	// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y���擾
//	dwSizeFVF = D3DXGetFVFVertexSize(file.pMesh->GetFVF());
//
//	// ���f���̒��_�o�b�t�@�����b�N
//	file.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
//	{ // ���f���̒��_�����J��Ԃ�
//
//		// ���f���̒��_���W����
//		vtx = *(D3DXVECTOR3*)pVtxBuff;
//
//		// ���_���W�̐ݒ�
//		pVtx[0].pos = vtx;
//
//		// �@���x�N�g���̐ݒ�
//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//
//		// ���_�J���[�̐ݒ�
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// �e�N�X�`�����W�̐ݒ�
//		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx++;				// ���_�f�[�^��i�߂�
//
//		// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
//		pVtxBuff += dwSizeFVF;
//	}
//
//	// ���f���̒��_�o�b�t�@���A�����b�N
//	file.pMesh->UnlockVertexBuffer();
//
//	// ���_�o�b�t�@���A�����b�N����
//	m_pVtxBuff->Unlock();
//}