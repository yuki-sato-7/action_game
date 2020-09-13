/**
 * @file EnemyManager.h
 * @brief �G�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */

#pragma once

#include "ESGLib.h"
#include "Enemy.h"
#include <vector>
#include <memory>
#include "Observer.h"
#include "Enum.h"

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

	/**
�@�@ * @brief �I�u�U�[�o�[�ɐV���ȃI�u�U�[�o�[��ǉ�
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AddObserver(IObserver* observer)
	{
		game_clear_subject_.addObserver(observer);
	}

	/**
�@�@ * @brief �I�u�U�[�o�[�̃��X�g����I�u�U�[�o�[���폜
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void RemoveObserver(IObserver* observer)
	{
		game_clear_subject_.removeObserver(observer);
	}

	/**
�@�@ * @brief ���X�g�ɓo�^����Ă���I�u�U�[�o�[�̕ω���ʒm
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AllDelteObserver(IObserver* observer)
	{
		game_clear_subject_.alldelteObservers();
	}

	//�G�̏��擾
	std::vector< std::shared_ptr<Enemy> >& GetEnemys() { return enemy_vector_; }

private:
	//! �G�̏��
	std::vector< std::shared_ptr<Enemy> > enemy_vector_;

	Subject game_clear_subject_;
};