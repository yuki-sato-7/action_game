/**
 * @file EnemyManager.h
 * @brief �G�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */

#pragma once

#include "ESGLib.h"
#include "Enemy.h"
#include "ResultManager.h"
#include <vector>
#include <memory>

class EnemyManager
{
public:
	/**
	 * @brief �G�Ǘ��N���X������������
	 * @return ���true
	 */
	virtual bool Initialize();

	/**
	 * @brief �G�Ǘ����A�b�v�f�[�g����
	 * @param[in] (player) �v���C���[�N���X
	 * @param[in] (ground) �X�e�[�W�w�i�Ǘ��N���X
	 * @param[in] (enemy_manager) �G�Ǘ��N���X
	 */
	virtual void Update(Player& player, Ground& ground);

	/**
	 * @brief �G�Ǘ��N���X��`�悷��
	 */
	virtual void Draw();

	/**
	 * @brief �G�𐶐�����
	 * @param[in] (player) �v���C���[�N���X
	 * @param[in] (enemy_pos) �G�̐������W
	 */
	void CreateEnemy(Player& player ,Vector3& enemy_pos);

	//�G�̏��擾
	std::vector< std::shared_ptr<Enemy> >& GetEnemys() { return enemy_vector_; }

private:
	//! �G�̏��
	std::vector< std::shared_ptr<Enemy> > enemy_vector_;
};