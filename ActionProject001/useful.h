//============================================
//
// �֗��w�b�_�[[useful.h]
// Author�F��������
//
//============================================
#ifndef _USEFUL_H_				//���̃}�N����`������Ă��Ȃ�������
#define _USEFUL_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// ���O���
//--------------------------------------------
namespace useful
{
	void RotNormalize(float *pRot);													// �����̐��K��
	void Gravity(float *fGravity, D3DXVECTOR3& pPos, const float fAdd);				// �d�͏���
	void RotCorrect(const float fDest, float *pRot, const float fCorrect);			// �����̕␳����(�z�[�~���O����)
	void Correct(const float fDest, float *pValue, const float fCorrect);			// �l�̕␳����
	void ColReverse(float *pData);													// 1.0f��0.0f�𔽓]���鏈��
	bool CircleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1);		// �~�̓����蔻��(XY����)
	bool CircleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1);		// �~�̓����蔻��(XZ����)
	float LineOuterProductXZ(D3DXVECTOR3 posLeft, D3DXVECTOR3 posRight, D3DXVECTOR3 pos);										// �O�ς̍��E���f����(XZ����)
	float LineOuterProductXY(D3DXVECTOR3 posUp, D3DXVECTOR3 posDown, D3DXVECTOR3 pos);											// �O�ς̍��E���f����(XY����)
	void NormalizeVector(D3DXVECTOR3& nor, const D3DXVECTOR3& posRight, const D3DXVECTOR3& posLeft, const D3DXVECTOR3& pos);	// �@���̌v�Z(���K��)
	float InnerProduct(const D3DXVECTOR3 VecMove, const D3DXVECTOR3 VecNor);		// ���ς̔��菈��
	bool CollisionOuterProductXZ(D3DXVECTOR3& Targetpos, D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft);		// �O�ς̓����蔻�菈��(XZ����)
	bool CollisionOuterProductXY(D3DXVECTOR3& Targetpos, D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft);		// �O�ς̓����蔻�菈��(XY����)
	bool RectangleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1);		// XY���W�̋�`�̓����蔻��
	bool RectangleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1);		// XZ���W�̋�`�̓����蔻��
	void CylinderCollision(D3DXVECTOR3* TargetPos, const D3DXVECTOR3& ObjectPos, const float fObjectRadius);					// �~���̓����蔻��
	void DecimalCalculation(const int nDigit, const int nValue, int* aAnswer);		// 10�i���ւ̕ϊ�����
	void FrameCorrect(const float fDest, float *fTarget, const float fCorrect);		// �ϓ��Ȑ��l�̕␳
}

#endif