/**
 * @file Enum.h
 * @brief 定数管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once

 /**
  * @enum Enum
  * プレイヤーの状態
  */
enum PLAYER_STATE {
	//!待機モーション
	WAIT,
	//!歩きモーション
	WALK,
	//!走りモーション
	RUN,
	//!ダッシュモーション
	DASH,
	//!ダメージモーション
	DAMAGE,
	//!攻撃（待機）モーション
	ATTACK_WAIT,
	//!攻撃（ダッシュ）モーション
	ATTACK_DASH,
	//!攻撃（待機）戻りモーション
	ATTACK_WAITBACK,
	//!攻撃（ダッシュ）戻りモーション
	ATTACK_DASHBACK,
	//!倒れモーション
	DEATH,
	//!必殺技モーション
	DEATHBLOW,
	//!必殺技戻りモーション
	DEATHBLOW_BACK,
	//!回避モーション
	STEP,
	//!タイムオーバー状態
	TIME_OVER,
	//!ゲームクリア状態
	GAME_CLEAR
};

/**
 * @enum Enum
 * 無敵状態
 */
enum Player_Invincible {
	//!無敵状態
	Invincible,
	//!非無敵状態
	Not_invincible
};

/**
 * @enum Enum
 * 敵の状態
 */
enum Enemy_STATE {
	//!通常状態
	WAITING,
	//!攻撃モーション
	ATTACK,
	//!歩きモーション
	HEAVY_DAMAGE,
	//!走りモーション
	WEAK_DAMAGE,
	//!移動モーション
	MOVE,
	//!通常状態
	END_WAITING,
	//!パンチモーション
	PUNCH,
	//!待機モーション（ゲーム終了）
	SIDE_JUMP,
	//!通常状態
	NORMAL,
	//!タイムオーバー状態
	TIME_OVER_,
	//!プレイヤー死亡状態
	PLAYER_DEATH_
};

/**
 * @enum Enum
 * HPゲージの状態
 */
enum HpGauge_STATE {
	//!ダメージ5回
	RED_1,
	//!ダメージ4回
	RED_2,
	//!ダメージ3回
	YELLOW_1,
	//!ダメージ2回
	YELLOW_2,
	//!ダメージ1回
	GREEN_1,
	//!ダメージ0回
	GREEN_2
};

/**
 * @enum Enum
 * 文字の濃度
 */
enum Alfa_STATE {
	//!文字の透明度0%
	ALPHA_MIN,
	//!文字の透明度100%
	ALPHA_MAX
};

/**
 * @enum Enum
 * Observerの引数
 */
enum Observer_STATE {
	//!タイムオーバー状態
	TIME_OVER_STATE,
	//!ゲームオーバー状態
	GAME_OVER_STATE,
	//!ゲームクリア状態
	GAME_CLEAR_STATE,
};