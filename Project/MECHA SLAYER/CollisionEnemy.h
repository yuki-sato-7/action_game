/**
 * @file CameraMain.h
 * @brief �Փ˔���p�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "Player.h"
#include "EnemyManager.h"
#include "EffeksserManager.h"


class CollisionEnemy
{
public:

	/**
	 * @brief �X�V�i�v���C���[�A�G�̍U���̏Փ˔��菈���j
	 * @param[in] (em) �G�Ǘ��N���X
	 * @param[in] (player) �v���C���[�N���X
	 */
	virtual void Update(EnemyManager& em, Player& player);
};
