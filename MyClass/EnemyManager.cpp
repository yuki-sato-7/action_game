/**
 * @file EnemyManager.cpp
 * @brief �G�S�̊Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "EnemyManager.h"

/**
 * @brief �G�S�̊Ǘ��N���X������������
 * @return ���true
 */
bool EnemyManager::Initialize()
{
	return true;
}

/**
 * @brief �X�V�iHP�������Ȃ�����G�������j�A
 * @param[in] (player) �v���C���[�Ǘ��N���X
 * @param[in] (ground) �X�e�[�W�w�i�Ǘ��N���X
 * @param[in] (enemy_manager) �G�S�̊Ǘ��N���X
 */
void EnemyManager::Update(Player& player, Ground& ground)
{
	auto enemys_it = enemy_vector_.begin(); 
	while (enemys_it != enemy_vector_.end()) {
		(*enemys_it)->Update(player, ground, (*this));
		if ((*enemys_it)->GetSurvialFlag() != true) {
			enemys_it++;
		}
		else {
			enemys_it = enemy_vector_.erase(enemys_it);
		}
	}

	if (enemy_vector_.size() == 0) {
		game_clear_subject_.notifyObservers(GAME_CLEAR_STATE);  //�Q�[���N���A�ɂȂ������Ƃ��I�u�U�[�o�[�ɒʒm
	}
}

/**
 * @brief �G�S�̊Ǘ��N���X��`�悷��
 */
void EnemyManager::Draw()
{
	for (int i = 0; i < enemy_vector_.size(); i++)
		enemy_vector_[i]->Draw();
}

/**
 * @brief �G�𐶐�����
 * @param[in] (player) �v���C���[�Ǘ��N���X
 * @param[in] (enemy_pos) �G�̐������W
 */
void EnemyManager::CreateEnemy(Player& player,Vector3& enemy_pos_)
{
	std::shared_ptr<Enemy> enemy(new Enemy());
	enemy->Initialize(player,enemy_pos_);
	enemy_vector_.push_back(enemy);
}

