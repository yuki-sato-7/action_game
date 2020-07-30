/**
 * @file Player.h
 * @brief �v���C���[�N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once

class Enemy;
class CameraMain;

#include "Ground.h"
#include "EffeksserManager.h"
#include "EnemyManager.h"
#include "UiManager.h"
#include "TimeManager.h"
#include "Enum.h"

class Player
{
public:

	/**
 �@�@* @brief�@�v���C���[�N���X������������
 �@�@* @return ���true
 �@�@*/
	virtual bool Initialize();

	/**
 �@�@*  * @brief �X�V(�ړ��A��ԑJ�ځA�Փˌ��o�A�ǃY���A���G���)
 �@�@* @param[in] (ground) �w�i�X�e�[�W�N���X
 �@�@* @param[in] (camera_main) �J�����N���X
 �@�@* @param[in] (enemy_manager) �G�Ǘ��N���X
 �@�@* @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾��
 �@�@* @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
 �@�@*/
	virtual void Update(Ground& ground,CameraMain& camera_main, EnemyManager& em, GamePadBuffer&pad_buffer,GamePadState&pad_state);
	
	/**
 �@�@* @brief �v���C���[��`��
 �@�@*/
	virtual void Draw();

	/**
�@�@ * @brief �v���C���[�̏�Ԃ�؂�ւ��邽�߂̏���
 �@�@* @param[in] (new_state) �v���C���[�̏��
 �@�@*/
	void SetPlayerState(int new_state);

	/**
     * @brief ������
     */
	void StepState();

	/**
�@�@ * @brief �_�b�V�����
 �@�@* @param[in] (camera_main) �J�����N���X
 �@�@* @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾���
 �@�@* @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
 �@�@*/
	void DashState(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	/**
 �@�@* @brief �_�b�V���U�����
 �@�@*/
	void AttackDashState();

	/**
 �@�@* @brief �_�b�V���U���i�߂�j���
 �@�@*/
	void AttackDashBackState();

	/**
     * @brief �_���[�W���
     */
	void DamageState();

	/**
     * @brief �U�����
     */
	void AttackWaitState();

	/**
     * @brief �U���i�߂�j���
     */
	void AttackWaitBackState();

	/**
     * @brief ���S���
     */
	void DeathState();

	/**
     * @brief �K�E�Z���
     */
	void DeathblowState();

	/**
     * @brief �K�E�Z�i�߂�j���
     */
	void DeathblowBackState();
	
	/**
     * @brief �_���[�W��ԂɑJ�ڂ�����
     * @param[in] (knockbackVector) �J�����Ǘ��N���X
     * @param[in] (enemy) �U�����󂯂��G�̏��
     */
	void PlayerDamageSwitch(Vector3& knockbackVector, std::shared_ptr<Enemy> enemy_);

	/**
     * @brief �ʏ��Ԃɂ��玟�̏�ԂɑJ�ڂ�����
     * @param[in] (camera_main) �J�����N���X
     * @param[in] (pad_buffer) �Q�[���p�b�h�̏��擾
     * @param[in] (pad_state) �Q�[���p�b�h�̏��擾
     */
	void PlayerMoveSwitch(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state);

	/**
 �@�@* @brief �v���C���[�̏Փ˔͈͂�ݒ肷��
 �@�@*/
	void HitAreaControl();

	/**
     * @brief �_���[�W���󂯂���̖��G��Ԃ��Ǘ�
     */
	void InvincibleTime();

	/**
 �@�@* @brief �v���C���[�̍U���͈͂�ݒ肷��
 �@�@*/
	void AttackAreaControl();

	//�v���C���[�̍��W�擾
	Vector3 GetPlayerPos() { return player_->GetPosition(); }

	//�v���C���[�̃��f�����擾
	ANIMATIONMODEL GetPlayerModel() { return player_; }

	//�G�̍U���L���͈͂̎擾
	MODEL GetPlayerHitArea() { return hit_area_; }

	//�K�E�Z�̍U���͈͂̎擾
	MODEL GetDeathBlowHitArea() { return death_blow_area_; };

	//�v���C���[�̍U���͈͂̎擾
	MODEL GetAttackArea() { return attack_area_; }

	//�v���C���[�̏�Ԃ��擾����֐�
	int GetPlayerState() { return player_state_; }

	//�v���C���[���U�����Ă��邩
	bool GetHitFlag() { return player_hit_flag_; };

	//�G�̍U�����������Ă��邩
	bool GetDamageFlag() { return damage_flag_; };

	//�Q�[���I�[�o�[��Ԃ�
	bool GameOverFlag() { return game_over_flag_; };

	//�Q�[���I����Ԃ�
	bool GameEndFlag() { return operation_flag_; };

	//�v���C���[�p�̉e
	inline Matrix Create_Shadow_Matrix(const D3DLIGHTTYPE light_type, const Vector3& light,
		const Vector3& pos, const Vector3& shadow_offset,
		const Vector3& normal);



	float GetDist() { return wall_dist_min_; };

private:
	// �萔
	const float kAdjustAdvanceTimeSpeed      = (1.0f / 60.0f);    //�A�j���[�V�����̍Đ����x����
	const float kAdjustGroundDistRay         = 100.0f;            //���܂ł̋����𑪂�ۂ̃��C�̒���
	const float kAdjustGroundDistPosY        = 20.0f;             //�ǂ܂ł̋����𑪂�ۂ�Y���W����
	const float kAdjustGroundMaxDist         = 100.0f;            //�ǂ܂ł̈ړ��ł���MAX����
	const float kAdjustGroundWallMaxDist     = 50.0f;             //�ǃY������MAX����
	const float kAdjustEnemydWallMaxDist     = 20.0f;             //�ǃY������MAX�����i�G�j
	const float kAdjustEnemyWallDistPosY1    = 10.0f;             //�ǃY������̋����𑪂�ۂ�Y���W����
  	const float kAdjustEnemyWallDistPosY2    = 100.0f;             //�ǃY������̋����𑪂�ۂ�Y���W�����i�G�̃W�����v��Ԃœ�����悤�ɒ����j
	const float kAdjustEnemyMinxDist         = 8.0f;              //�ǂ܂ł̈ړ��ł��Ȃ��Ȃ�MIN�����s�i�G�j
	const float kAdjustGroundWallSpeed       = 1.0f;              //�ǃY���̃X�s�[�h
	const float kAdjustAttackArea            = 25.0f;             //�U���̍��W����
	const float kAdjustPlayerRota            = 180.0f;            //�v���C���[�̌�������
	const float kAdjustPlayerMove            = 0.2f;              //�v���C���[�̈ړ��ʒ����i�_�b�V���j
	const float kAdjustPlayerRunMove         = 0.5f;              //�v���C���[�̈ړ��ʒ����i����j
	const float kAdjustPlayerWalkMove        = 1.0f;              //�v���C���[�̈ړ��ʒ����i�����j
	const float kAdjustPlayerWalkPadAngle    = 0.5f;              //�v���C���[�̕����ɂ���Q�[���p�b�h�̊p�x

	const float kAdjustAttackDashTimeEnd     = (51.0f / 60.0f);   //�_�b�V���U����ԏI������
	const float kAdjustAttackDashTimeOff     = (21.0f / 60.0f);   //�_�b�V���U���i�U�������j����
	const float kAdjustAttackDashTimeOn      = (10.0f / 60.0f);   //�_�b�V���U���i�U���L���j����
	const float kAdjustAttackDashBackTimeEnd = (39.0f / 60.0f);   //�_�b�V���U���i�߂�j��ԏI������

	const float kAdjustStepTimeEnd           = (58.0f / 60.0f);   //�����ԏI������
	const float kAdjustStepTimeMove          = (41.0f / 60.0f);   //����i�ړ��j��ԏI������
	const float kAdjustStepMoveZ             = -3.0f;             //�����Ԉړ�(Z)

	const float kAdjustAttakWaitTimeEnd      = (41.0f / 60.0f);  //�U����ԏI������
	const float kAdjustAttakWaitTimeOff      = (35.0f / 60.0f);   //�U���i�U�������j����
	const float kAdjustAttakWaitTimeOn       = (17.0f / 60.0f);   //�U���i�U���L���j����
	const float kAdjustAttakWaitTimeReserve  = (8.0f / 60.0f);    //�U���i�����j����
	const float kAdjustAttakWaitMoveZ        = 2.5f;              //�U����Ԉړ��ʒ���(Z)

	const float kAdjustAttakDamageTimeEnd    = (60.0f / 60.0f);   //�_���[�W��ԏ�ԏI������

	const float kAdjustAttakDamageMove       = 1.5f;              //�_���[�W��ԂœG�̐i�s�����Ɉړ������

	const float kAdjustDeathTimeEnd          = (116.0f / 60.0f);  //���S��ԏ�ԏI������
	
	const float kAdjustInvincibleTime        = 150.0f;            //���G���Ԓ���

	const float kAdjustDeathBlowTimeEnd      = (120.0f / 60.0f);  //�K�E�Z��ԏI������
	const float kAdjustDeathBlowTimeOn       = (28.0f / 60.0f);   //�K�E�Z�i�U���L���j����
	const float kAdjustDeathBlowMoveZ        = 8.0f;              //�K�E�Z��Ԉړ��ʒ���(Z)

	const float kAdjustDeathBlowBackTimeEnd  = (45.0f / 60.0f);   //�K�E�Z�i�߂�j��ԏI������
	const float kAdjustDeathBlowBackTimeOn   = (10.0f / 60.0f);   //�K�E�Z�i�߂�j�J�n����
	const float kAdjustDeathBlowBackMoveZ    = 0.1f;              //�K�E�Z�i�߂�j��Ԉړ��ʒ���(Z)

	const float kAdjustShadowDepth           = 0.75f;             //�e�̔Z��
	const Vector3 kAdjustShadowLightDist     = Vector3(0, 1500000, 150000);  //�e�𓊉e���邽�߂̃��C�g�̈ʒu
	const Vector3 kAdjustShadowMove          = Vector3(0.0f, 1.0f, 0.0f);    //�v���C���[����e���ǂꂭ�炢���炷��
	
	const int kAdjustFlashInterval           = 2.0f;                //���G���Ԃ̍ۂɃv���C���[��_�ł�����Ԋu


	//!�v���C���[�̃��f��
	ANIMATIONMODEL player_;

	//!�v���C���[�̍U������p�̈�
	MODEL attack_area_;

	//!�K�E�Z�̏Փ˔���̈�
	MODEL death_blow_area_;

	//!�v���C���[�̏Փ˔���̈�
	MODEL hit_area_;

	//!�����f��
	MODEL ground_;

	//!�ǃ��f��
	MODEL ground_wall_;

	//!�J�����̊p�x
	Quaternion camer_qt_;

	//!�ǃY����Ԃ�
	bool ground_block_;

	//!�J����
	CAMERA camera_;
	
	//!�p�b�h�̏�ԁi���E�j
	float pad_x_;

	//!�p�b�h�̏�ԁi�㉺�j
	float pad_y_;

	//!�p�b�h�̏�ԁi���E�j�}�b�s���O��
	float pad_x_x_;

	//!�p�b�h�̏�ԁi�㉺�j�}�b�s���O��
	float pad_y_y_;

	//!LB�{�^���̏��
	float lb_;

	//!�U������̗L��
	bool hit_judge_;

	//!�G�Ƃ̓����蔻��
	bool collsion_judge_;

	//!�v���C���[�U�����L����
	bool player_hit_flag_;

	//!�v���C���[�̊p�x
	float angle_;

	//!���݂̃v���C���[�̃��[�V����
	int player_state_;

	//!���܂ł̋����i����p�j
	float ground_dist_;

	//!�ǃY�����Ă��邩
	bool wall_bolck_;	

	//!�G�t�F�N�g��\��������
	bool ef_flag_;

	//!���G���Ԍv��
	int invincible_time_;

	//!�_���[�W��������Ă��邩
	bool damage_flag_;

	//!�G�̐i�s�x�N�g��
	Vector3 enemy_front_;

	//!�G�̏��
	int enemy_state_;

	//!�U�����Ă���G�̎擾
	std::shared_ptr<Enemy> enemy_;

	//!���S��Ԃ��ǂ���
	bool death_flag_;

	//!����\��
	bool operation_flag_;

	//!�Q�[���I�[�o�[��
	bool game_over_flag_;

	//!�K�E�Z�G�t�F�N�g��\��������
	bool deathblow_ef_flag_;

	//!SP�Q�[�W�̗�
	float sp_max;

	//!�v���C���[�Ə��܂ł̃��C
	float dist_;

	//!�ǂ܂ł̍ł��Z�����C
	float wall_dist_min_;

	//!�ǂ܂ł̃��C1
	float wall_dist_1_;

	//!�ǂ܂ł̃��C2
	float wall_dist_2_;

	//!�ǃY����̕ǂ܂ł̃��C
	float wall_dist_3_;

	//!�ǂƂ̕��s�x�N�g��
	Vector3  parallel_vec_;

	//!�X�e�B�b�N�̌X���
	float pad_angle_;

	//!�J�����̐i�s�x�N�g���i�m�[�}���C�Y�j
	float camera_dist_;

	//!�v���C���[�̍��W
	Vector3 anime_pos_;
};