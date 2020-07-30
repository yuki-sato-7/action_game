/**
 * @file CameraMain.cpp
 * @brief �J�����N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "CameraMain.h"

/**
 * @brief �J�����N���X������������
 * @param[in] (player) �v���C���[�N���X
 * @return ���true
 */
bool CameraMain::Initialize(Player& player)
{
	//�J�����̐ݒ�
	camera_->SetPerspectiveFieldOfView(45.0, 16.0f / 9.0f, 1.0f, 10000.0f);
	camera_->SetLookAt(camera_pos_, player_pos_ + Vector3(0, 30, 0), Vector3_Up);	
	GraphicsDevice.SetCamera(camera_);

	//�e�ϐ��̏�����
	camera_dist_ = 30.0f;
	angle_       = 0.0f;
	player_dist_ = 110.0f;

	return true;
}

/**
 * @brief �X�V(�ړ��A���W�ݒ�)
 * @param[in] (player) �v���C���[�N���X
 * @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾
 * @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
 */
void CameraMain::Update(Player& player, GamePadBuffer& pad_buffer, GamePadState& pad_state)
{
	//�v���C���[�̍��W
	player_pos_ = player.GetPlayerPos();

	//�Q�[���p�b�h�̊p�x����
	pad_x_ = -(((float)pad_state.X3 - Axis_Center) / (Axis_Max - Axis_Center));
	pad_y_ = (((float)pad_state.Y2 - Axis_Center) / (Axis_Max - Axis_Center));

	//�p�b�h�����ɓ|�������̃J�����̏�����ړ�
	if (pad_x_ < 0 ) {
		if (camera_dist_ <= kCameraMoveMaxX) {
			camera_dist_ += kCameraMoveX;
		}
	}

	//�p�b�h����ɓ|�������̃J�����̉������ړ�
	if (pad_x_ > 0) {		
		if (camera_dist_ >= kCameraMoveMinX) {
			camera_dist_ -= kCameraMoveX;
		}
	}

	//�p�b�h�����ɓ|�������̃J�����̍������ړ�
	if (pad_y_ < 0.0f) {
		angle_ += kCameraMoveY;
	}

	//�p�b�h���E�ɓ|�������̃J�����̉E�����ړ�
	if (pad_y_ > 0.0f) {
		angle_ -= kCameraMoveY;
	}

	//�J�����̍��W�ݒ�
	camera_pos_ = Vector3(MathHelper_Cos(angle_) * player_dist_ + player_pos_.x, camera_dist_, MathHelper_Sin(angle_) * player_dist_ + player_pos_.z);
	camera_->SetLookAt(camera_pos_, player_pos_ + Vector3(0.0f, kCameraAdjustY, 0.0f), Vector3_Up);
	camera_.SetFieldOfViewY(kAdjustViewAngle);
	camera_.SetPosition(camera_pos_);

	//�J�����̍ăZ�b�g
	GraphicsDevice.SetCamera(camera_);
}
