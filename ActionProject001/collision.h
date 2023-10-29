//===================================
//
// �����蔻��w�b�_�[[collision.h]
// Author ��������
//
//===================================
#ifndef _COLLISION_H_			//���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CPlayer;		// �v���C���[
class CEnemy;		// �G
class CBlock;		// �u���b�N

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �ۉe�̓����蔻��
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// �ۉe�̓����蔻��
	void ShadowElevCollision(D3DXVECTOR3& pos);										// �ۉe�ƋN���n�ʂ̓����蔻��
	void ShadowBlockCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posPlayer);		// �ۉe�ƃu���b�N�̓����蔻��
	void ShadowTableCollision(D3DXVECTOR3& pos, const D3DXVECTOR3& posPlayer);		// �ۉe�Ƒ�̓����蔻��

	// ��s�@�̓����蔻��
	void AirplaneHit(CPlayer& player);			// �v���C���[�Ɣ�s�@�Ƃ̓����蔻��

	// �A�C�e���̓����蔻��
	void ScrewHit(CPlayer& player);				// �v���C���[�ƃl�W�Ƃ̓����蔻��

	// �G�̓����蔻��
	void EnemyHit(CPlayer& player);				// �v���C���[�ƓG�Ƃ̓����蔻��
	void EnemyPenetrate(CPlayer& player);		// �v���C���[�ƓG�Ƃ̂߂肱�ݔ���
	//void EnemyToEnemy(CEnemy* pTarget);		// �G���m�̓����蔻�菈��
	void EnemyStun(CPlayer& player);			// �G�̋C�⏈��

	// �e�[�u���̓����蔻��
	bool TableCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth, const float fDepth);		// ��Ƃ̓����蔻��

	// �}�L�i���̓����蔻��
	void MacchinaHit(CPlayer& player);			// �v���C���[�ƃ}�L�i���Ƃ̓����蔻��

	// �S�[���̓����蔻��
	void GoalHit(CPlayer& player);				// �v���C���[�ƃS�[���Ƃ̓����蔻��

	// ���̓����蔻��
	void NeedleHit(CPlayer& player);			// �v���C���[�ƞ��̓����蔻��

	// �u���b�N�̓����蔻��
	bool BlockCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth, const float fHeight, const bool bJump, CBlock** ppRide);		// �u���b�N�Ƃ̓����蔻��
}

#endif