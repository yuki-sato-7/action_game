/**
 * @file CameraMain.h
 * @brief カメラクラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once 
#include "ESGLib.h"
#include "Player.h"

class CameraMain
{
public:

	/**
     * @brief カメラクラスを初期化する
     * @param[in] (player) プレイヤー管理クラス
     * @return 常にtrue
     */
	virtual bool Initialize(Player& player);

	/**
     * @brief 更新(移動、座標設定)
     * @param[in] (player) プレイヤークラス
     * @param[in] (pad_buffer) ゲームパッドの状態取得
     * @param[in] (pad_state) ゲームパッドの状態取得
     */
	virtual void Update(Player& player, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	//カメラの取得
	CAMERA GetCamera() { return camera_; };

	//カメラ座標の取得
	Vector3 GetCameraPos() { return camera_pos_; };

private:
	// 定数
	const float kAdjustViewAngle = 45.0f;  //カメラの視野角
	const float kCameraAdjustY   = 30.0f;  //カメラのY座標調整
	const float kCameraMoveX     = 4.0f;   //カメラの移動量（X）
	const float kCameraMoveMaxX  = 194.0f; //カメラの移動量の最大（X）
	const float kCameraMoveMinX  = 7.0f;   //カメラの移動量の最小（X）
	const float kCameraMoveY     = 2.5f;   //カメラの移動量（Y）
	
	//!カメラ
	CAMERA camera_;
	
	//!カメラの座標
	Vector3 camera_pos_;

	//!カメラの角度
	float angle_;

	//!カメラの移動距離
	float camera_dist_;

	//!プレイヤーの座標
	Vector3   player_pos_;

	//!ゲームパッドを角度
	float pad_x_;
	float pad_y_;

	//!プレイヤーからカメラを離す距離
	float player_dist_;
};