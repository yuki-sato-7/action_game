/**
 * @file TitleScene.h
 * @brief �^�C�g���V�[���Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */

#pragma once

#include "BaseScene.h"
#include "MyLight.h"
#include "SeManager.h"
#include "SceneManager.h"
#include "Enum.h"

class TitleScene :public BaseScene {
public:
	void Initialize();
	void Update();
	void Draw3D();
	void Draw2D();

	/**
	 * @brief�@������_�ł����鏈��
	 */
	void FlashInterval();

private:
	// �萔
	const float kAdjustTittleTime  = 50.0f;    //�����ʂɈڍs���鎞�Ԓ���
	const float kAdjustTittleState = 1.0f;     //�����ʂɈڍs������
	const float kAdjustAlfaChange_ = 0.02f;    //�����̓����x��
	const float kAdjustAlfaMAX     = 1.0f;     //�����̓����x�i�ő�j
	
	//!�^�C�g�����
	SPRITE tittle_;

	//!�X�^�[�g�{�^��
	SPRITE press_start_;

	//!������������
	SPRITE operation_explanation_;

	//!�����������ʁi�{�^���j
	SPRITE operation_button;

	//!�Q�[���p�b�g�̏�Ԏ擾
	GamePadBuffer   pad_buffer_;
	GamePadState   pad_state_;
	
	//!�^�C�g����ʂ̑J��
	int tittle_state_;

	//!��ʑJ�ڂɕK�v����
	int tittle_count_;

	//!���̉�ʂɑJ�ڂ��邽�߂̏�ԊǗ�
	bool next_flag_;

	//!�Z���N�g���̏�ԊǗ�
	bool select_se_flag_;

	//!�����̓����x
	float alfa_clear_;

	//!�����̓����x
	float alfa_state_;
};
