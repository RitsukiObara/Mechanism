//===========================================
//
// �u���b�N�̃��C������[block.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "block.h"
#include "block_manager.h"
#include "useful.h"

//==============================
// �R���X�g���N�^
//==============================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_nBreakCount = 0;		// �j��J�E���g
	m_bBreak = false;		// �j���
	m_pPrev = nullptr;		// �O�ւ̃|�C���^
	m_pNext = nullptr;		// ���ւ̃|�C���^

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CBlockManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CBlock::~CBlock()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
//�u���b�N�̏���������
//==============================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nBreakCount = 0;		// �j��J�E���g
	m_bBreak = false;		// �j���

	// �l��Ԃ�
	return S_OK;
}

//========================================
//�u���b�N�̏I������
//========================================
void CBlock::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CBlockManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
//�u���b�N�̍X�V����
//========================================
void CBlock::Update(void)
{

}

//=====================================
//�u���b�N�̕`�揈��
//=====================================
void CBlock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);						// �ʒu
	SetPosOld(pos);						// �O��̈ʒu
	SetRot(rot);						// ����
	SetScale(scale);					// �g�嗦

	// �S�Ă̒l��ݒ肷��
	m_nBreakCount = 0;		// �j��J�E���g

	switch (type)
	{
	case TYPE_IRON:

		SetFileData(CXFile::TYPE_IRONBLOCK);	// ���f���̏��
		m_bBreak = false;		// �j���

		break;

	case TYPE_WOOD:

		SetFileData(CXFile::TYPE_WOODBLOCK);	// ���f���̏��
		m_bBreak = true;		// �j���

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �t�@�C���̏����擾����
	CXFile::SXFile file = GetFileData();

	// �ő�l�𔽉f����
	file.vtxMax.x *= scale.x;
	file.vtxMax.y *= scale.y;
	file.vtxMax.z *= scale.z;

	// �ŏ��l�𔽉f����
	file.vtxMin.x *= scale.x;
	file.vtxMin.y *= scale.y;
	file.vtxMin.z *= scale.z;

	// �f�[�^�̐ݒ菈��
	SetFileData(file);
}

//=======================================
// �j��J�E���g�̐ݒ菈��
//=======================================
void CBlock::SetBreakCount(const int nCount)
{
	// �j��J�E���g��ݒ肷��
	m_nBreakCount = nCount;
}

//=======================================
// �j��J�E���g�̎擾����
//=======================================
int CBlock::GetBreakCount(void) const
{
	// �j��J�E���g��Ԃ�
	return m_nBreakCount;
}

//=======================================
// �j��󋵂̐ݒ菈��
//=======================================
void CBlock::SetEnableBreak(const bool bBreak)
{
	// �j��󋵂�ݒ肷��
	m_bBreak = bBreak;
}

//=======================================
// �j��󋵂̎擾����
//=======================================
bool CBlock::IsBreak(void)
{
	// �j��󋵂�Ԃ�
	return m_bBreak;
}

//=======================================
// ��������
//=======================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBlock* pBlock = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pBlock == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �u���b�N�𐶐�
		pBlock = new CBlock;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBlock != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBlock->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBlock->SetData(pos, rot, scale, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pBlock;
}