//===========================================
//
// �|�[�Y�w�b�_�[[pause.h]
// Author ��������
//
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "main.h"

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CObject2D;

//-------------------------------------------
// �N���X��`(�|�[�Y)
//-------------------------------------------
class CPause : public CObject
{
public:		// �N�ł��A�N�Z�X�ł���

	// �|�[�Y��ʂ̍\�����̒�`
	enum MENU
	{
		MENU_CONTINUE = 0,		// �R���e�j���[
		MENU_RESET,				// ���g���C
		MENU_TITLE,				// �^�C�g���ɖ߂�
		MENU_MAX
	};

	// �|�[�Y��ʂ̃o�b�t�@�̒�`
	enum POLYGON
	{
		POLYGON_BACK = 0,		// �^�����|���S��
		POLYGON_MENU,			// ���j���[
		POLYGON_CONTINUE,		// �R���e�j���[
		POLYGON_RESET,			// ���g���C
		POLYGON_TITLE,			// �N�C�b�g
		POLYGON_MAX
	};

	// �\���̒�`(���\����)
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 size;		// �T�C�Y
	};

	CPause();					// �R���X�g���N�^
	virtual ~CPause();			// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);	// ����������
	virtual void Uninit(void);	// �I������
	virtual void Update(void);	// �X�V����
	virtual void Draw(void);	// �`�揈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetPause(const bool bPause);		// �|�[�Y�󋵂̐ݒ菈��
	bool GetPause(void);					// �|�[�Y�󋵂̎擾����

	void ChangeDisp(void);		// �`��󋵂̐؂�ւ�����

	// �ÓI�����o�֐�
	static CPause* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void SizeCorrect(int nIdx);		// �T�C�Y�␳����
	void PauseSelect(void);			// �|�[�Y�̑I������
	bool PauseDecide(void);			// �|�[�Y�̌��菈��
	void PauseAlphaCorrect(void);	// �|�[�Y�̓����x�␳����
	void PauseVertex(void);			// �|�[�Y�̒��_�ݒ菈��

	// �����o�ϐ�
	D3DXCOLOR m_PauseColor;					// �I�𒆂̑I�����̐F
	D3DXVECTOR3 sizeDest;					// �ڕW�̃T�C�Y
	CObject2D* m_apObject[POLYGON_MAX];		// �|���S���̏��
	MENU m_PauseMenu;						// �|�[�Y���j���[
	int m_nPauseCounter;					// �J�E���^�[
	float m_fPauseAlpha;					// �����x��ω�������ϐ�
	bool m_bPause;							// �|�[�Y��
	bool m_bDisp;							// �`���

	// �ÓI�����o�ϐ�
	static const char *c_apFilename[POLYGON_MAX];		// �e�N�X�`���t�@�C����
	static const Info c_aPauseInfo[POLYGON_MAX];		// �|�[�Y�̏��
};

#endif