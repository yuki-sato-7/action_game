/**
 * @file CameraMain.h
 * @brief �J�����N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once 
#include "ESGLib.h"
#include "Player.h"

class CameraMain
{
public:

	/**
     * @brief �J�����N���X������������
     * @param[in] (player) �v���C���[�Ǘ��N���X
     * @return ���true
     */
	virtual bool Initialize(Player& player);

	/**
     * @brief �X�V(�ړ��A���W�ݒ�)
     * @param[in] (player) �v���C���[�N���X
     * @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾
     * @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
     */
	virtual void Update(Player& player, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	//�J�����̎擾
	CAMERA GetCamera() { return camera_; };

	//�J�������W�̎擾
	Vector3 GetCameraPos() { return camera_pos_; };

private:
	// �萔
	const float kAdjustViewAngle = 45.0f;  //�J�����̎���p
	const float kCameraAdjustY   = 30.0f;  //�J������Y���W����
	const float kCameraMoveX     = 4.0f;   //�J�����̈ړ��ʁiX�j
	const float kCameraMoveMaxX  = 194.0f; //�J�����̈ړ��ʂ̍ő�iX�j
	const float kCameraMoveMinX  = 7.0f;   //�J�����̈ړ��ʂ̍ŏ��iX�j
	const float kCameraMoveY     = 2.5f;   //�J�����̈ړ��ʁiY�j
	
	//!�J����
	CAMERA camera_;
	
	//!�J�����̍��W
	Vector3 camera_pos_;

	//!�J�����̊p�x
	float angle_;

	//!�J�����̈ړ�����
	float camera_dist_;

	//!�v���C���[�̍��W
	Vector3   player_pos_;

	//!�Q�[���p�b�h���p�x
	float pad_x_;
	float pad_y_;

	//!�v���C���[����J�����𗣂�����
	float player_dist_;
};