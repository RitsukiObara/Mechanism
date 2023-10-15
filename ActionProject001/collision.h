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

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �ۉe�̓����蔻��
	void ShadowElevCollision(const D3DXVECTOR3& pos, int nIdx);		// �ۉe�ƋN���n�ʂ̓����蔻��

	// ��s�@�̓����蔻��
	void AirplaneHit(CPlayer& player);								// �v���C���[�Ɣ�s�@�Ƃ̓����蔻��

	// �A�C�e���̓����蔻��
	void ScrewHit(CPlayer& player);									// �v���C���[�ƃl�W�Ƃ̓����蔻��

	// �G�̓����蔻��
	void EnemyHit(CPlayer& player);									// �v���C���[�ƓG�Ƃ̓����蔻��
	void EnemyPenetrate(CPlayer& player);							// �v���C���[�ƓG�Ƃ̂߂肱�ݔ���
}

#endif