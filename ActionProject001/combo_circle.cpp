//=======================================
//
// �R���{�̐����~�̃��C������[combo_circle.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "combo_circle.h"
#include "objectDonut2D.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================

//=========================
// �R���X�g���N�^
//=========================
CComboCircle::CComboCircle() : CDonut2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_nVtx = 0;				// ���_��
	m_bEnd = false;			// �������ԏ�
}

//=========================
// �f�X�g���N�^
//=========================
CComboCircle::~CComboCircle()
{

}

//=========================
// ����������
//=========================
HRESULT CComboCircle::Init(void)
{
	if (FAILED(CDonut2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nVtx = 0;				// ���_��
	m_bEnd = false;			// �������ԏ�

	// �F��ݒ肷��
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CComboCircle::Uninit(void)
{
	// �I��
	CDonut2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CComboCircle::Update(void)
{
	// ���_�������Z����
	m_nVtx--;

	if (m_nVtx <= 0)
	{ // ���_����0�ȉ��ɂȂ����ꍇ

		// ���_����ݒ肷��
		m_nVtx = 0;

		// �I���󋵂ɂ���
		m_bEnd = true;
	}

	// ���_�J���[�̐ݒ菈��(�͈͐ݒ�)
	SetVtxColor(m_nVtx, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
}

//=========================
// �`�揈��
//=========================
void CComboCircle::Draw(void)
{
	// �`�揈��
	CDonut2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CComboCircle::SetData(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi)
{
	// �S�Ă̒l��ݒ肷��
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetSize(fSize);			// �T�C�Y
	SetDistance(fDist);		// ����
	SetDivi(nDivi);			// ������
	SetNumVtx();			// �����_��

	// �S�Ă̒l��ݒ肷��
	m_nVtx = 0;				// ���_��
	m_bEnd = false;			// �������ԏ�
}

//=========================
// ��������
//=========================
CComboCircle* CComboCircle::Create(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CComboCircle* pComboCircle = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pComboCircle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pComboCircle = new CComboCircle;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pComboCircle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pComboCircle->SetData(pos, fSize, fDist, nDivi);

		// ����������
		if (FAILED(pComboCircle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �R���{�̉~�̃|�C���^��Ԃ�
	return pComboCircle;
}

//=========================
// ���_�̃��Z�b�g����
//=========================
void CComboCircle::ResetNumVtx(void)
{
	// ���_���ő�ɐݒ肷��
	m_nVtx = GetNumVtx();

	// �I���󋵂� false �ɂ���
	m_bEnd = false;
}

//=========================
// �I���󋵂̐ݒ菈��
//=========================
void CComboCircle::SetEnd(const bool bEnd)
{
	// �I���󋵂�ݒ肷��
	m_bEnd = bEnd;
}

//=========================
// �I���󋵂̎擾����
//=========================
bool CComboCircle::GetEnd(void)
{
	// �I���󋵂�Ԃ�
	return m_bEnd;
}