/**
 * @file Enemy.h
 * @brief 敵クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once

class Player;

#include "Player.h"
#include "SeManager.h"
#include "Ground.h"
#include "EnemyManager.h"
#include "Enum.h"
#include "EffeksserManager.h"


class Enemy
{
public:

	/**
 　　* @brief 敵クラスを初期化する
     * @param[in] (player) プレイヤークラス
 　　* @param[in] (enemy_pos_) メインシーンで設定した敵の座標
 　　* @return 常にtrue
 　　*/
	virtual bool Initialize(Player& player,Vector3& enemy_pos_);

	/**
　　 * @brief 更新(移動、状態遷移、衝突検出)
 　　* @param[in] (player) プレイヤークラス
 　　* @param[in] (ground) 背景座標管理クラス
 　　* @param[in] (enemy_pos_) 敵管理クラス
 　　*/
	virtual void Update(Player& player,Ground& ground, EnemyManager& em);

	/**
 　　* @brief 待機状態からプレイヤーとの処理を測り、次の状態を決定するための処理
 　　*/
	virtual void Draw();

	/**
　　 * @brief ダッシュ攻撃のダメージ状態に遷移させる
 　　*/
	void EnemyHeavyDamageSwitch();

	/**
 　　* @brief 通常攻撃のダメージ状態に遷移させる
 　　*/
	void EnemyWeakDamageSwitch();

	/**
　　 * @brief　敵の状態を切り替えるための処理
 　　* @param[in] (new_state) 敵の状態
 　　*/
	void SetEnemyState(int new_state);

	/**
　　 * @brief　移動ジャンプの状態の処理
 　　*/
	void EnemyMove();

	/**
     * @brief　待機状態からプレイヤーとの処理を測り、次の状態を決定するための処理
     * @param[in] (enemy_manager) 敵管理クラス
     */
	void EnemyNormalSwitch(EnemyManager& enemy_manager);

	/**
     * @brief　通常攻撃を受けた後のダメージ状態
     */
	void WeakDamageState();

	/**
     * @brief　ダッシュ攻撃を受けた後のダメージ状態
     * @param[in] (enemy_manager) 敵管理クラス
     */
	void HeavyDamageState(EnemyManager& enemy_manager);

	/**
     * @brief パンチ攻撃状態
     */
	void PunchState();

	/**
     * @brief 通常攻撃状態
     * @param[in] (enemy_manager) 敵全体管理クラス
     */
	void AttackState(EnemyManager& enemy_manager);

	/**
     * @brief　敵が待機状態の際の処理
     * @param[in] (enemy_manager) 敵管理クラス
     */
	void WaitState(EnemyManager& enemy_manager);

	/**
     * @brief　ダメージを受けた後の、サイドジャンプをするために敵同士の距離を測る処理
     * @param[in] (enemy_manager) 敵管理クラス
     */
	void EnemyDist(EnemyManager& enemy_manager);

	/**
     * @brief 残りHPを管理する HPが無くなったら爆発エフェクトを出す
     */
	void HpManager();

	/**
     * @brief 必殺技を受けた後に爆発エフェクトを出す
     */
	void DeathBolwHit();

	/**
     * @brief　ダメージを受けた後の、左サイドジャンプをするための処理
     */
	void LeftSideJumpState();

	/**
     * @brief　ダメージを受けた後の、右サイドジャンプをするための処理
     */
	void RightSideJumpState();

	/**
     * @brief　ダメージを受けた後の、後ろサイドジャンプをするための処理
     */
	void BackSideJumpState();

	/**
     * @brief　ダメージを受けた後のジャンプを左右、後ろに決定するための処理
     * @param[in] (enemy_manager) 敵管理クラス
     */
	void SideJumpState(EnemyManager& eenemy_managerm);

 	/**
     * @brief　敵の衝突範囲を設定する
     */
	void HitAreaControl();

	/**
	 * @brief　パンチ状態の攻撃範囲を設定する
	 * @param[in] (enemy_manager) 敵管理クラス
	 */
	void PunchAreaControl(EnemyManager& enemy_manager);

	/**
     * @brief 壁との距離を測定する
     * @param[in] (ground) 背景ステージ管理クラス
     */
	void GroundDist(Ground& ground);

	//敵のHP取得する
	int GetEnemyHp() { return enemy_hp_; };

	//敵がダメージを受けているか取得する
	bool GetEnemyHitFlag() { return hit_flag_; }

	//敵の状態を取得する
	int GetEnemyState(){ return enemy_state_; }

	//敵の座標取得
	Vector3 GetEnemyPos() { return enemy_pos_; }

	//敵の情報取得
	ANIMATIONMODEL GetEnemyModel() { return enemy_; }

	//敵の衝突範囲取得
	MODEL GetHitModel() { return hit_enemy_ob_; }

	//攻撃範囲
	MODEL GetAttackModel() { return punch_; }

	//攻撃しているか取得
	bool GetAttackFlag() { return attack_flag_; };

	//生存しているか
	bool GetSurvialFlag() { return survival_flag_; }

private:
	// 定数
	const float kAdjustAdvanceTimeSpeed     = (1.0f/60.0f);     //アニメーションの再生速度調整
	const float kAdjustGroundDist           = 100.0f;           //地面までの距離調整
	const float kAdjustEnemyRota            = 90.0f;            //敵の向き調整
	const float kAdjustPunchArea            = 25.0f;            //パンチ攻撃の座標調整
	const float kAdjustHitArea              = 25.0f;            //衝突範囲の座標調整
	const float kAdjustWaitTimeEnd          = (100.0f/60.0f);   //待機状態終了時間
	const float kAdjustEnemyDistPosY        = 20.0f;            //敵同士の距離を測る際のY座標調整
	const float kAdjustEnemyDistFrontVec    = 10.0f;            //敵同士の距離を測る際のレイの調整
	const float kAdjustSideJumpMaxDist      = 800.0f;           //サイドジャンプの際の敵同士の距離
	const float kAdjustGroundMaxDist        = 300.0f;           //壁までの移動できるMAX距離

	const float kAdjustJumpTimeEnd          = (72.0f/60.0f);    //ジャンプ状態終了時間
	const float kAdjustJumpTimeRise         = (38.0f / 60.0f);  //ジャンプ状態（上昇中）
	const float kAdjustJumpTimeFall         = (55.0f / 60.0f);  //ジャンプ状態（下降中）
	const float kAdjustJumpTimeTakeOff      = (22.0f / 60.0f);  //ジャンプ状態（上昇前）
	const float kAdjustJumpMoveX            = 3.0f;             //ジャンプ移動距離（X）
	const float kAdjustJumpMoveY            = 1.01f;            //ジャンプ移動距離（Y）
	const float kAdjustJumpMoveZ            = 1.5f;             //ジャンプ移動距離（Z）

	const float kAdjustMoveDist             = 120.0f;           //移動状態に入る距離
	const float kAdjustAttackDist           = 80.0f;            //通常攻撃状態に入る距離

	const float kAdjustHeavyDamagePos       = 60.0f;            //ダッシュ攻撃ダメージの座標調整
	const float kAdjustHeavyDamageTimeEnd   = (229.0f/60.0f);   //ダッシュ攻撃ダメージ状態終了時間

	const float kAdjustWeakDamagePos        = 2.0f;             //通常攻撃ダメージの座標調整
	const float kAdjustWeakDamageTimeEnd    = (39.0f / 60.0f);  //通常攻撃ダメージ状態終了時間
	const float kAdjustAttackTimeEnd        = (250.0f / 60.0f); //通常攻撃状態終了時間
	const float kAdjustAttackTimeOn         = (190.0f / 60.0f); //通常攻撃（攻撃有効）時間
	const float kAdjustAttackPosZ           = 1.5f;             //通常攻撃の座標調整(Z)

	const float kAdjustPunchTimeEnd         = (100.0f / 60.0f); //パンチ攻撃状態終了時間
	const float kAdjustPunchTimeOff         = (79.0f / 60.0f);  //パンチ攻撃（攻撃無効）時間
	const float kAdjustPunchTimeOn          = (50.0f / 60.0f);  //パンチ攻撃（攻撃有効）時間
	const float kAdjustPunchTimeReserve     = (46.0f / 60.0f);  //パンチ攻撃（準備）時間
	const float kAdjustPunchPosZ            = 0.5f;             //パンチ攻撃の座標調整(Z)

	const float kAdjustDamageCount          = 1.0f;             //ダメージの加算
	const float kAdjustDeathBlowDamageCount = 5.0f;             //必殺技ダメージの加算

	const float kAdjustShadowScale          = 0.5f;             //影の大きさ
	const Vector3 kAdjustShadowLightPos     = Vector3(-10.0f, -100.0f, 10.0f);  //影を投影するためのライトの座標
	const Vector3 kAdjustShadowPos          = Vector3(0.0f, 0.1f, 0.0f);        //影の座標
	

	//!敵のアニメーションモデル
	ANIMATIONMODEL enemy_;

	//!敵の座標
	Vector3 enemy_pos_;

	//!敵の衝突判定用モデル
	MODEL hit_enemy_ob_;

	//!敵の衝突判定領域
	OrientedBoundingBox enemy_obb_; 

	//!敵の状態
	int enemy_state_;
	
	//!パンチの衝突範囲モデル
	MODEL punch_;

	//!プレイヤーの座標
	Vector3 player_pos_;

	//!SEを鳴らしたか
	bool se_flag_;

	//!ダウン状態で攻撃を当てないため falseで攻撃が当たる状態
	bool hit_flag_;

	//!床モデル
	MODEL ground_;

	//!衝突判定用壁モデル
	MODEL ground_wall_;

	//!倒されたどうか
	bool death_flag_;

	//!敵とプレイヤーの距離
	float player_dist_;

	//!床までの距離
	float ground_down_dist_;

	//!プレイヤーに向けるかどうか　trueで向ける
	bool rotation_flag_;

	//!敵のY座標
	float groud_dist_;
 
	//!敵がダメージを受けた回数
	int enemy_hp_;

	//!ジャンプSEを鳴らしたか
	bool move_se_flag_;

	//!パンチSEを鳴らしたか
	bool punch_se_flag_;

	//!仲間との距離
	float wait_dist_;

	//!敵の総HP
	int hp_max_;

	//!敵が攻撃中か
	bool attack_flag_;

	//!敵が生存しているか
	bool survival_flag_;

	//!hitのseを鳴らしたか
	bool hit_se_flag_;

	//!ダメージ後にジャンプするための障害物との距離（右方向）
	float right_side_dist_;

	//!ダメージ後にジャンプするための障害物との距離障害物との距離（左方向）
	float left_side_dist_;

	//!ダメージ後にジャンプするための障害物との距離障害物との距離（後ろ方向）
	float back_dist_;

	//!前方方向にいる敵との距離１
	float forward_1_dist_;

	//!前方方向にいる敵との距離１
	float forward_2_dist_;

	//!左にジャンプ可能か判断
	bool left_side_jump_flag_;

	//!右にジャンプ可能か判断
	bool right_side_jump_flag_;

	//!後ろにジャンプ可能か判断
	bool back_side_jump_flag_;

	//!右にジャンプ可能か判断 
	bool side_jump_flag_;

	//!ダメージ後にジャンプしたか判断
	float ground_long_dist_;

	//!壁までの距離（前方向）
	float enemy_forward_direction_;

	//!壁までの距離（後ろ方向）
	float enemy_back_direction_;

	//!壁までの距離（左方向）
	float enemy_left_direction_;

	//!壁までの距離（右方向）
	float enemy_right_direction_;

	//!移動が可能かどうか（前方向）
	bool forward_move_flag_;

	//!移動が可能かどうか（後ろ方向）
	bool back_move_flag_;

	//!移動が可能かどうか（左方向）
	bool left_move_flag_;

	//!移動が可能かどうか（右方向）
	bool right_move_flag_;

	//!仲間との距離（左方向）
	float left_dist_max_;

	//!仲間との距離（右方向）
	float right_dist_max_;

	//!プレイヤーの向いている方向
	Vector3 player_angle_;
};