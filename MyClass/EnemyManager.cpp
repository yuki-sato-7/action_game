/**
 * @file EnemyManager.cpp
 * @brief 敵全体管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "EnemyManager.h"

/**
 * @brief 敵全体管理クラスを初期化する
 * @return 常にtrue
 */
bool EnemyManager::Initialize()
{
	return true;
}

/**
 * @brief 更新（HPが無くなったら敵を消す）、
 * @param[in] (player) プレイヤー管理クラス
 * @param[in] (ground) ステージ背景管理クラス
 * @param[in] (enemy_manager) 敵全体管理クラス
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
		game_clear_subject_.notifyObservers(GAME_CLEAR_STATE);  //ゲームクリアになったことをオブザーバーに通知
	}
}

/**
 * @brief 敵全体管理クラスを描画する
 */
void EnemyManager::Draw()
{
	for (int i = 0; i < enemy_vector_.size(); i++)
		enemy_vector_[i]->Draw();
}

/**
 * @brief 敵を生成する
 * @param[in] (player) プレイヤー管理クラス
 * @param[in] (enemy_pos) 敵の生成座標
 */
void EnemyManager::CreateEnemy(Player& player,Vector3& enemy_pos_)
{
	std::shared_ptr<Enemy> enemy(new Enemy());
	enemy->Initialize(player,enemy_pos_);
	enemy_vector_.push_back(enemy);
}

