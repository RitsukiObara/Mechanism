//============================================
//
// �����L���O�̕�������[ranking_word.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "ranking_word.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RANKING_WORD_POS				(D3DXVECTOR3(120.0f, 40.0f, 0.0f))		// �����L���O�̕����̈ʒu
#define RANKING_WORD_TRANS_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 40.0f, 0.0f))		// �����L���O�̎����J�ڌ�̕����̈ʒu
#define RANKING_WORD_SIZE				(D3DXVECTOR3(120.0f, 40.0f, 0.0f))		// �����L���O�̕����̃T�C�Y
#define RANKING_WORD_TEXTURE			"data/TEXTURE/RankingWord.png"			// �����L���O�̕����̃e�N�X�`��

//========================
// �R���X�g���N�^
//========================
CRankingWord::CRankingWord() : CObject2D(CObject::TYPE_RANKINGWORD, CObject::PRIORITY_UI)
{

}

//========================
// �f�X�g���N�^
//========================
CRankingWord::~CRankingWord()
{

}

//========================
// ����������
//========================
HRESULT CRankingWord::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	//// ���̐ݒ�
	//if (CManager::GetClear() == true)
	//{ // �N���A��̏ꍇ

		// �ʒu
		SetPos(RANKING_WORD_POS);
	//}
	//else
	//{ // ��L�ȊO

	//	// �ʒu
	//	SetPos(RANKING_WORD_TRANS_POS);
	//}
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
	SetSize(RANKING_WORD_SIZE);				// �T�C�Y
	SetAngle();								// ����
	SetLength();							// ����

	SetVertex();							// ���_���W�̐ݒ菈��

	// �e�N�X�`���̊��蓖�ď���
	BindTexture(CManager::Get()->GetTexture()->Regist(RANKING_WORD_TEXTURE));

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CRankingWord::Uninit(void)
{
	// �j������
	CObject2D::Uninit();
}

//========================
// �X�V����
//========================
void CRankingWord::Update(void)
{

}

//========================
// �`�揈��
//========================
void CRankingWord::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//========================
// ��������
//========================
CRankingWord* CRankingWord::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRankingWord* pScore = nullptr;			// �v���C���[�̃C���X�^���X�𐶐�

	if (pScore == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScore = new CRankingWord;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScore != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScore->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�X�R�A�\���̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �X�R�A�\���̃|�C���^��Ԃ�
	return pScore;
}