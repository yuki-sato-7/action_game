/**
 * @file CameraMain.h
 * @brief 衝突判定用管理クラスヘッダーファイル
 * @author 佐藤雄希
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
	 * @brief 更新（プレイヤー、敵の攻撃の衝突判定処理）
	 * @param[in] (em) 敵管理クラス
	 * @param[in] (player) プレイヤークラス
	 */
	virtual void Update(EnemyManager& em, Player& player);
};
