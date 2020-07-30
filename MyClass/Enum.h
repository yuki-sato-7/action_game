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
	//待機モーション
	WAIT,
	//歩きモーション
	WALK,
	//走りモーション
	RUN,
	//ダッシュモーション
	DASH,
	//ダメージモーション
	DAMAGE,
	//攻撃（待機）モーション
	ATTACK_WAIT,
	//攻撃（ダッシュ）モーション
	ATTACK_DASH,
	//攻撃（待機）戻りモーション
	ATTACK_WAITBACK,
	//攻撃（ダッシュ）戻りモーション
	ATTACK_DASHBACK,
	//倒れモーション
	DEATH,
	//必殺技モーション
	DEATHBLOW,
	//必殺技戻りモーション
	DEATHBLOW_BACK,
	//必殺技戻りモーション
	STEP
};

/**
 * @enum Enum
 * 無敵状態
 */
enum Player_Invincible {
	Invincible,
	Not_invincible
};

/**
 * @enum Enum
 * 敵の状態
 */
enum Enemy_STATE {
	//移動モーション
	MOVE,
	DA,
	//パンチモーション
	PUNCH,
	//待機モーション
	WAITING,
	//パンチモーション
	SIDE_JUMP,
	//走りモーション
	WEAK_DAMAGE,
	///歩きモーション
	HEAVY_DAMAGE,
	//攻撃モーション
	ATTACK,
	//必殺技ダメージモーション
	DEATHBLOW_DAMAGE,
	BREAK,
	//NORMAL,
	NORMAL
};

/**
 * @enum Enum
 * HPゲージの状態
 */
enum Gauge_STATE {
	RED_1,
	RED_2,
	YELLOW_1,
	YELLOW_2,
	GREEN_1,
	GREEN_2
};

/**
 * @enum Enum
 * 文字の濃度
 */
enum Alfa_STATE {
	ALFA_MIN,
	ALFA_MAX
};