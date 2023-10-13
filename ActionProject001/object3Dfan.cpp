//============================================
//
// �I�u�W�F�N�g3D�t�@���̃��C������[object3Dfan.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object3Dfan.h"
#include "renderer.h"
#include "manager.h"
#include "useful.h"

//=========================================
// �R���X�g���N�^
//=========================================
CObject3DFan::CObject3DFan() : CObject(CObject::TYPE_3DPOLYGON, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�̃|�C���^
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));	// ���[���h�}�g���b�N�X
	m_nNumAngle = 0;								// �p�x�̐�
	m_fRadius = 0.0f;								// ���a
}

//=========================================
// �f�X�g���N�^
//=========================================
CObject3DFan::~CObject3DFan()
{

}

//===========================================
// �I�u�W�F�N�g3D�̏���������
//===========================================
HRESULT CObject3DFan::Init(void)
{
	// �S�Ă̒l������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_nNumAngle = 1024;								// �p�x�̐�
	m_fRadius = 100.0f;								// ���a

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumAngle * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{ // �o�b�t�@�̐����Ɏ��s�����ꍇ

		// �x����
		MessageBox(NULL, "�I�u�W�F�N�g3D�t�@���̒��_�o�b�t�@�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	float fAngle = D3DX_PI / m_nNumAngle;									// �p�x

	VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (m_pVtxBuff == nullptr)
	{ // ���_�o�b�t�@�̃|�C���^��NULL�̏ꍇ

		// �x����
		MessageBox(NULL, "�I�u�W�F�N�g3D�t�@���̒��_�o�b�t�@�̃|�C���^��NULL�I", "�x���I", MB_ICONWARNING);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �I�u�W�F�N�g3D�̏I������
//===========================================
void CObject3DFan::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{ // ���_�o�b�t�@�̔j��

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �j������
	Release();
}

//===========================================
// �I�u�W�F�N�g3D�̍X�V����
//===========================================
void CObject3DFan::Update(void)
{
	// ���_�̐ݒ菈��
	SetVertex();
}

//===========================================
// �I�u�W�F�N�g3D�̕`�揈��
//===========================================
void CObject3DFan::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;						// �r���[�}�g���b�N�X�擾�p

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,									// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_3D));							// ���_���\���̂̃T�C�Y

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST,		// �v���~�e�B�u�̎��
		0,											// �`�悷��ŏ��̒��_�C���f�b�N�X
		m_nNumAngle);								// �`�悷��v���~�e�B�u��

	// ���C�e�B���O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================================
// ���_���̐ݒ�
//===========================================
void CObject3DFan::SetVertex(void)
{
	float fAngle;									// �p�x

	VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�J���[�̐ݒ菈��
//===========================================
void CObject3DFan::SetVtxColor(const D3DXCOLOR& col)
{
		VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ��������
//===========================================
CObject3DFan* CObject3DFan::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObject3DFan* pObject3DFan = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�

	if (pObject3DFan == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pObject3DFan = new CObject3DFan;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pObject3DFan != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		pObject3DFan->Init();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g3D�̃|�C���^��Ԃ�
	return pObject3DFan;
}