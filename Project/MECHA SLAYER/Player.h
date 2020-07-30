/**
 * @file Player.h
 * @brief プレイヤークラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once

class Enemy;
class CameraMain;

#include "Ground.h"
#include "EffeksserManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "TimeManager.h"
#include "Enum.h"

class Player
{
public:

	/**
 　　* @brief　プレイヤークラスを初期化する
 　　* @return 常にtrue
 　　*/
	virtual bool Initialize();

	/**
 　　*  * @brief 更新(移動、状態遷移、衝突検出、壁ズリ、無敵状態)
 　　* @param[in] (ground) 背景ステージクラス
 　　* @param[in] (camera_main) カメラクラス
 　　* @param[in] (enemy_manager) 敵管理クラス
 　　* @param[in] (pad_buffer) ゲームパッドの状態取得情
 　　* @param[in] (pad_state) ゲームパッドの状態取得
 　　*/
	virtual void Update(Ground& ground,CameraMain& camera_main, EnemyManager& em, GamePadBuffer&pad_buffer,GamePadState&pad_state);
	
	/**
 　　* @brief プレイヤーを描画
 　　*/
	virtual void Draw();

	/**
　　 * @brief プレイヤーの状態を切り替えるための処理
 　　* @param[in] (new_state) プレイヤーの状態
 　　*/
	void SetPlayerState(int new_state);

	/**
     * @brief 回避状態
     */
	void StepState();

	/**
　　 * @brief ダッシュ状態
 　　* @param[in] (camera_main) カメラクラス
 　　* @param[in] (pad_buffer) ゲームパッドの状態取得情報
 　　* @param[in] (pad_state) ゲームパッドの状態取得
 　　*/
	void DashState(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	/**
 　　* @brief ダッシュ攻撃状態
 　　*/
	void AttackDashState();

	/**
 　　* @brief ダッシュ攻撃（戻り）状態
 　　*/
	void AttackDashBackState();

	/**
     * @brief ダメージ状態
     */
	void DamageState();

	/**
     * @brief 攻撃状態
     */
	void AttackWaitState();

	/**
     * @brief 攻撃（戻り）状態
     */
	void AttackWaitBackState();

	/**
     * @brief 死亡状態
     */
	void DeathState();

	/**
     * @brief 必殺技状態
     */
	void DeathblowState();

	/**
     * @brief 必殺技（戻り）状態
     */
	void DeathblowBackState();
	
	/**
     * @brief ダメージ状態に遷移させる
     * @param[in] (knockbackVector) カメラ管理クラス
     * @param[in] (enemy) 攻撃を受けた敵の情報
     */
	void PlayerDamageSwitch(Vector3& knockbackVector, std::shared_ptr<Enemy> enemy_);

	/**
     * @brief 通常状態にから次の状態に遷移させる
     * @param[in] (camera_main) カメラクラス
     * @param[in] (pad_buffer) ゲームパッドの情報取得
     * @param[in] (pad_state) ゲームパッドの情報取得
     */
	void PlayerMoveSwitch(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	/**
 　　* @brief プレイヤーの衝突範囲を設定する
 　　*/
	void HitAreaControl();

	/**
     * @brief ダメージを受けた後の無敵状態を管理
     */
	void InvincibleTime();

	/**
 　　* @brief プレイヤーの攻撃範囲を設定する
 　　*/
	void AttackAreaControl();

	//プレイヤーの座標取得
	Vector3 GetPlayerPos() { return player_->GetPosition(); }

	//プレイヤーのモデル情報取得
	ANIMATIONMODEL GetPlayerModel() { return player_; }

	//敵の攻撃有効範囲の取得
	MODEL GetPlayerHitArea() { return hit_area_; }

	//必殺技の攻撃範囲の取得
	MODEL GetDeathBlowHitArea() { return death_blow_area_; };

	//プレイヤーの攻撃範囲の取得
	MODEL GetAttackArea() { return attack_area_; }

	//プレイヤーの状態を取得する関数
	int GetPlayerState() { return player_state_; }

	//プレイヤーが攻撃しているか
	bool GetHitFlag() { return player_hit_flag_; };

	//敵の攻撃が当たっているか
	bool GetDamageFlag() { return damage_flag_; };

	//ゲームオーバー状態か
	bool GameOverFlag() { return game_over_flag_; };

	//ゲーム終了状態か
	bool GameEndFlag() { return operation_flag_; };

	//プレイヤー用の影
	inline Matrix Create_Shadow_Matrix(const D3DLIGHTTYPE light_type, const Vector3& light,
		const Vector3& pos, const Vector3& shadow_offset,
		const Vector3& normal);



	float GetDist() { return wall_dist_min_; };

private:
	// 定数
	const float kAdjustAdvanceTimeSpeed      = (1.0f / 60.0f);    //アニメーションの再生速度調整
	const float kAdjustGroundDistRay         = 100.0f;            //床までの距離を測る際のレイの調整
	const float kAdjustGroundDistPosY        = 20.0f;             //壁までの距離を測る際のY座標調整
	const float kAdjustGroundMaxDist         = 100.0f;            //壁までの移動できるMAX距離
	const float kAdjustGroundWallMaxDist     = 50.0f;             //壁ズリするMAX距離
	const float kAdjustEnemydWallMaxDist     = 20.0f;             //壁ズリするMAX距離（敵）
	const float kAdjustEnemyWallDistPosY1    = 10.0f;             //壁ズリするの距離を測る際のY座標調整
  	const float kAdjustEnemyWallDistPosY2    = 100.0f;             //壁ズリするの距離を測る際のY座標調整（敵のジャンプ状態で当たるように調整）
	const float kAdjustEnemyMinxDist         = 8.0f;              //壁までの移動できなくなるMIN距離Ｔ（敵）
	const float kAdjustGroundWallSpeed       = 1.0f;              //壁ズリのスピード
	const float kAdjustAttackArea            = 25.0f;             //攻撃の座標調整
	const float kAdjustPlayerRota            = 180.0f;            //プレイヤーの向き調整
	const float kAdjustPlayerMove            = 0.2f;              //プレイヤーの移動量調整（ダッシュ）
	const float kAdjustPlayerRunMove         = 0.5f;              //プレイヤーの移動量調整（走り）
	const float kAdjustPlayerWalkMove        = 1.0f;              //プレイヤーの移動量調整（歩き）
	const float kAdjustPlayerWalkPadAngle    = 0.5f;              //プレイヤーの歩きにするゲームパッドの角度

	const float kAdjustAttackDashTimeEnd     = (51.0f / 60.0f);   //ダッシュ攻撃状態終了時間
	const float kAdjustAttackDashTimeOff     = (21.0f / 60.0f);   //ダッシュ攻撃（攻撃無効）時間
	const float kAdjustAttackDashTimeOn      = (10.0f / 60.0f);   //ダッシュ攻撃（攻撃有効）時間
	const float kAdjustAttackDashBackTimeEnd = (39.0f / 60.0f);   //ダッシュ攻撃（戻り）状態終了時間

	const float kAdjustStepTimeEnd           = (58.0f / 60.0f);   //回避状態終了時間
	const float kAdjustStepTimeMove          = (41.0f / 60.0f);   //回避（移動）状態終了時間
	const float kAdjustStepMoveZ             = -3.0f;             //回避状態移動(Z)

	const float kAdjustAttakWaitTimeEnd      = (41.0f / 60.0f);  //攻撃状態終了時間
	const float kAdjustAttakWaitTimeOff      = (35.0f / 60.0f);   //攻撃（攻撃無効）時間
	const float kAdjustAttakWaitTimeOn       = (17.0f / 60.0f);   //攻撃（攻撃有効）時間
	const float kAdjustAttakWaitTimeReserve  = (8.0f / 60.0f);    //攻撃（準備）時間
	const float kAdjustAttakWaitMoveZ        = 2.5f;              //攻撃状態移動量調整(Z)

	const float kAdjustAttakDamageTimeEnd    = (60.0f / 60.0f);   //ダメージ状態状態終了時間

	const float kAdjustAttakDamageMove       = 1.5f;              //ダメージ状態で敵の進行方向に移動する量

	const float kAdjustDeathTimeEnd          = (116.0f / 60.0f);  //死亡状態状態終了時間
	
	const float kAdjustInvincibleTime        = 150.0f;            //無敵時間調整

	const float kAdjustDeathBlowTimeEnd      = (120.0f / 60.0f);  //必殺技状態終了時間
	const float kAdjustDeathBlowTimeOn       = (28.0f / 60.0f);   //必殺技（攻撃有効）時間
	const float kAdjustDeathBlowMoveZ        = 8.0f;              //必殺技状態移動量調整(Z)

	const float kAdjustDeathBlowBackTimeEnd  = (45.0f / 60.0f);   //必殺技（戻り）状態終了時間
	const float kAdjustDeathBlowBackTimeOn   = (10.0f / 60.0f);   //必殺技（戻り）開始時間
	const float kAdjustDeathBlowBackMoveZ    = 0.1f;              //必殺技（戻り）状態移動量調整(Z)

	const float kAdjustShadowDepth           = 0.75f;             //影の濃さ
	const Vector3 kAdjustShadowLightDist     = Vector3(0, 1500000, 150000);  //影を投影するためのライトの位置
	const Vector3 kAdjustShadowMove          = Vector3(0.0f, 1.0f, 0.0f);    //プレイヤーから影をどれくらいずらすか
	
	const int kAdjustFlashInterval           = 2.0f;                //無敵時間の際にプレイヤーを点滅させる間隔


	//!プレイヤーのモデル
	ANIMATIONMODEL player_;

	//!プレイヤーの攻撃判定用領域
	MODEL attack_area_;

	//!必殺技の衝突判定領域
	MODEL death_blow_area_;

	//!プレイヤーの衝突判定領域
	MODEL hit_area_;

	//!床モデル
	MODEL ground_;

	//!壁モデル
	MODEL ground_wall_;

	//!カメラの角度
	Quaternion camer_qt_;

	//!壁ズリ状態か
	bool ground_block_;

	//!カメラ
	CAMERA camera_;
	
	//!パッドの状態（左右）
	float pad_x_;

	//!パッドの状態（上下）
	float pad_y_;

	//!パッドの状態（左右）マッピング後
	float pad_x_x_;

	//!パッドの状態（上下）マッピング後
	float pad_y_y_;

	//!LBボタンの状態
	float lb_;

	//!攻撃判定の有無
	bool hit_judge_;

	//!敵との当たり判定
	bool collsion_judge_;

	//!プレイヤー攻撃が有効か
	bool player_hit_flag_;

	//!プレイヤーの角度
	float angle_;

	//!現在のプレイヤーのモーション
	int player_state_;

	//!床までの距離（判定用）
	float ground_dist_;

	//!壁ズリしているか
	bool wall_bolck_;	

	//!エフェクトを表示したか
	bool ef_flag_;

	//!無敵時間計測
	int invincible_time_;

	//!ダメージをくらっているか
	bool damage_flag_;

	//!敵の進行ベクトル
	Vector3 enemy_front_;

	//!敵の状態
	int enemy_state_;

	//!攻撃している敵の取得
	std::shared_ptr<Enemy> enemy_;

	//!死亡状態かどうか
	bool death_flag_;

	//!操作可能か
	bool operation_flag_;

	//!ゲームオーバーか
	bool game_over_flag_;

	//!必殺技エフェクトを表示したか
	bool deathblow_ef_flag_;

	//!SPゲージの量
	float sp_max;

	//!プレイヤーと床までのレイ
	float dist_;

	//!壁までの最も短いレイ
	float wall_dist_min_;

	//!壁までのレイ1
	float wall_dist_1_;

	//!壁までのレイ2
	float wall_dist_2_;

	//!壁ズリ後の壁までのレイ
	float wall_dist_3_;

	//!壁との平行ベクトル
	Vector3  parallel_vec_;

	//!スティックの傾け具合
	float pad_angle_;

	//!カメラの進行ベクトル（ノーマライズ）
	float camera_dist_;

	//!プレイヤーの座標
	Vector3 anime_pos_;
};