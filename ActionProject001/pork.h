//===================================
//
// �|�[�N�w�b�_�[[pork.h]
// Author ��������
//
//===================================
#ifndef _PORK_H_
#define _PORK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CSignBoard;		// �Ŕ�

//-----------------------------------
// �N���X��`(�|�[�N)
//-----------------------------------
class CPork : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HOVER = 0,		// �z�o�[
		TYPE_DASH,			// �_�b�V��
		TYPE_QUAKE,			// �O���E���h�N�G�C�N
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CPork();				// �R���X�g���N�^
	~CPork();				// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CPork* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CPork* pNext);	// ��̃|�C���^�̐ݒ菈��
	CPork* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CPork* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CPork* Create(const D3DXVECTOR3& pos, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CSignBoard* m_pSignBoard;		// �Ŕ̃|�C���^

	// ���X�g�\���֌W
	CPork* m_pPrev;	// �O�ւ̃|�C���^
	CPork* m_pNext;	// ���ւ̃|�C���^
};

#endif