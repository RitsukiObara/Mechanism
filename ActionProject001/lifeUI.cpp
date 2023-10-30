//============================================
//
// �̗�UI����[lifeUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "lifeUI.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"

#include "player.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define BACK_TEXTURE		"data\\TEXTURE\\LifeUIBack.png"			// �w�i�̃e�N�X�`��
#define LIFE_TEXTURE		"data\\TEXTURE\\LifeUIMark.png"			// �̗͂̃e�N�X�`��
#define BACK_POS			(D3DXVECTOR3(170.0f, 50.0f, 0.0f))		// �w�i�̈ʒu
#define LIFE_POS			(D3DXVECTOR3(80.0f, 50.0f, 0.0f))		// �̗͂̈ʒu
#define BACK_SIZE			(D3DXVECTOR3(160.0f, 40.0f, 0.0f))		// �w�i�̃T�C�Y
#define LIFE_SIZE			(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// �̗͂̃T�C�Y
#define LIFE_SHIFT			(90.0f)									// �̗͂̂��炷��

//========================
// �R���X�g���N�^
//========================
CLifeUI::CLifeUI() : CObject(TYPE_LIFEUI, PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		// �����̏��
		m_apLife[nCnt] = nullptr;
	}
	m_pBack = nullptr;	// �w�i
}

//========================
// �f�X�g���N�^
//========================
CLifeUI::~CLifeUI()
{

}

//========================
// ����������
//========================
HRESULT CLifeUI::Init(void)
{
	if (FAILED(CreateBack()))
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (FAILED(CreateLife()))
	{ // �����Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CLifeUI::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		// �̗͂̏I������
		m_apLife[nCnt]->Uninit();
	}

	// �w�i�̏I������
	m_pBack->Uninit();

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CLifeUI::Update(void)
{
	// �v���C���[�̗̑͂��擾����
	int nLife = CPlayer::Get()->GetLife();

	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		if (nLife > nCnt)
		{ // �̗͂�����̂������|���S���̏ꍇ

			// ���_�J���[�̐ݒ菈��
			m_apLife[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{ // ��L�ȊO

			// ���_�J���[�̐ݒ菈��
			m_apLife[nCnt]->SetVtxColor(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f));
		}
	}
}

//========================
// �`�揈��
//========================
void CLifeUI::Draw(void)
{
	if (m_pBack != nullptr)
	{ // �w�i�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pBack->Draw();
	}

	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		if (m_apLife[nCnt] != nullptr)
		{ // ������ NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apLife[nCnt]->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CLifeUI::SetData(void)
{
	// �̗͂̏��̐ݒ菈��
	SetDataLife();

	// �w�i�̏��̐ݒ菈��
	SetDataBack();
}

//========================
// �w�i�̏��̐ݒ菈��
//========================
void CLifeUI::SetDataBack(void)
{
	// �ݒ菈��
	m_pBack->SetPos(BACK_POS);				// �ʒu�ݒ�
	m_pBack->SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	m_pBack->SetSize(BACK_SIZE);			// �T�C�Y�ݒ�
	m_pBack->SetLength();					// �����ݒ�
	m_pBack->SetAngle();					// �����ݒ�

	// ���_���̐ݒ菈��
	m_pBack->SetVertex();
}

//========================
// �̗͂̐�������
//========================
void CLifeUI::SetDataLife(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		// �ݒ菈��
		m_apLife[nCnt]->SetPos(D3DXVECTOR3(LIFE_POS.x + (nCnt * LIFE_SHIFT), LIFE_POS.y, 0.0f));		// �ʒu�ݒ�
		m_apLife[nCnt]->SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
		m_apLife[nCnt]->SetSize(LIFE_SIZE);			// �T�C�Y�ݒ�
		m_apLife[nCnt]->SetLength();				// �����ݒ�
		m_apLife[nCnt]->SetAngle();					// �����ݒ�

		// ���_���̐ݒ菈��
		m_apLife[nCnt]->SetVertex();
	}
}

//========================
// �w�i�̐�������
//========================
HRESULT CLifeUI::CreateBack(void)
{
	if (m_pBack == nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		// ���������m�ۂ���
		m_pBack = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	if (m_pBack != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pBack->Init()))
		{ // �����������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		// �e�N�X�`���̊��蓖�ď���
		m_pBack->BindTexture(CManager::Get()->GetTexture()->Regist(BACK_TEXTURE));
	}
	else
	{ // �|�C���^���@NULL �̏ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// �̗͂̐�������
//========================
HRESULT CLifeUI::CreateLife(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_LIFE_POLYGON; nCnt++)
	{
		if (m_apLife[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apLife[nCnt] = new CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apLife[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apLife[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apLife[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(LIFE_TEXTURE));
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//========================
// ��������
//========================
CLifeUI* CLifeUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CLifeUI* pLife = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLife == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLife = new CLifeUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLife != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLife->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLife->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �̗�UI�̃|�C���^��Ԃ�
	return pLife;
}