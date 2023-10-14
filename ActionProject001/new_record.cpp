//============================================
//
// �V�L�^����[new_record.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "new_record.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define NEW_RECORD_POS_X			(300.0f)								// �V�L�^�̈ʒu(X��)
#define NEW_RECORD_SIZE				(D3DXVECTOR3(160.0f, 60.0f, 0.0f))		// �V�L�^�̃T�C�Y
#define NEW_RECORD_TEXTURE			"data/TEXTURE/NewRecord.png"			// �V�L�^�̃e�N�X�`��

//========================
// �R���X�g���N�^
//========================
CNewRecord::CNewRecord() : CObject2D(CObject::TYPE_NEWRECORD, CObject::PRIORITY_UI)
{

}

//========================
// �f�X�g���N�^
//========================
CNewRecord::~CNewRecord()
{

}

//========================
// ����������
//========================
HRESULT CNewRecord::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CNewRecord::Uninit(void)
{
	// �j������
	CObject2D::Uninit();
}

//========================
// �X�V����
//========================
void CNewRecord::Update(void)
{

}

//========================
// �`�揈��
//========================
void CNewRecord::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//========================
// ���̐ݒ菈��
//========================
void CNewRecord::SetData(const D3DXVECTOR3 pos)
{
	// ���̐ݒ�
	SetPos(D3DXVECTOR3(NEW_RECORD_POS_X,pos.y,0.0f));					// �ʒu
	SetPosOld(GetPos());					// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
	SetSize(NEW_RECORD_SIZE);				// �T�C�Y
	SetAngle();								// ����
	SetLength();							// ����

	SetVertex();							// ���_���W�̐ݒ菈��

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(NEW_RECORD_TEXTURE));
}

//========================
// ��������
//========================
CNewRecord* CNewRecord::Create(const D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CNewRecord* pNewRecord = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pNewRecord == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pNewRecord = new CNewRecord;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pNewRecord != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pNewRecord->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�V�L�^�̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pNewRecord->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �V�L�^�̃|�C���^��Ԃ�
	return pNewRecord;
}