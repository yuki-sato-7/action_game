/**
 * @file Effeksser_Manager.h
 * @brief エフェクト管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "SeManager.h"

class Player;
class CameraMain;
class EnemyManager;
class Enemy;


class EffeksserManager
{
public:

	/**
	 * @brief エフェクト管理クラスを初期化する
	 * @param[in] (camara_) カメラクラス
	 * @param[in] (player_) プレイヤークラス
	 * @return 常にtrue
	 */
	virtual bool Initialize(CameraMain& camara_, Player& player_);

	/**
	 * @brief 更新（エフェクトをカメラに投影する）
	 * @param[in] (camara_) カメラクラス
	 */
	virtual void Update(CameraMain& camara_);

	/**
     * @brief エフェクトを描画する
     * @param[in] (camara_) カメラクラス
     */
	virtual void Draw(CameraMain& camara_);

	/**
     * @brief 攻撃エフェクトを再生する
     * @param[in] (player) プレイヤークラス
     */
	virtual void SlashEffectPlay(Player& player);

	/**
     * @brief ヒットエフェクトを再生する
     * @param[in] (player) プレイヤークラス
	 * @param[in] (enemy_pos) 敵の座標
     */
	virtual void HitEffectPlay(Player& player, Vector3& enemy_pos);

	/**
	 * @brief ダッシュ攻撃エフェクトを再生する
	 * @param[in] (player) プレイヤー管理クラス
	 */
	virtual void DashSlashEffectPlay(Player& player);

	/**
     * @brief 必殺技エフェクトを再生する
     * @param[in] (player) プレイヤークラス
     */
	virtual void DeathBlowEffectPlay(Player& player);

	/**
     * @brief 必殺技エフェクトをプレイヤーに沿って移動させる
     * @param[in] (player) プレイヤークラス
     */
	virtual void DeathBlowEffectMove(Player& player);

	/**
	 *@brief 敵の爆発エフェクトを再生する
	 * @param[in](enemy_pos) 死亡した敵の座標
     */
	virtual void ExplosionPlay(Vector3 enemy_pos);

	/**
     * @brief 必殺技エフェクトを停止する
     */
	virtual void DeathBlowEffectStop();

	// シングルトンインスタンスの取得
	static EffeksserManager& GetInstance()
	{
		static EffeksserManager effect_manager;
		return effect_manager;
	}

private:
	// 定数
	const float kEffectAdjustAngle          = 45.0f;    //エフェクトの角度調整
	const float kEffectAdjustPos            = 60.0f;    //攻撃、ヒットエフェクトの座標調整
	const float kEffectAdjustDashSlashPos   = 30.0f;    //ダッシュ攻撃の座標調整
	const float kEffectAdjustScale          = 8.0f;     //攻撃、ヒットエフェクトの大きさ調整
	const float kEffectAdjustDeathBlowPos   = 30.0f;    //必殺技エフェクトの座標調整
	const float kEffectAdjustDeathBlowScale = 6.0f;     //必殺技エフェクトの大きさ調整
	const float kEffectAdjustDeathBlowMove  = 8.0f;     //必殺技エフェクトの移動量調整
	const float kEffectAdjustExplosioScale  = 20.0f;    //爆発エフェクトの大きさ調整



	//!攻撃エフェクト
	EFFEKSEER slash_effect_;

	//!ダッシュ攻撃エフェクト
	EFFEKSEER dash_slash_effect_;

	//!爆発エフェクト
	EFFEKSEER explosion_effect_;

	//!必殺技エフェクト
	EFFEKSEER death_blow_;

	//!ヒットエフェクト
	EFFEKSEER hit_effect_;

	//!必殺技ID
	int death_blow_effect_effect_id_;

	//!エフェクトの向き
	Vector3 effect_dir_;


	EffeksserManager() {} 

	EffeksserManager(const EffeksserManager&);
	EffeksserManager& operator=(const EffeksserManager&);
};

inline EffeksserManager& effectmanager() { return EffeksserManager::GetInstance(); }



