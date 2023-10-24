//===================================
//
// �G�w�b�_�[[enemy.h]
// Author ��������
//
//===================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CStun;			// �C�≉�o

//-----------------------------------
// �N���X��`(�G)
//-----------------------------------
class CEnemy : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_ITOCAN = 0,		// �C�g�L����
		TYPE_MACHIDORI,			// �}�V���h���[
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CEnemy();							// �R���X�g���N�^
	CEnemy(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CEnemy();					// �f�X�g���N�^
	void Box(void);						// �R���X�g���N�^�̔�

	// ���X�g�\���֌W
	void SetPrev(CEnemy* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CEnemy* pNext);	// ��̃|�C���^�̐ݒ菈��
	CEnemy* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CEnemy* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void Hit(void);			// �q�b�g����
	virtual void SmashHit(void);	// ������уq�b�g����
	virtual void StunHit(void);		// �C��̃q�b�g����
	virtual void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	CStun* GetStun(void) const;					// �C�≉�o�̎擾����
	void DeleteStun(void);						// �C���Ԃ̏�������

	D3DXVECTOR3 GetInitPos(void) const;			// �����ʒu�̎擾����

	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����

	void SetCollSize(const D3DXVECTOR3& size);	// �����蔻��̃T�C�Y�̐ݒ菈��
	D3DXVECTOR3 GetCollSize(void) const;		// �����蔻��̃T�C�Y�̎擾����

	void SetEnableStep(const bool bStep);		// ���݂��󋵂̐ݒ菈��
	bool IsStep(void) const;					// ���݂��󋵂̎擾����

	void SetEnableCollision(const bool bColl);	// �����蔻��󋵂̐ݒ菈��
	bool IsCollision(void) const;				// �����蔻��󋵂̎擾����

	// ���̑��̊֐�
	void Gravity(void);				// �d�͏���
	bool ElevationCollision(void);	// �N���n�ʂ̓����蔻�菈��
	bool TableCollision(void);		// ��Ƃ̓����蔻��

	// �ÓI�����o�֐�
	static CEnemy* Create(const D3DXVECTOR3& pos, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CStun* m_pStun;			// �C�≉�o�̃|�C���^

	D3DXVECTOR3 m_posInit;	// �����ʒu
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_sizeColl;	// �����蔻��̃T�C�Y
	bool m_bStep;			// ���݂���
	bool m_bCollision;		// �����蔻���ʂ邩�ǂ���

	// ���X�g�\���֌W
	CEnemy* m_pPrev;	// �O�ւ̃|�C���^
	CEnemy* m_pNext;	// ���ւ̃|�C���^
};

#endif