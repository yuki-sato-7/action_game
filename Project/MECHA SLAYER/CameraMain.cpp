/**
 * @file CameraMain.cpp
 * @brief カメラクラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "CameraMain.h"

/**
 * @brief カメラクラスを初期化する
 * @param[in] (player) プレイヤークラス
 * @return 常にtrue
 */
bool CameraMain::Initialize(Player& player)
{
	//カメラの設定
	camera_->SetPerspectiveFieldOfView(45.0, 16.0f / 9.0f, 1.0f, 10000.0f);
	camera_->SetLookAt(camera_pos_, player_pos_ + Vector3(0, 30, 0), Vector3_Up);	
	GraphicsDevice.SetCamera(camera_);

	//各変数の初期化
	camera_dist_ = 30.0f;
	angle_       = 0.0f;
	player_dist_ = 110.0f;

	return true;
}

/**
 * @brief 更新(移動、座標設定)
 * @param[in] (player) プレイヤークラス
 * @param[in] (pad_buffer) ゲームパッドの状態取得
 * @param[in] (pad_state) ゲームパッドの状態取得
 */
void CameraMain::Update(Player& player, GamePadBuffer& pad_buffer, GamePadState& pad_state)
{
	//プレイヤーの座標
	player_pos_ = player.GetPlayerPos();

	//ゲームパッドの角度調整
	pad_x_ = -(((float)pad_state.X3 - Axis_Center) / (Axis_Max - Axis_Center));
	pad_y_ = (((float)pad_state.Y2 - Axis_Center) / (Axis_Max - Axis_Center));

	//パッドを下に倒した時のカメラの上方向移動
	if (pad_x_ < 0 ) {
		if (camera_dist_ <= kCameraMoveMaxX) {
			camera_dist_ += kCameraMoveX;
		}
	}

	//パッドを上に倒した時のカメラの下方向移動
	if (pad_x_ > 0) {		
		if (camera_dist_ >= kCameraMoveMinX) {
			camera_dist_ -= kCameraMoveX;
		}
	}

	//パッドを左に倒した時のカメラの左方向移動
	if (pad_y_ < 0.0f) {
		angle_ += kCameraMoveY;
	}

	//パッドを右に倒した時のカメラの右方向移動
	if (pad_y_ > 0.0f) {
		angle_ -= kCameraMoveY;
	}

	//カメラの座標設定
	camera_pos_ = Vector3(MathHelper_Cos(angle_) * player_dist_ + player_pos_.x, camera_dist_, MathHelper_Sin(angle_) * player_dist_ + player_pos_.z);
	camera_->SetLookAt(camera_pos_, player_pos_ + Vector3(0.0f, kCameraAdjustY, 0.0f), Vector3_Up);
	camera_.SetFieldOfViewY(kAdjustViewAngle);
	camera_.SetPosition(camera_pos_);

	//カメラの再セット
	GraphicsDevice.SetCamera(camera_);
}
