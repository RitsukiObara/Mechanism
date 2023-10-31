//===================================
//
// �u���b�N�w�b�_�[[block.h]
// Author ��������
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_IRON = 0,		// �S��
		TYPE_WOOD,			// �ؔ�
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�h���b�v�̎��)
	enum DROPTYPE
	{
		DROPTYPE_NONE = 0,	// �h���b�v����
		DROPTYPE_ITEM,		// �A�C�e���h���b�v
		DROPTYPE_AIRPLANE,	// ��s�@�h���b�v
		DROPTYPE_MAX		// ���̗񋓌^�̑���
	};

	CBlock();				// �R���X�g���N�^
	~CBlock();				// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CBlock* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBlock* pNext);	// ��̃|�C���^�̐ݒ菈��
	CBlock* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CBlock* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Drop(void);		// �h���b�v����
	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type, const DROPTYPE dropType);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֐�
	void SetBreakCount(const int nCount);		// �j��J�E���g�̐ݒ菈��
	int GetBreakCount(void) const;				// �j��J�E���g�̎擾����
	void SetEnableBreak(const bool bBreak);		// �j��󋵂̐ݒ菈��
	bool IsBreak(void);							// �j��󋵂̎擾����

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const TYPE type, const DROPTYPE dropType);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	DROPTYPE m_dropType;	// �h���b�v�̎��
	int m_nBreakCount;		// �j��J�E���g
	bool m_bBreak;			// �j���

	// ���X�g�\���֌W
	CBlock* m_pPrev;	// �O�ւ̃|�C���^
	CBlock* m_pNext;	// ���ւ̃|�C���^
};

#endif