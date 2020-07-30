/**
 * @file Enemy.h
 * @brief �G�N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once

class Player;

#include "Player.h"
#include "SeManager.h"
#include "Ground.h"
#include "EnemyManager.h"
#include "Enum.h"
#include "EffeksserManager.h"


class Enemy
{
public:

	/**
 �@�@* @brief �G�N���X������������
     * @param[in] (player) �v���C���[�N���X
 �@�@* @param[in] (enemy_pos_) ���C���V�[���Őݒ肵���G�̍��W
 �@�@* @return ���true
 �@�@*/
	virtual bool Initialize(Player& player,Vector3& enemy_pos_);

	/**
�@�@ * @brief �X�V(�ړ��A��ԑJ�ځA�Փˌ��o)
 �@�@* @param[in] (player) �v���C���[�N���X
 �@�@* @param[in] (ground) �w�i���W�Ǘ��N���X
 �@�@* @param[in] (enemy_pos_) �G�Ǘ��N���X
 �@�@*/
	virtual void Update(Player& player,Ground& ground, EnemyManager& em);

	/**
 �@�@* @brief �ҋ@��Ԃ���v���C���[�Ƃ̏����𑪂�A���̏�Ԃ����肷�邽�߂̏���
 �@�@*/
	virtual void Draw();

	/**
�@�@ * @brief �_�b�V���U���̃_���[�W��ԂɑJ�ڂ�����
 �@�@*/
	void EnemyHeavyDamageSwitch();

	/**
 �@�@* @brief �ʏ�U���̃_���[�W��ԂɑJ�ڂ�����
 �@�@*/
	void EnemyWeakDamageSwitch();

	/**
�@�@ * @brief�@�G�̏�Ԃ�؂�ւ��邽�߂̏���
 �@�@* @param[in] (new_state) �G�̏��
 �@�@*/
	void SetEnemyState(int new_state);

	/**
�@�@ * @brief�@�ړ��W�����v�̏�Ԃ̏���
 �@�@*/
	void EnemyMove();

	/**
     * @brief�@�ҋ@��Ԃ���v���C���[�Ƃ̏����𑪂�A���̏�Ԃ����肷�邽�߂̏���
     * @param[in] (enemy_manager) �G�Ǘ��N���X
     */
	void EnemyNormalSwitch(EnemyManager& enemy_manager);

	/**
     * @brief�@�ʏ�U�����󂯂���̃_���[�W���
     */
	void WeakDamageState();

	/**
     * @brief�@�_�b�V���U�����󂯂���̃_���[�W���
     * @param[in] (enemy_manager) �G�Ǘ��N���X
     */
	void HeavyDamageState(EnemyManager& enemy_manager);

	/**
     * @brief �p���`�U�����
     */
	void PunchState();

	/**
     * @brief �ʏ�U�����
     * @param[in] (enemy_manager) �G�S�̊Ǘ��N���X
     */
	void AttackState(EnemyManager& enemy_manager);

	/**
     * @brief�@�G���ҋ@��Ԃ̍ۂ̏���
     * @param[in] (enemy_manager) �G�Ǘ��N���X
     */
	void WaitState(EnemyManager& enemy_manager);

	/**
     * @brief�@�_���[�W���󂯂���́A�T�C�h�W�����v�����邽�߂ɓG���m�̋����𑪂鏈��
     * @param[in] (enemy_manager) �G�Ǘ��N���X
     */
	void EnemyDist(EnemyManager& enemy_manager);

	/**
     * @brief �c��HP���Ǘ����� HP�������Ȃ����甚���G�t�F�N�g���o��
     */
	void HpManager();

	/**
     * @brief �K�E�Z���󂯂���ɔ����G�t�F�N�g���o��
     */
	void DeathBolwHit();

	/**
     * @brief�@�_���[�W���󂯂���́A���T�C�h�W�����v�����邽�߂̏���
     */
	void LeftSideJumpState();

	/**
     * @brief�@�_���[�W���󂯂���́A�E�T�C�h�W�����v�����邽�߂̏���
     */
	void RightSideJumpState();

	/**
     * @brief�@�_���[�W���󂯂���́A���T�C�h�W�����v�����邽�߂̏���
     */
	void BackSideJumpState();

	/**
     * @brief�@�_���[�W���󂯂���̃W�����v�����E�A���Ɍ��肷�邽�߂̏���
     * @param[in] (enemy_manager) �G�Ǘ��N���X
     */
	void SideJumpState(EnemyManager& eenemy_managerm);

 	/**
     * @brief�@�G�̏Փ˔͈͂�ݒ肷��
     */
	void HitAreaControl();

	/**
	 * @brief�@�p���`��Ԃ̍U���͈͂�ݒ肷��
	 * @param[in] (enemy_manager) �G�Ǘ��N���X
	 */
	void PunchAreaControl(EnemyManager& enemy_manager);

	/**
     * @brief �ǂƂ̋����𑪒肷��
     * @param[in] (ground) �w�i�X�e�[�W�Ǘ��N���X
     */
	void GroundDist(Ground& ground);

	//�G��HP�擾����
	int GetEnemyHp() { return enemy_hp_; };

	//�G���_���[�W���󂯂Ă��邩�擾����
	bool GetEnemyHitFlag() { return hit_flag_; }

	//�G�̏�Ԃ��擾����
	int GetEnemyState(){ return enemy_state_; }

	//�G�̍��W�擾
	Vector3 GetEnemyPos() { return enemy_pos_; }

	//�G�̏��擾
	ANIMATIONMODEL GetEnemyModel() { return enemy_; }

	//�G�̏Փ˔͈͎擾
	MODEL GetHitModel() { return hit_enemy_ob_; }

	//�U���͈�
	MODEL GetAttackModel() { return punch_; }

	//�U�����Ă��邩�擾
	bool GetAttackFlag() { return attack_flag_; };

	//�������Ă��邩
	bool GetSurvialFlag() { return survival_flag_; }

private:
	// �萔
	const float kAdjustAdvanceTimeSpeed     = (1.0f/60.0f);     //�A�j���[�V�����̍Đ����x����
	const float kAdjustGroundDist           = 100.0f;           //�n�ʂ܂ł̋�������
	const float kAdjustEnemyRota            = 90.0f;            //�G�̌�������
	const float kAdjustPunchArea            = 25.0f;            //�p���`�U���̍��W����
	const float kAdjustHitArea              = 25.0f;            //�Փ˔͈͂̍��W����
	const float kAdjustWaitTimeEnd          = (100.0f/60.0f);   //�ҋ@��ԏI������
	const float kAdjustEnemyDistPosY        = 20.0f;            //�G���m�̋����𑪂�ۂ�Y���W����
	const float kAdjustEnemyDistFrontVec    = 10.0f;            //�G���m�̋����𑪂�ۂ̃��C�̒���
	const float kAdjustSideJumpMaxDist      = 800.0f;           //�T�C�h�W�����v�̍ۂ̓G���m�̋���
	const float kAdjustGroundMaxDist        = 300.0f;           //�ǂ܂ł̈ړ��ł���MAX����

	const float kAdjustJumpTimeEnd          = (72.0f/60.0f);    //�W�����v��ԏI������
	const float kAdjustJumpTimeRise         = (38.0f / 60.0f);  //�W�����v��ԁi�㏸���j
	const float kAdjustJumpTimeFall         = (55.0f / 60.0f);  //�W�����v��ԁi���~���j
	const float kAdjustJumpTimeTakeOff      = (22.0f / 60.0f);  //�W�����v��ԁi�㏸�O�j
	const float kAdjustJumpMoveX            = 3.0f;             //�W�����v�ړ������iX�j
	const float kAdjustJumpMoveY            = 1.01f;            //�W�����v�ړ������iY�j
	const float kAdjustJumpMoveZ            = 1.5f;             //�W�����v�ړ������iZ�j

	const float kAdjustMoveDist             = 120.0f;           //�ړ���Ԃɓ��鋗��
	const float kAdjustAttackDist           = 80.0f;            //�ʏ�U����Ԃɓ��鋗��

	const float kAdjustHeavyDamagePos       = 60.0f;            //�_�b�V���U���_���[�W�̍��W����
	const float kAdjustHeavyDamageTimeEnd   = (229.0f/60.0f);   //�_�b�V���U���_���[�W��ԏI������

	const float kAdjustWeakDamagePos        = 2.0f;             //�ʏ�U���_���[�W�̍��W����
	const float kAdjustWeakDamageTimeEnd    = (39.0f / 60.0f);  //�ʏ�U���_���[�W��ԏI������
	const float kAdjustAttackTimeEnd        = (250.0f / 60.0f); //�ʏ�U����ԏI������
	const float kAdjustAttackTimeOn         = (190.0f / 60.0f); //�ʏ�U���i�U���L���j����
	const float kAdjustAttackPosZ           = 1.5f;             //�ʏ�U���̍��W����(Z)

	const float kAdjustPunchTimeEnd         = (100.0f / 60.0f); //�p���`�U����ԏI������
	const float kAdjustPunchTimeOff         = (79.0f / 60.0f);  //�p���`�U���i�U�������j����
	const float kAdjustPunchTimeOn          = (50.0f / 60.0f);  //�p���`�U���i�U���L���j����
	const float kAdjustPunchTimeReserve     = (46.0f / 60.0f);  //�p���`�U���i�����j����
	const float kAdjustPunchPosZ            = 0.5f;             //�p���`�U���̍��W����(Z)

	const float kAdjustDamageCount          = 1.0f;             //�_���[�W�̉��Z
	const float kAdjustDeathBlowDamageCount = 5.0f;             //�K�E�Z�_���[�W�̉��Z

	const float kAdjustShadowScale          = 0.5f;             //�e�̑傫��
	const Vector3 kAdjustShadowLightPos     = Vector3(-10.0f, -100.0f, 10.0f);  //�e�𓊉e���邽�߂̃��C�g�̍��W
	const Vector3 kAdjustShadowPos          = Vector3(0.0f, 0.1f, 0.0f);        //�e�̍��W
	

	//!�G�̃A�j���[�V�������f��
	ANIMATIONMODEL enemy_;

	//!�G�̍��W
	Vector3 enemy_pos_;

	//!�G�̏Փ˔���p���f��
	MODEL hit_enemy_ob_;

	//!�G�̏Փ˔���̈�
	OrientedBoundingBox enemy_obb_; 

	//!�G�̏��
	int enemy_state_;
	
	//!�p���`�̏Փ˔͈̓��f��
	MODEL punch_;

	//!�v���C���[�̍��W
	Vector3 player_pos_;

	//!SE��炵����
	bool se_flag_;

	//!�_�E����ԂōU���𓖂ĂȂ����� false�ōU������������
	bool hit_flag_;

	//!�����f��
	MODEL ground_;

	//!�Փ˔���p�ǃ��f��
	MODEL ground_wall_;

	//!�|���ꂽ�ǂ���
	bool death_flag_;

	//!�G�ƃv���C���[�̋���
	float player_dist_;

	//!���܂ł̋���
	float ground_down_dist_;

	//!�v���C���[�Ɍ����邩�ǂ����@true�Ō�����
	bool rotation_flag_;

	//!�G��Y���W
	float groud_dist_;
 
	//!�G���_���[�W���󂯂���
	int enemy_hp_;

	//!�W�����vSE��炵����
	bool move_se_flag_;

	//!�p���`SE��炵����
	bool punch_se_flag_;

	//!���ԂƂ̋���
	float wait_dist_;

	//!�G�̑�HP
	int hp_max_;

	//!�G���U������
	bool attack_flag_;

	//!�G���������Ă��邩
	bool survival_flag_;

	//!hit��se��炵����
	bool hit_se_flag_;

	//!�_���[�W��ɃW�����v���邽�߂̏�Q���Ƃ̋����i�E�����j
	float right_side_dist_;

	//!�_���[�W��ɃW�����v���邽�߂̏�Q���Ƃ̋�����Q���Ƃ̋����i�������j
	float left_side_dist_;

	//!�_���[�W��ɃW�����v���邽�߂̏�Q���Ƃ̋�����Q���Ƃ̋����i�������j
	float back_dist_;

	//!�O�������ɂ���G�Ƃ̋����P
	float forward_1_dist_;

	//!�O�������ɂ���G�Ƃ̋����P
	float forward_2_dist_;

	//!���ɃW�����v�\�����f
	bool left_side_jump_flag_;

	//!�E�ɃW�����v�\�����f
	bool right_side_jump_flag_;

	//!���ɃW�����v�\�����f
	bool back_side_jump_flag_;

	//!�E�ɃW�����v�\�����f 
	bool side_jump_flag_;

	//!�_���[�W��ɃW�����v���������f
	float ground_long_dist_;

	//!�ǂ܂ł̋����i�O�����j
	float enemy_forward_direction_;

	//!�ǂ܂ł̋����i�������j
	float enemy_back_direction_;

	//!�ǂ܂ł̋����i�������j
	float enemy_left_direction_;

	//!�ǂ܂ł̋����i�E�����j
	float enemy_right_direction_;

	//!�ړ����\���ǂ����i�O�����j
	bool forward_move_flag_;

	//!�ړ����\���ǂ����i�������j
	bool back_move_flag_;

	//!�ړ����\���ǂ����i�������j
	bool left_move_flag_;

	//!�ړ����\���ǂ����i�E�����j
	bool right_move_flag_;

	//!���ԂƂ̋����i�������j
	float left_dist_max_;

	//!���ԂƂ̋����i�E�����j
	float right_dist_max_;

	//!�v���C���[�̌����Ă������
	Vector3 player_angle_;
};