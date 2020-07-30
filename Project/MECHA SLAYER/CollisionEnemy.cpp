/**
 * @file Collision_Enemy.cpp
 * @brief 衝突判定用クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "CollisionEnemy.h"

/**
 * @brief 更新（プレイヤー、敵の攻撃の衝突判定処理）
 * @param[in] (em) 敵管理クラス
 * @param[in] (player) プレイヤークラス
 */
void CollisionEnemy::Update(EnemyManager& enemy_manager, Player& player)
{
	OrientedBoundingBox player_hit_obb = player.GetAttackArea()->GetOBB();
	OrientedBoundingBox death_blow_hit_obb = player.GetDeathBlowHitArea()->GetOBB();

	//通常攻撃判定
	if (player.GetPlayerState() == ATTACK_WAIT) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
			auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
			while (enemys_it != enemys.end()) {
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (player_hit_obb.Intersects(enemy_obb)) {   //剣とエネミーの衝突判定を調べる
						(*enemys_it) ->EnemyWeakDamageSwitch();
						(*enemys_it)->HpManager();
						effectmanager().HitEffectPlay(player,(*enemys_it)->GetEnemyPos());
					}
				} 
				enemys_it++;
			}
		}
	}

	//ダッシュ攻撃判定
	if (player.GetPlayerState() == ATTACK_DASH) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
			auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
			while (enemys_it != enemys.end()) { //エネミーを最後まで調べる
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (player_hit_obb.Intersects(enemy_obb)) {   //剣とエネミーの衝突判定を調べる	
						(*enemys_it)->EnemyHeavyDamageSwitch();
						(*enemys_it)->HpManager();
						effectmanager().HitEffectPlay(player, (*enemys_it)->GetEnemyPos());
					}
				}
				enemys_it++; //次のエネミーを調べる
			}
		}
	}

	//必殺技判定
	if (player.GetPlayerState() == DEATHBLOW) {
		if (player.GetHitFlag() == true) {
			auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
			auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
			while (enemys_it != enemys.end()) { //エネミーを最後まで調べる
				if ((*enemys_it)->GetEnemyHitFlag() == false) {
					OrientedBoundingBox enemy_obb = (*enemys_it)->GetHitModel()->GetOBB();
					if (death_blow_hit_obb.Intersects(enemy_obb)) {   //剣とエネミーの衝突判定を調べる	
						(*enemys_it)->DeathBolwHit();
					}
				}
				enemys_it++; //次のエネミーを調べる
			}
		}
	}

	//敵の攻撃判定
	if (player.GetDamageFlag() == false) {
		auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
		auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
		while (enemys_it != enemys.end()) {
			if ((*enemys_it)->GetEnemyHitFlag() == false) {
				if ((*enemys_it)->GetAttackFlag() == true) {
					OrientedBoundingBox player_obb = player.GetPlayerHitArea()->GetOBB(); //剣のオブジェクトをもらう
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