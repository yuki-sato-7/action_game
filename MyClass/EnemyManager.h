/**
 * @file EnemyManager.h
 * @brief 敵管理クラスヘッダーファイル
 * @author 佐藤雄希
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

	/**
　　 * @brief オブザーバーに新たなオブザーバーを追加
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void AddObserver(IObserver* observer)
	{
		game_clear_subject_.addObserver(observer);
	}

	/**
　　 * @brief オブザーバーのリストからオブザーバーを削除
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void RemoveObserver(IObserver* observer)
	{
		game_clear_subject_.removeObserver(observer);
	}

	/**
　　 * @brief リストに登録されているオブザーバーの変化を通知
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void AllDelteObserver(IObserver* observer)
	{
		game_clear_subject_.alldelteObservers();
	}

	//敵の情報取得
	std::vector< std::shared_ptr<Enemy> >& GetEnemys() { return enemy_vector_; }

private:
	//! 敵の情報
	std::vector< std::shared_ptr<Enemy> > enemy_vector_;

	Subject game_clear_subject_;
};