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
	//�ҋ@���[�V����
	WAIT,
	//�������[�V����
	WALK,
	//���胂�[�V����
	RUN,
	//�_�b�V�����[�V����
	DASH,
	//�_���[�W���[�V����
	DAMAGE,
	//�U���i�ҋ@�j���[�V����
	ATTACK_WAIT,
	//�U���i�_�b�V���j���[�V����
	ATTACK_DASH,
	//�U���i�ҋ@�j�߂胂�[�V����
	ATTACK_WAITBACK,
	//�U���i�_�b�V���j�߂胂�[�V����
	ATTACK_DASHBACK,
	//�|�ꃂ�[�V����
	DEATH,
	//�K�E�Z���[�V����
	DEATHBLOW,
	//�K�E�Z�߂胂�[�V����
	DEATHBLOW_BACK,
	//�K�E�Z�߂胂�[�V����
	STEP
};

/**
 * @enum Enum
 * ���G���
 */
enum Player_Invincible {
	Invincible,
	Not_invincible
};

/**
 * @enum Enum
 * �G�̏��
 */
enum Enemy_STATE {
	//�ړ����[�V����
	MOVE,
	DA,
	//�p���`���[�V����
	PUNCH,
	//�ҋ@���[�V����
	WAITING,
	//�p���`���[�V����
	SIDE_JUMP,
	//���胂�[�V����
	WEAK_DAMAGE,
	///�������[�V����
	HEAVY_DAMAGE,
	//�U�����[�V����
	ATTACK,
	//�K�E�Z�_���[�W���[�V����
	DEATHBLOW_DAMAGE,
	BREAK,
	//NORMAL,
	NORMAL
};

/**
 * @enum Enum
 * HP�Q�[�W�̏��
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
 * �����̔Z�x
 */
enum Alfa_STATE {
	ALFA_MIN,
	ALFA_MAX
};