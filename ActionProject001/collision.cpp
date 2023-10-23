//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "game.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "player.h"
#include "player_act.h"
#include "player_ability.h"
#include "combo.h"
#include "combo_magni.h"
#include "screwUI.h"
#include "airplane.h"
#include "airplane_manager.h"
#include "screw.h"
#include "screw_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "table.h"
#include "table_manager.h"
#include "macchina.h"
#include "macchina_manager.h"
#include "goal.h"
#include "useful.h"

//===============================
// �}�N����`
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)
#define AIRPLANE_COLL_RADIUS			(55.0f)			// ��s�@�̓����蔻�莞�̔��a
#define PLAYER_SIZE						(D3DXVECTOR3(20.0f, 70.0f, 20.0f))		// �v���C���[�̃T�C�Y
#define PLAYER_HALF_HEIGHT				(PLAYER_SIZE.y / 2)						// �v���C���[�̍����̔���
#define SCREW_COLL_RADIUS				(20.0f)			// �l�W�̓����蔻�莞�̔��a
#define MACCHINA_HIT_RANGE				(D3DXVECTOR3(220.0f, 0.0f, 100.0f))		// �}�L�i���̓����蔻��͈̔�

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

			if (player.GetAction()->GetState() != CPlayerAct::STATE_CANNON &&
				player.GetAction()->GetState() != CPlayerAct::STATE_FLY)
			{ // ��Ԃ���C�ҋ@�ȊO�̏ꍇ

				// �v���C���[�̈ʒu��ݒ肷��
				player.SetPos(pAirplane->GetPos());

				// ��Ԃ̐ݒ菈��
				player.GetAction()->SetState(CPlayerAct::STATE_CANNON);
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
	CScrew* pScrew = CScrewManager::Get()->GetTop();	// �l�W�̃|�C���^
	CScrew* pScrewNext = nullptr;						// ���̃l�W�̃|�C���^
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// �v���C���[�̈ʒu
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// �ő�l
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// �ŏ��l
	D3DXVECTOR3 AirplaneVtxMax = D3DXVECTOR3(AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS, AIRPLANE_COLL_RADIUS);			// �ő�l
	D3DXVECTOR3 AirplaneVtxMin = D3DXVECTOR3(-AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS, -AIRPLANE_COLL_RADIUS);		// �ŏ��l

	while (pScrew != nullptr)
	{ // �I�u�W�F�N�g�̂� NULL ����Ȃ������

		// ���̃l�W�̏����擾����
		pScrewNext = pScrew->GetNext();

		if (useful::RectangleCollisionXY(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pScrew->GetPos(), PosPlayer, AirplaneVtxMax, VtxMax, AirplaneVtxMin, VtxMin) == true)
		{ // ��`�̓����蔻�肪 true �̏ꍇ

			// �q�b�g����
			pScrew->Hit(pScrew->GetPos());

			// �X�R�A�̉��Z����
			player.GetScrewUI()->AddScore(1);

			// �R���{�̉��Z����
			player.GetCombo()->AddCombo(10);
		}

		// ���̃I�u�W�F�N�g��������
		pScrew = pScrewNext;
	}
}

//===============================
// �v���C���[�ƓG�Ƃ̓����蔻��
//===============================
void collision::EnemyHit(CPlayer& player)
{
	// ���[�J���ϐ��錾
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// �G�̏��
	CEnemy* pEnemyNext = nullptr;							// ���̓G�̏��
	D3DXVECTOR3 pos = player.GetPos();						// �v���C���[�̈ʒu
	D3DXVECTOR3 posOld = player.GetPosOld();				// �v���C���[�̑O��̈ʒu
	D3DXVECTOR3 EnemyVtxMin = NONE_D3DXVECTOR3;				// �G�̍ŏ��l

	while (pEnemy != nullptr)
	{ // �G�̏�� NULL ����Ȃ��ꍇ

		// �G�̏����擾����
		pEnemyNext = pEnemy->GetNext();

		// �G�̍ŏ��l��ݒ肷��
		EnemyVtxMin = D3DXVECTOR3(-pEnemy->GetCollSize().x, 0.0f, -pEnemy->GetCollSize().z);

		if (pEnemy->GetPos().z + pEnemy->GetFileData().collsize.z >= pos.z &&
			pEnemy->GetPos().z - pEnemy->GetFileData().collsize.z <= pos.z &&
			pEnemy->IsCollision() == true)
		{ // �G��Z���������Ă��邩�A�����蔻��󋵂� true �̏ꍇ

			if (posOld.y >= pEnemy->GetPosOld().y + pEnemy->GetCollSize().y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetCollSize().y &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + EnemyVtxMin.x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetCollSize().x)
			{ // �ォ��̓����蔻��

				if (pEnemy->IsStep() == true)
				{ // ���݂�����̏ꍇ

					// �G�̃q�b�g����
					pEnemy->Hit();

					// ���݂����̏���
					player.StepHit();
				}
				else
				{ // ��L�ȊO

					// �v���C���[�̃q�b�g����
					player.Hit();
				}
			}
			else if (posOld.y + PLAYER_SIZE.y <= pEnemy->GetPosOld().y + EnemyVtxMin.y &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + EnemyVtxMin.y &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + EnemyVtxMin.x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetCollSize().x)
			{ // ������̓����蔻��

				if (player.GetAbility()->GetAbility() == CAbility::ABILITY_JETDASH || 
					player.GetAbility()->GetAbility() == CAbility::ABILITY_DASHJUMP)
				{ // �W�F�b�g�_�b�V���܂��́A�_�b�V���W�����v��Ԃ̏ꍇ

					// �G�̃q�b�g����
					pEnemy->SmashHit();

					// �R���{�̉��Z����
					player.GetCombo()->AddCombo(100);
				}
				else
				{ // ��L�ȊO

					// �v���C���[�̃q�b�g����
					player.Hit();
				}
			}
			else if (posOld.x + PLAYER_SIZE.x <= pEnemy->GetPosOld().x + EnemyVtxMin.x &&
				pos.x + PLAYER_SIZE.x >= pEnemy->GetPos().x + EnemyVtxMin.x &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + EnemyVtxMin.y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetCollSize().y)
			{ // ������̓����蔻��

				if (player.GetAbility()->GetAbility() == CAbility::ABILITY_JETDASH ||
					player.GetAbility()->GetAbility() == CAbility::ABILITY_DASHJUMP)
				{ // �W�F�b�g�_�b�V����Ԃ̏ꍇ

					// �G�̃q�b�g����
					pEnemy->SmashHit();

					// �R���{�̉��Z����
					player.GetCombo()->AddCombo(100);
				}
				else
				{ // ��L�ȊO

					// �v���C���[�̃q�b�g����
					player.Hit();
				}
			}
			else if (posOld.x - PLAYER_SIZE.x >= pEnemy->GetPosOld().x + pEnemy->GetCollSize().x &&
				pos.x - PLAYER_SIZE.x <= pEnemy->GetPos().x + pEnemy->GetCollSize().x &&
				pos.y + PLAYER_SIZE.y >= pEnemy->GetPos().y + EnemyVtxMin.y &&
				pos.y <= pEnemy->GetPos().y + pEnemy->GetCollSize().y)
			{ // �E����̓����蔻��

				if (player.GetAbility()->GetAbility() == CAbility::ABILITY_JETDASH ||
					player.GetAbility()->GetAbility() == CAbility::ABILITY_DASHJUMP)
				{ // �W�F�b�g�_�b�V����Ԃ̏ꍇ

					// �G�̐�����уq�b�g����
					pEnemy->SmashHit();

					// �R���{�̉��Z����
					player.GetCombo()->AddCombo(100);
				}
				else
				{ // ��L�ȊO

					// �v���C���[�̃q�b�g����
					player.Hit();
				}
			}
		}

		// ���̃I�u�W�F�N�g��������
		pEnemy = pEnemyNext;
	}
}

//===============================
// �v���C���[�ƓG�Ƃ̂߂肱�ݔ���
//===============================
void collision::EnemyPenetrate(CPlayer& player)
{
	// ���[�J���ϐ��錾
	CEnemy* pEnemy = CEnemyManager::Get()->GetTop();		// �G�̏��
	CEnemy* pEnemyNext = nullptr;							// ���̓G�̏��
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// �v���C���[�̈ʒu
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// �ő�l
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// �ŏ��l
	D3DXVECTOR3 EnemyVtxMin = NONE_D3DXVECTOR3;				// �G�̍ŏ��l

	while (pEnemy != nullptr)
	{ // �G�̏�� NULL ����Ȃ��ꍇ

		// �G�̏����擾����
		pEnemyNext = pEnemy->GetNext();

		// �G�̍ŏ��l��ݒ肷��
		EnemyVtxMin = D3DXVECTOR3(-pEnemy->GetCollSize().x, 0.0f, -pEnemy->GetCollSize().z);

		if (useful::RectangleCollisionXY(pEnemy->GetPos(), PosPlayer, pEnemy->GetCollSize(), VtxMax, EnemyVtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pEnemy->GetPos(), PosPlayer, pEnemy->GetCollSize(), VtxMax, EnemyVtxMin, VtxMin) == true &&
			pEnemy->IsCollision() == true)
		{ // �G�ƃv���C���[���d�Ȃ��Ă��鎞

			if (player.GetAction()->GetState() == CPlayerAct::STATE_FLY ||
				player.GetAbility()->GetAbility() == CAbility::ABILITY_JETDASH ||
				player.GetAbility()->GetAbility() == CAbility::ABILITY_DASHJUMP)
			{ // ���ł���ꍇ

				// ������΂�����
				pEnemy->SmashHit();
			}
			else
			{ // ��L�ȊO

				// �v���C���[�̃q�b�g����
				player.Hit();
			}
		}

		// ���̃I�u�W�F�N�g��������
		pEnemy = pEnemyNext;
	}
}

//===============================
// ��Ƃ̓����蔻��
//===============================
bool collision::TableCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posOld, const float fWidth, const float fDepth)
{
	// ���[�J���ϐ��錾
	CTable* pTable = CTableManager::Get()->GetTop();		// �G�̏��
	bool bLand = false;										// ���n����

	while (pTable != nullptr)
	{ // �G�̏�� NULL ����Ȃ��ꍇ

		if (posOld.y >= pTable->GetPosOld().y + pTable->GetFileData().vtxMax.y &&
			pos->y <= pTable->GetPosOld().y + pTable->GetFileData().vtxMax.y &&
			pos->x + fWidth >= pTable->GetPos().x + pTable->GetFileData().vtxMin.x &&
			pos->x - fWidth <= pTable->GetPos().x + pTable->GetFileData().vtxMax.x &&
			pos->z + fDepth >= pTable->GetPos().z + pTable->GetFileData().vtxMin.z &&
			pos->z - fDepth <= pTable->GetPos().z + pTable->GetFileData().vtxMax.z)
		{ // �ォ��̓����蔻��

			// �ʒu��␳
			pos->y = pTable->GetPos().y + pTable->GetFileData().vtxMax.y + COLLISION_ADD_DIFF_LENGTH;

			// ���n�����t�^����
			bLand = true;
		}

		// ���̃I�u�W�F�N�g��������
		pTable = pTable->GetNext();
	}

	// ���n�����Ԃ�
	return bLand;
}

//===============================
// �v���C���[�ƃ}�L�i���Ƃ̓����蔻��
//===============================
void collision::MacchinaHit(CPlayer& player)
{
	// ���[�J���ϐ��錾
	CMacchina* pMacchina = CMacchinaManager::Get()->GetTop();		// �}�L�i���̏��

	while (pMacchina != nullptr)
	{ // �G�̏�� NULL ����Ȃ��ꍇ

		if (useful::RectangleCollisionXZ(player.GetPos(), pMacchina->GetPos(), MACCHINA_HIT_RANGE, NONE_D3DXVECTOR3, -MACCHINA_HIT_RANGE, NONE_D3DXVECTOR3) &&
			pMacchina->GetCollision() == true)
		{ // �����蔻��ɓ��������ꍇ

			// �q�b�g����
			pMacchina->Hit();
		}

		// ���̃I�u�W�F�N�g��������
		pMacchina = pMacchina->GetNext();
	}
}

//===============================
// �v���C���[�ƃS�[���Ƃ̓����蔻��
//===============================
void collision::GoalHit(CPlayer& player)
{
	// ���[�J���|�C���^�錾
	CModel* pGoal = nullptr;		// �S�[���̃|�C���^
	D3DXVECTOR3 PosPlayer = D3DXVECTOR3(player.GetPos().x, player.GetPos().y + PLAYER_HALF_HEIGHT, player.GetPos().z);		// �v���C���[�̈ʒu
	D3DXVECTOR3 VtxMax = D3DXVECTOR3(PLAYER_SIZE.x, PLAYER_HALF_HEIGHT, PLAYER_SIZE.z);										// �ő�l
	D3DXVECTOR3 VtxMin = D3DXVECTOR3(-PLAYER_SIZE.x, -PLAYER_HALF_HEIGHT, -PLAYER_SIZE.z);									// �ŏ��l

	if (CGoal::Get() != nullptr)
	{ // �S�[���� NULL ����Ȃ��ꍇ

		// �S�[���̏����擾����
		pGoal = CGoal::Get()->GetModel(CGoal::MODEL_BODY);

		if (useful::RectangleCollisionXY(pGoal->GetPos(), PosPlayer, pGoal->GetFileData().vtxMax, VtxMax, pGoal->GetFileData().vtxMin, VtxMin) == true &&
			useful::RectangleCollisionXZ(pGoal->GetPos(), PosPlayer, pGoal->GetFileData().vtxMax, VtxMax, pGoal->GetFileData().vtxMin, VtxMin) == true)
		{ // ��`�̓����蔻�肪 true �̏ꍇ

			// �q�b�g����
			CGoal::Get()->Hit();
		}
	}
}