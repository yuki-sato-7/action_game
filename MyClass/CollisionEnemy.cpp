/**
 * @file Collision_Enemy.cpp
 * @brief �Փ˔���p�N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "CollisionEnemy.h"

/**
 * @brief �X�V�i�v���C���[�A�G�̍U���̏Փ˔��菈���j
 * @param[in] (em) �G�Ǘ��N���X
 * @param[in] (player) �v���C���[�N���X
 */
void CollisionEnemy::Update(EnemyManager& enemy_manager, Player& player)
{
	OrientedBoundingBox player_hit_obb = player.GetAttackArea()->GetOBB();
	OrientedBoundingBox death_blow_hit_obb = player.GetDeathBlowHitArea()->GetOBB();

	//�ʏ�U������
	if (player.GetPlayerState() == ATTACK_WAIT) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
			auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
			while (enemys_it != enemys.end()) {
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (player_hit_obb.Intersects(enemy_obb)) {   //���ƃG�l�~�[�̏Փ˔���𒲂ׂ�
						(*enemys_it) ->EnemyWeakDamageSwitch();
						(*enemys_it)->HpManager();
						effectmanager().HitEffectPlay(player,(*enemys_it)->GetEnemyPos());
					}
				} 
				enemys_it++;
			}
		}
	}

	//�_�b�V���U������
	if (player.GetPlayerState() == ATTACK_DASH) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
			auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
			while (enemys_it != enemys.end()) { //�G�l�~�[���Ō�܂Œ��ׂ�
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (player_hit_obb.Intersects(enemy_obb)) {   //���ƃG�l�~�[�̏Փ˔���𒲂ׂ�	
						(*enemys_it)->EnemyHeavyDamageSwitch();
						(*enemys_it)->HpManager();
						effectmanager().HitEffectPlay(player, (*enemys_it)->GetEnemyPos());
					}
				}
				enemys_it++; //���̃G�l�~�[�𒲂ׂ�
			}
		}
	}

	//�K�E�Z����
	if (player.GetPlayerState() == DEATHBLOW) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
			auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
			while (enemys_it != enemys.end()) { //�G�l�~�[���Ō�܂Œ��ׂ�
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (death_blow_hit_obb.Intersects(enemy_obb)) {   //���ƃG�l�~�[�̏Փ˔���𒲂ׂ�	
						(*enemys_it)->DeathBolwHit();
					}
				}
				enemys_it++; //���̃G�l�~�[�𒲂ׂ�
			}
		}
	}

	//�G�̍U������
	if (player.GetDamageFlag() == false) {
		auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
		auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
		while (enemys_it != enemys.end()) {
			if ((*enemys_it)->GetEnemyHitFlag() == false) {
				if ((*enemys_it)->GetAttackFlag() == true) {
					OrientedBoundingBox player_obb = player.GetPlayerHitArea()->GetOBB(); //���̃I�u�W�F�N�g�����炤
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetAttackModel()->GetOBB();
					if (player_obb.Intersects(enemy_obb)) {
						player.PlayerDamageSwitch((*enemys_it)->GetEnemyModel()->GetFrontVector(), (*enemys_it));
						break;
					}
				}
			}
			enemys_it++;
		}
	}
}