/**
 * @file EnemyManager.h
 * @brief 敵管理クラスヘッダーファイル
 * @author 佐藤雄希
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
	 * @brief 敵管理クラスを初期化する
	 * @return 常にtrue
	 */
	virtual bool Initialize();

	/**
	 * @brief 敵管理をアップデートする
	 * @param[in] (player) プレイヤークラス
	 * @param[in] (ground) ステージ背景管理クラス
	 * @param[in] (enemy_manager) 敵管理クラス
	 */
	virtual void Update(Player& player, Ground& ground);

	/**
	 * @brief 敵管理クラスを描画する
	 */
	virtual void Draw();

	/**
	 * @brief 敵を生成する
	 * @param[in] (player) プレイヤークラス
	 * @param[in] (enemy_pos) 敵の生成座標
	 */
	void CreateEnemy(Player& player ,Vector3& enemy_pos);

	//敵の情報取得
	std::vector< std::shared_ptr<Enemy> >& GetEnemys() { return enemy_vector_; }

private:
	//! 敵の情報
	std::vector< std::shared_ptr<Enemy> > enemy_vector_;
};