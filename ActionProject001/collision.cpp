//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "player.h"
#include "player_act.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "screw.h"
#include "screw_manager.h"
#include "useful.h"

//===============================
// �}�N����`
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)
#define AIRPLANE_COLL_RADIUS			(55.0f)			// ��s�@�̓����蔻�莞�̔��a
#define PLAYER_SIZE						(D3DXVECTOR3(20.0f,70.0f,20.0f))	// �v���C���[�̃T�C�Y
#define PLAYER_HALF_HEIGHT				(PLAYER_SIZE.y / 2)					// �v���C���[�̍����̔���
#define SCREW_COLL_RADIUS				(20.0f)			// �l�W�̓����蔻�莞�̔��a

//===============================
// �ۉe�̋N���n�ʂ̓����蔻�菈��
//===============================
void collision::ShadowElevCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// �e�̃|�C���^
	CElevation* pMesh = nullptr;			// ���b�V���̃|�C���^
	D3DXVECTOR3 posShadow = pos;				// �e�̈ʒu

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL ����Ȃ������ꍇ

		// �I�u�W�F�N�g�̃|�C���^���擾����
		pMesh = CElevationManager::Get()->GetTop();

		while (pMesh != nullptr)
		{ // �I�u�W�F�N�g�̂� NULL ����Ȃ������

			// �e�̈ʒu��ݒ肷��
			posShadow.y = pMesh->ElevationCollision(posShadow);

			// ���̃I�u�W�F�N�g��������
			pMesh = pMesh->GetNext();
		}

		// �ʒu��ݒ肷��
		pShadow->SetPos(posShadow);
	}
}

//===============================
// �v���C���[�Ɣ�s�@�Ƃ̓����蔻��
//===============================
void collision::AirplaneHit(CPlayer& player)
{
	// ���[�J���ϐ��錾
	CAirplane* pAirplane = nullptr;	// �e�̃|�C���^
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// �v���C���[�̈ʒu
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// �ő�l
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// �ŏ��l
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// �ő�l
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// �ŏ��l

	// �I�u�W�F�N�g�̃|�C���^���擾����
	pAirplane = CAirplaneManager::Get()->GetTop();

	while (pAirplane != nullptr)
	{ // �I�u�W�F�N�g�̂� NULL ����Ȃ������

		if (useful::RectangleCollisionXY(pAirplane->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pAirplane->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // ��`�̓����蔻�肪 true �̏ꍇ

			if (player.GetAction()->GetAct() != CPlayerAct::ACT_CANNON &&
				player.GetAction()->GetAct() != CPlayerAct::ACT_FLY)
			{ // ��Ԃ���C�ҋ@�ȊO�̏ꍇ

				// �v���C���[�̈ʒu��ݒ肷��
				player.SetPos(pAirplane->GetPos());

				// ��Ԃ̐ݒ菈��
				player.GetAction()->SetAct(CPlayerAct::ACT_CANNON);
			}

			// ���̐�̏����𔲂��o��
			return;
		}

		// ���̃I�u�W�F�N�g��������
		pAirplane = pAirplane->GetNext();
	}
}

//===============================
// �v���C���[�ƃl�W�Ƃ̓����蔻��
//===============================
void collision::ScrewHit(CPlayer& player)
{
	// ���[�J���ϐ��錾
	CScrew* pScrew = nullptr;	// �e�̃|�C���^
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// �v���C���[�̈ʒu
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// �ő�l
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// �ŏ��l
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// �ő�l
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// �ŏ��l

	// �I�u�W�F�N�g�̃|�C���^���擾����
	pScrew = CScrewManager::Get()->GetTop();

	while (pScrew != nullptr)
	{ // �I�u�W�F�N�g�̂� NULL ����Ȃ������

		if (useful::RectangleCollisionXY(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // ��`�̓����蔻�肪 true �̏ꍇ

			// �q�b�g����
			pScrew->Hit(pScrew->GetPos());

			// ���̐�̏������s��Ȃ�
			return;
		}

		// ���̃I�u�W�F�N�g��������
		pScrew = pScrew->GetNext();
	}
}