/**
 * @file Enum.h
 * @brief �萔�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once

 /**
  * @enum Enum
  * �v���C���[�̏��
  */
enum PLAYER_STATE {
	//!�ҋ@���[�V����
	WAIT,
	//!�������[�V����
	WALK,
	//!���胂�[�V����
	RUN,
	//!�_�b�V�����[�V����
	DASH,
	//!�_���[�W���[�V����
	DAMAGE,
	//!�U���i�ҋ@�j���[�V����
	ATTACK_WAIT,
	//!�U���i�_�b�V���j���[�V����
	ATTACK_DASH,
	//!�U���i�ҋ@�j�߂胂�[�V����
	ATTACK_WAITBACK,
	//!�U���i�_�b�V���j�߂胂�[�V����
	ATTACK_DASHBACK,
	//!�|�ꃂ�[�V����
	DEATH,
	//!�K�E�Z���[�V����
	DEATHBLOW,
	//!�K�E�Z�߂胂�[�V����
	DEATHBLOW_BACK,
	//!������[�V����
	STEP,
	//!�^�C���I�[�o�[���
	TIME_OVER,
	//!�Q�[���N���A���
	GAME_CLEAR
};

/**
 * @enum Enum
 * ���G���
 */
enum Player_Invincible {
	//!���G���
	Invincible,
	//!�񖳓G���
	Not_invincible
};

/**
 * @enum Enum
 * �G�̏��
 */
enum Enemy_STATE {
	//!�ʏ���
	WAITING,
	//!�U�����[�V����
	ATTACK,
	//!�������[�V����
	HEAVY_DAMAGE,
	//!���胂�[�V����
	WEAK_DAMAGE,
	//!�ړ����[�V����
	MOVE,
	//!�ʏ���
	END_WAITING,
	//!�p���`���[�V����
	PUNCH,
	//!�ҋ@���[�V�����i�Q�[���I���j
	SIDE_JUMP,
	//!�ʏ���
	NORMAL,
	//!�^�C���I�[�o�[���
	TIME_OVER_,
	//!�v���C���[���S���
	PLAYER_DEATH_
};

/**
 * @enum Enum
 * HP�Q�[�W�̏��
 */
enum HpGauge_STATE {
	//!�_���[�W5��
	RED_1,
	//!�_���[�W4��
	RED_2,
	//!�_���[�W3��
	YELLOW_1,
	//!�_���[�W2��
	YELLOW_2,
	//!�_���[�W1��
	GREEN_1,
	//!�_���[�W0��
	GREEN_2
};

/**
 * @enum Enum
 * �����̔Z�x
 */
enum Alfa_STATE {
	//!�����̓����x0%
	ALPHA_MIN,
	//!�����̓����x100%
	ALPHA_MAX
};

/**
 * @enum Enum
 * Observer�̈���
 */
enum Observer_STATE {
	//!�^�C���I�[�o�[���
	TIME_OVER_STATE,
	//!�Q�[���I�[�o�[���
	GAME_OVER_STATE,
	//!�Q�[���N���A���
	GAME_CLEAR_STATE,
};