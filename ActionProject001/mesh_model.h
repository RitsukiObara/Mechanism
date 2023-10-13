////=====================================================
////
//// ���b�V�����f���w�b�_�[ [mesh_model.h]
//// Author�F��������
////
////=====================================================
//#ifndef _MESH_MODEL_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
//#define _MESH_MODEL_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����
//
////*****************************************************
//// �C���N���[�h�t�@�C��
////*****************************************************
//#include "object.h"
//#include "objectX.h"
//
////-----------------------------------------------------
//// �N���X��`(���b�V�����f��)
////-----------------------------------------------------
//class CMeshModel : public CObject
//{
//public:		// �N�ł��A�N�Z�X�ł���
//
//	CMeshModel();			// �R���X�g���N�^
//	~CMeshModel();	// �f�X�g���N�^
//
//	// �����o�֐�
//	HRESULT Init(void);		// ����������
//	void Uninit(void);		// �I������
//	void Update(void);		// �X�V����
//	void Draw(void);		// �`�揈��
//
//	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const CXFile::TYPE type);		// ���̐ݒ菈��
//
//	void BindTexture(int nIdx);		// �e�N�X�`���̊��蓖�ď���
//
//	// �ÓI�����o�֐�
//	static CMeshModel* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const CXFile::TYPE type);		// ��������
//
//private:		// ���������A�N�Z�X�ł���
//
//	// �����o�֐�
//	void SetMesh(const CXFile::TYPE type);		// ���b�V���̐ݒ菈��
//
//	// �����o�ϐ�
//	D3DXVECTOR3 m_pos;		// �ʒu
//	D3DXVECTOR3 m_rot;		// ����
//	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
//	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
//	int m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X
//	int m_nNumVtx;			// �����_��
//	bool m_bLightOff;		// ���C�e�B���O��
//};
//
//
//#endif