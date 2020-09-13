/**
 * @file Player.cpp
 * @brief �v���C���[�N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "Player.h"
#include "CameraMain.h"
#include "Enemy.h"

/**
 * @brief�@�v���C���[�N���X������������
 * @return ���true
 */
bool Player::Initialize(EnemyManager& enemy_manager)
{
	//�v���C���[���f���̐ݒ�
	player_       = GraphicsDevice.CreateAnimationModelFromFile(_T("player/player.X"));
	player_->SetScale(0.5f);
	Material mtrl;
	mtrl.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	mtrl.Ambient  = Color(0.25f, 0.25f, 0.25f);
	mtrl.Specular = Color(1.f, 1.f, 1.f);
	mtrl.Power    = 1.f;
	mtrl.Emissive = Color(0.f, 0.f, 0.f);
	player_->SetMaterial(mtrl);
	player_->SetDirection(0, -90, 0);
	player_->SetPosition(0, 0, 0);

	//�v���C���[�̍U������p�̈惂�f���̐ݒ�
	SimpleShape shape;
	shape.Type   = Shape_Box;
	shape.Width  = 50.0f;
	shape.Depth  = 40.0f;
	shape.Height = 30.0f;
	attack_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape);
	attack_area_->SetDirection(0.0f, 0.0f, 0.0f);//����
	attack_area_->SetMaterial(mtrl);
	hit_judge_  = false;

	//�v���C���[�̕K�E�Z����p�̈惂�f���̐ݒ�
	SimpleShape shape3;
	shape3.Type      = Shape_Box;
	shape3.Depth     = 59.0f; 
	shape3.Height    = 45.0f;
	shape3.Width     = 37.0f;
	death_blow_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape3);
	death_blow_area_->SetDirection(0.0f, 0.0f, 0.0f);//����
	death_blow_area_->SetMaterial(mtrl);

	//�v���C���[�̏Փ˔���̈惂�f���̐ݒ�
	SimpleShape shape2;
	shape2.Type   = Shape_Box;
	shape2.Depth  = 17.0f;  //���a
	shape2.Height = 65.0f;
	shape2.Width  = 13.0f;
	hit_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape2);
	hit_area_->SetDirection(player_->GetDirectionQuaternion());
	hit_area_->SetMaterial(mtrl);
	hit_area_->SetPosition(player_->GetPosition());
	GraphicsDevice.SetMaterial(mtrl);

	//�e�A�j���[�V���������[�v�����Ȃ�
	player_->SetTrackLoopMode(DEATH, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_WAIT, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_WAITBACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_DASH, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_DASHBACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DEATHBLOW, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DEATHBLOW_BACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DAMAGE, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(STEP, AnimationLoopMode_Once);

	//�I�u�U�[�o�[�ɒǉ�
	time_manager().AddObserver(this);
	ui_manager().AddObserver(this);
	enemy_manager.AddObserver(this);
	
	//�e�ϐ��̏�����
	SetPlayerState(WAIT);
	player_state_    = WAIT;
	pad_angle_       = 0.0f;
	ground_dist_     = 100.0f;
	invincible_time_ = 0.0f;
	sp_max           = 319.0f;
	wall_dist_min_   = FLT_MAX;
	dist_            = FLT_MAX;
	anime_pos_       = player_->GetPosition();
	
	wall_bolck_        = false;
	ef_flag_           = true;
	player_hit_flag_   = false;
	damage_flag_       = false;
	death_flag_        = false;
	operation_flag_    = false;
	deathblow_ef_flag_ = false;
	game_clear_flag_   = false;
	
	return true;
}

/**
 * @brief �X�V(�ړ��A��ԑJ�ځA�Փˌ��o�A�ǃY���A���G���)
 * @param[in] (ground) �w�i�X�e�[�W�N���X
 * @param[in] (camera_main) �J�����N���X
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 * @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾��
 * @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
 */
void Player::Update(Ground& ground, CameraMain& camera_main, EnemyManager& enemy_manager, GamePadBuffer& pad_buffer, GamePadState& pad_state)
{

	//�v���C���[�̍��W
	anime_pos_ = player_->GetPosition();

	//���[�V�����̍Đ��X�s�[�h����
	player_->AdvanceTime(kAdjustAdvanceTimeSpeed);

	//�X�e�[�W�̃��f��
	ground_ = ground.GetModel();
	ground_wall_ = ground.GetCollisionModelWall();

	//�n�ʂ̉��ʔ���
	ground_->IntersectRay(anime_pos_ + Vector3(0, kAdjustGroundDistRay, 0), Vector3_Down, &dist_);

	//�Q�[���p�b�g�̔���
	pad_x_ = -(((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));
	pad_y_ = (((float)pad_state.Y - Axis_Center) / (Axis_Max - Axis_Center));
	lb_ = (((float)pad_state.X2 - Axis_Center) / (Axis_Max - Axis_Center));

	//�l�p�`���~�Ƀ}�b�s���O���Ď΂ߕ����ɓ|�������̃X�s�[�h�𒲐�����
	pad_x_x_ = pad_x_ * Math_Sqrt(1.0f - 0.5f * pad_y_ * pad_y_);
	pad_y_y_ = pad_y_ * Math_Sqrt(1.0f - 0.5f * pad_x_ * pad_x_);

	//�A�i���O�X�e�B�b�N�̌X���
	pad_angle_ = Math_Sqrt(pad_x_x_ * pad_x_x_ + pad_y_y_ * pad_y_y_);

	//�v���C���[��y���W
	angle_ = MathHelper_Atan2(-float(pad_state.X - Axis_Center) / float(Axis_Max - Axis_Center),
		float(pad_state.Y - Axis_Center) / float(Axis_Max - Axis_Center));

	//�i�s�x�N�g��
	Vector3 F = player_->GetFrontVector();

	//�ǂ܂ł̋�������
	wall_dist_1_ = FLT_MAX;
	Vector3 vec;
	wall_dist_2_= FLT_MAX;
	Vector3 vec2;

	ground_wall_->IntersectRay(anime_pos_ + Vector3(0, kAdjustGroundDistPosY, 0) - player_->GetRightVector(), F, &wall_dist_1_, &vec);
	ground_wall_->IntersectRay(anime_pos_ + Vector3(0, kAdjustGroundDistPosY, 0) + player_->GetRightVector(), F, &wall_dist_2_, &vec2);

	Vector3 vec_x;
	if (wall_dist_1_ <= wall_dist_2_) {
		wall_dist_min_ = wall_dist_1_;
		vec_x = vec;
	}
	else {
		wall_dist_min_ = wall_dist_2_;
		vec_x = vec2;
	}

	wall_dist_3_ = FLT_MAX;
	Vector3 vec3;


	//�ǂƂ̕ǃY��
	if (wall_dist_min_ < kAdjustGroundMaxDist) {
		ground_block_ = true;
		// ���ς����߂�
		float  a = Vector3_Dot(-F, vec_x);
		//�ǂɕ��s�ȃx�N�g�������߂�
		parallel_vec_ = F + a * vec_x;
		//�ǂ���̑��x��ݒ�
		if (player_state_ == WALK || player_state_ == RUN || player_state_ == DASH) {
			ground_wall_->IntersectRay(anime_pos_, parallel_vec_, &wall_dist_3_, &vec3);
			if (wall_dist_3_ > kAdjustGroundWallMaxDist) {
				anime_pos_ += parallel_vec_ * kAdjustGroundWallSpeed;
			}

		}
		//�L�����ɃZ�b�g�i�o���j������
		player_->SetPosition(anime_pos_);
	}

	else {
		ground_block_ = false;
	}


	Vector3 front = player_->GetFrontVector();
	Vector3 normal_vector1_;  //!�G�Ƃ̕��s�x�N�g��
	Vector3 normal_vector2_;
	Vector3 normal_vectorx1_;
	Vector3 normal_vectorx2_;
	float enemy_dist1_  = FLT_MAX;   //!�G�Ƃ̋���
	float enemy_dist2_  = FLT_MAX;
	float enemy_distx1_ = FLT_MAX;
	float enemy_distx2_ = FLT_MAX;

	if (player_state_ != DAMAGE) {
		auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
		auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
		while (enemys_it != enemys.end()) {

			if ((*enemys_it)->GetEnemyState() != WEAK_DAMAGE && (*enemys_it)->GetEnemyState() != HEAVY_DAMAGE) {                //�|��Ă���G�Ƃ͕ǃY�������Ȃ�

				(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY1, 0), front, &enemy_dist1_, &normal_vector1_);
				(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY2, 0), front, &enemy_dist2_, &normal_vector2_);

				if (enemy_dist2_ < enemy_dist1_) {
					enemy_dist1_ = enemy_dist2_;
					normal_vector1_ = normal_vector2_;
				}

				//�G�Ƃ̕ǃY��
				if (enemy_dist1_ < kAdjustEnemydWallMaxDist) {
					wall_bolck_ = true;
					// ���ς����߂�
					float  a = Vector3_Dot(-front, normal_vector1_);
					//�G�ɕ��s�ȃx�N�g�������߂�
					Vector3  p = front + a * normal_vector1_;
					//�ǂ���̑��x��ݒ�
					if (player_state_ == WALK || player_state_ == RUN || player_state_ == DASH || player_state_ == DAMAGE) {
						//�ǃY�����̔���
						(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY1, 0), front, &enemy_distx1_, &normal_vectorx1_);
						(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY2, 0), front, &enemy_distx2_, &normal_vectorx2_);

						if (enemy_distx2_ < enemy_distx1_) {
							enemy_distx1_ = enemy_distx2_;
							normal_vectorx1_ = normal_vectorx2_;
						}

						if (enemy_distx1_ > kAdjustEnemyMinxDist) {
							anime_pos_ += p * kAdjustGroundWallSpeed;    //�ǃY������
						}
						player_->SetPosition(anime_pos_);
					}
				}
				else {
					wall_bolck_ = false;
				}
			}
			enemys_it++;
		}
	}

	switch (player_state_) {
	case DASH:
		DashState(camera_main, pad_buffer, pad_state);
		break;

	case DAMAGE:
		DamageState();
		break;

	case ATTACK_WAIT:
		AttackWaitState();
		break;

	case ATTACK_DASH:
		AttackDashState();
		break;

	case ATTACK_WAITBACK:
		AttackWaitBackState();
		break;

	case ATTACK_DASHBACK:
		AttackDashBackState();
		break;

	case DEATH:
		DeathState(enemy_manager);
		break;

	case DEATHBLOW:
		DeathblowState();
		break;

	case DEATHBLOW_BACK:
		DeathblowBackState();
		break;

	case STEP:
		StepState(ground);
		break;

	case TIME_OVER:
		operation_flag_ = true;
		ui_manager().AllDelteObserver(this);
		time_manager().AllDelteObserver(this);
		enemy_manager.AllDelteObserver(this);
		SetPlayerState(WAIT);
		break;
	}

	if(game_clear_flag_ == true){
		ui_manager().AllDelteObserver(this);
		time_manager().AllDelteObserver(this);
		enemy_manager.AllDelteObserver(this);
	}

	//sp�Q�[�W�̉�
	if (player_state_ != DEATHBLOW && player_state_ != DEATHBLOW_BACK) {
		ui_manager().SpGaugeUp();
	}

	PlayerMoveSwitch(camera_main, pad_buffer, pad_state);

	HitAreaControl();

	AttackAreaControl();

	InvincibleTime();
}

/**
 * @brief �v���C���[�̍U���͈͂�ݒ肷��
 */
void Player::AttackAreaControl() {

	if (player_state_ == ATTACK_WAIT || player_state_ == ATTACK_DASH)
	{
		if (player_hit_flag_ == true) {
			attack_area_->SetPosition(anime_pos_ + player_->GetFrontVector() * kAdjustAttackArea);
			Vector3 kakudo_attack = Vector3_Zero;
			attack_area_->SetDirection(player_->GetDirectionQuaternion());
		}
	}

	if (player_state_ == DEATHBLOW)
	{
		if (player_hit_flag_ == true) {
			death_blow_area_->SetPosition(anime_pos_ + player_->GetFrontVector() * kAdjustAttackArea);
			Vector3 kakudo_attack = Vector3_Zero;
			death_blow_area_->SetDirection(player_->GetDirectionQuaternion());
		}
	}
}

/**
 * @brief �v���C���[�̏Փ˔͈͂�ݒ肷��
 */
void Player::HitAreaControl() {

	hit_area_->SetPosition(anime_pos_);
	hit_area_->SetDirection(player_->GetDirectionQuaternion());
}

/**
 * @brief �_�b�V�����
 * @param[in] (camera_main) �J�����N���X
 * @param[in] (pad_buffer) �Q�[���p�b�h�̏�Ԏ擾���
 * @param[in] (pad_state) �Q�[���p�b�h�̏�Ԏ擾
 */
void Player::DashState(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state) {

	if (player_state_ != DASH)
		return;

	if (operation_flag_ == false) {
		//�X�e�B�b�N��|���Ă���ꍇ
		if (pad_y_y_ != 0 || pad_x_x_ != 0) {
			//�J�����̐i�s�x�N�g���擾
			auto camera_dir = camera_main.GetCamera().GetFrontVector();
			//y���W�͎g�p���Ȃ��̂�0�ɂ��Ă���
			camera_dir.y = 0;
			//�i�s�x�N�g���𐳋K��
			camera_dir = Vector3_Normalize(camera_dir);
			//���K�������x�N�g������r���[�s����擾����
			Matrix   mat = Matrix_CreateLookAt(Vector3_Zero, camera_dir, Vector3_Up);
			//�r���[�s��̋t�s�񂩂烏�[���h�s������߂�
			mat = Matrix_Invert(mat);
			//���[���h�s�񂩂�N�H�[�^�j�I���i�p�x�j�ɕϊ�
			camer_qt_ = Quaternion_CreateFromRotationMatrix(mat);
			//�J�����̌����Ƀv���C���[����������
			player_->SetDirection(camer_qt_);
			//�X�e�B�b�N�̌X���ɍ��킹�ăv���C���[�̎�����]������
			player_->Rotation(0, angle_ + kAdjustPlayerRota, 0);
		}

		if (wall_bolck_ == false && ground_block_ == false) { 
			player_->Move(0, ground_dist_ - dist_, pad_angle_ / kAdjustPlayerMove);
		}

		if (pad_buffer.IsPressed(GamePad_Button2)) {
			SetPlayerState(ATTACK_DASH);
		}

		else if (pad_angle_ == 0) {
			SetPlayerState(WAIT);
		}

		else if (pad_buffer.IsPressed(GamePad_Button6)) {
			if (ui_manager().GetSpGauge() >= sp_max) {
				ui_manager().SpGaugeDown();
				SetPlayerState(DEATHBLOW);
			}
		}

		else if (pad_buffer.IsPressed(GamePad_Button5)) {
			SetPlayerState(STEP);
		}

		else if (lb_ == 0) {
			SetPlayerState(WAIT);
		}

		else if (pad_buffer.IsReleased(GamePad_Button1)) {
			SetPlayerState(WAIT);
		}
	}

}

/**
 * @brief �_�b�V���U�����
 */
void Player::AttackDashState() {
	if (player_state_ != ATTACK_DASH)
		return;

	auto attackdash_time = player_->GetTrackPosition(ATTACK_DASH);

	if (attackdash_time >= kAdjustAttackDashTimeEnd) {
		SetPlayerState(ATTACK_DASHBACK);
		player_hit_flag_ = false;
		hit_judge_ = false;
		ef_flag_ = true;
	}

	else if (attackdash_time >= kAdjustAttackDashTimeOn && attackdash_time < kAdjustAttackDashTimeOff) {
		if (ef_flag_ == true) {
			effectmanager().DashSlashEffectPlay(*this);
			ef_flag_ = false;
		}
		hit_judge_ = true;
	}

	else if (attackdash_time >= 0 && attackdash_time < kAdjustAttackDashTimeOn) {
		player_->Move(0, ground_dist_ - dist_, pad_angle_ / 0.25f);
		player_hit_flag_ = true;
		operation_flag_ = true;
	}
}

/**
 * @brief �_�b�V���U���i�߂�j���
 */
void Player::AttackDashBackState() {

	if (player_state_ != ATTACK_DASHBACK)
		return;

	auto attack_dash_back_time = player_->GetTrackPosition(ATTACK_DASHBACK);

	if (attack_dash_back_time >= kAdjustAttackDashBackTimeEnd) {
		SetPlayerState(WAIT);
		operation_flag_ = false;
	}
}

/**
 * @brief ������
 */
void Player::StepState(Ground& ground) {

	if (player_state_ != STEP)
		return;

	auto step_time = player_->GetTrackPosition(STEP);
	float wall_dist_back;
	Vector3 back_vec;
	ground_wall_->IntersectRay(anime_pos_ + Vector3(0, kAdjustGroundDistPosY, 0), -player_->GetFrontVector(), &wall_dist_back, &back_vec);

	if (step_time >= kAdjustStepTimeEnd) {
		SetPlayerState(WAIT);
		operation_flag_ = false;
	}
	else if (step_time > (0.0 / 60.0) && step_time <= kAdjustStepTimeMove) {
		if (wall_dist_back >= kAdjustGroundWallMaxDist) {
			player_->Move(0, 0, kAdjustStepMoveZ);
		}
		operation_flag_ = true;
	}
}

/**
 * @brief �U�����
 */
void Player::AttackWaitState() {

	if (player_state_ != ATTACK_WAIT)
		return;

	auto attack_time = player_->GetTrackPosition(ATTACK_WAIT);

	if (attack_time >= kAdjustAttackWaitTimeEnd) {
			SetPlayerState(ATTACK_WAITBACK);
			hit_judge_ = false;
			ef_flag_ = true;
			operation_flag_ = false;
	}

	else if (attack_time >= kAdjustAttackWaitTimeOff && attack_time < kAdjustAttackWaitTimeEnd) {
		player_hit_flag_ = false;
	}

	else if (attack_time >= kAdjustAttackWaitTimeReserve && attack_time < kAdjustAttackWaitTimeOn) {
		player_->Move(0, 0, kAdjustAttackWaitMoveZ);
	}

	else if (attack_time < kAdjustAttackWaitTimeReserve) {

		if (ef_flag_ == true) {
			effectmanager().SlashEffectPlay(*this);
			ef_flag_ = false;
		}
		hit_judge_ = true;
		player_hit_flag_ = true;
		operation_flag_ = true;
	}
}

/**
 * @brief �U���i�߂�j���
 */
void Player::AttackWaitBackState() {

	if (player_state_ != ATTACK_WAITBACK)
		return;

	auto attack_back_time = player_->GetTrackPosition(ATTACK_WAITBACK);

	if (attack_back_time >= (39.0 / 60.0)) {
		SetPlayerState(WAIT);
	}

	else {
		if (pad_y_y_ != 0 || pad_x_x_ != 0) {
			SetPlayerState(WAIT);
		}
	}
}

/**
 * @brief �_���[�W��ԂɑJ�ڂ�����
 * @param[in] (knockbackVector) �J�����N���X
 * @param[in] (enemy) �U�����󂯂��G�̏��
 */
void Player::PlayerDamageSwitch(Vector3& knockbackVector, std::shared_ptr<Enemy> enemy) {
	enemy_front_ = knockbackVector;
	enemy_front_.y = 0;
	enemy_front_ = Vector3_Normalize(enemy_front_);
	enemy_ = enemy;
	damage_flag_ = true;
	operation_flag_ = true;
	SetPlayerState(DAMAGE);
}

/**
 * @brief �_���[�W���
 */
void Player::DamageState() {

	if (player_state_ != DAMAGE)
		return;

	ui_manager().DamageHpCount();
	auto attack_damage_time = player_->GetTrackPosition(DAMAGE);

	if (attack_damage_time >= kAdjustAttackDamageTimeEnd) {
		SetPlayerState(WAIT);
		operation_flag_ = false;
	}
}

/**
 * @brief �ʏ��Ԃɂ��玟�̏�ԂɑJ�ڂ�����
 * @param[in] (camera_main) �J�����N���X
 * @param[in] (pad_buffer) �Q�[���p�b�h�̏��擾
 * @param[in] (pad_state) �Q�[���p�b�h�̏��擾
 */
void Player::PlayerMoveSwitch(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state) {

	if (death_flag_ == false) {
		if (enemy_ != nullptr) {
			if (enemy_->GetAttackFlag() == true && player_state_ == DAMAGE) {
				anime_pos_ += enemy_front_ * -kAdjustAttackDamageMove;
				player_->SetPosition(anime_pos_);
			}

			else if (enemy_->GetAttackFlag() == true && player_state_ == WAIT) {
				anime_pos_ += enemy_front_ * -kAdjustAttackDamageMove;
				player_->SetPosition(anime_pos_);
				if (pad_y_y_ != 0 || pad_x_x_ != 0) {
					enemy_ = nullptr;
				}

				else if (pad_buffer.IsPressed(GamePad_Button2))
				{
					if (player_state_ != DASH) {
						enemy_ = nullptr;
						SetPlayerState(ATTACK_WAIT);
					}
				}

				else if (pad_buffer.IsPressed(GamePad_Button5)) {
					enemy_ = nullptr;
					SetPlayerState(STEP);
				}
			}

			else if (enemy_->GetEnemyState() == PUNCH) {
				anime_pos_ += enemy_front_ * -kAdjustAttackDamageMove;
				player_->SetPosition(anime_pos_);
			}

			else {
				enemy_ = nullptr;
			}
		}

		else {

			if (operation_flag_ == false) {

				if (player_state_ != DEATHBLOW &&  player_state_ != ATTACK_DASH && player_state_ != DEATHBLOW_BACK && player_state_ != STEP ) {
					//�X�e�B�b�N��|���Ă���ꍇ
					if (pad_y_y_ != 0 || pad_x_x_ != 0) {
						//�J�����̐i�s�x�N�g���擾
						auto camera_dir = camera_main.GetCamera().GetFrontVector();
						camera_dist_ = MathHelper_Atan2(camera_dir.z, camera_dir.x);
						//y���W�͎g�p���Ȃ��̂�0�ɂ��Ă���
						camera_dir.y = 0;
						//�i�s�x�N�g���𐳋K��
						camera_dir = Vector3_Normalize(camera_dir);
						//���K�������x�N�g������J�����s����擾����
						Matrix   mat = Matrix_CreateLookAt(Vector3(0, 0, 0), camera_dir, Vector3_Up);
						//�J�����s��̋t�s�񂩂�r���[�s������߂�
						mat = Matrix_Invert(mat);
						//�r���[�s�񂩂�N�H�[�^�j�I���i�p�x�j�ɕϊ�
						camer_qt_ = Quaternion_CreateFromRotationMatrix(mat);
						//�J�����̌����Ƀv���C���[����������
						player_->SetDirection(camer_qt_);
						//�X�e�B�b�N�̌X���ɍ��킹�ăv���C���[�̎�����] ������
						player_->Rotation(0, angle_ + kAdjustPlayerRota, 0);
					}

					//�X�e�B�b�N��|���Ă��Ȃ��ꍇ
					if (pad_angle_ == 0) {
						SetPlayerState(WAIT);
					}

					else if (pad_angle_ < kAdjustPlayerWalkPadAngle && pad_angle_ > 0) {
						if (wall_bolck_ == false && ground_block_ == false) {
							player_->Move(0, 0, pad_angle_ / kAdjustPlayerWalkMove);
							player_->Move(0, kAdjustGroundDistRay - dist_, 0);
						}
						SetPlayerState(WALK);
					}

					else {
						if (wall_bolck_ == false && ground_block_ == false) {
							player_->Move(0, 0, pad_angle_ / kAdjustPlayerRunMove);
							/*player_->Move(0, ground_dist_ - dist_, 0);*/
						}
						SetPlayerState(RUN);
					}

					if (player_state_ == WAIT || player_state_ == WALK || player_state_ == RUN) {

						if (lb_ > 0) {
							if (pad_angle_ != 0)
							{
								SetPlayerState(DASH);
							}
						}

						else if (pad_buffer.IsPressed(GamePad_Button6)) {
							if (ui_manager().GetSpGauge() >= sp_max) {
								ui_manager().SpGaugeDown();
								SetPlayerState(DEATHBLOW);
							}
						}

						else if (pad_buffer.IsPressed(GamePad_Button2))
						{
							if (player_state_ != DASH) {
								SetPlayerState(ATTACK_WAIT);
							}
						}

						else if (pad_buffer.IsPressed(GamePad_Button5)) {
							SetPlayerState(STEP);
						}
					}
				}
			}
		}
	}
}

/**
 * @brief ���S���
 */
void Player::DeathState(EnemyManager& enemy_manager) {
	if (player_state_ != DEATH)
		return;

	auto death_damage_time = player_->GetTrackPosition(DEATH);
	ui_manager().AllDelteObserver(this);
	time_manager().AllDelteObserver(this);
	enemy_manager.AllDelteObserver(this);
	death_flag_ = true;
	operation_flag_ = true;
}

/**
 * @brief �v���C���[�̏�Ԃ�؂�ւ��邽�߂̏���
 * @param[in] (new_state) �v���C���[�̏��
 */
void Player::SetPlayerState(int new_state)
{
	player_->SetTrackEnable(player_state_, FALSE);
	player_->SetTrackEnable(new_state, TRUE);

	if (new_state == DEATHBLOW || new_state == DEATHBLOW_BACK || new_state == DAMAGE || new_state == ATTACK_WAIT || new_state == ATTACK_DASH || new_state == STEP ||new_state == ATTACK_WAITBACK || new_state == ATTACK_DASHBACK) {
		player_->SetTrackPosition(new_state, 0);
	}

	player_state_ = new_state;	
}

/**
 * @brief �_���[�W���󂯂���̖��G��Ԃ��Ǘ�
 */
void Player::InvincibleTime() {

	if (damage_flag_ == true) {
		invincible_time_++;

		if (invincible_time_ >= kAdjustInvincibleTime) {
			damage_flag_ = false;
			invincible_time_ = 0;
		}
	}
}

/**
 * @brief �K�E�Z���
 */
void Player::DeathblowState()
{
	if (player_state_ != DEATHBLOW)
		return;

	auto death_blowe_time = player_->GetTrackPosition(DEATHBLOW);

	if (death_blowe_time >= kAdjustDeathBlowTimeEnd) {
		SetPlayerState(DEATHBLOW_BACK);
	}

	else if (ground_block_ == true) {
		SetPlayerState(DEATHBLOW_BACK);
	}

	else if (death_blowe_time >= kAdjustDeathBlowTimeOn){
		player_->Move(0, kAdjustGroundDistRay - dist_, kAdjustDeathBlowMoveZ);
		if (deathblow_ef_flag_ == false) {
			player_hit_flag_ = true;
			effectmanager().DeathBlowEffectPlay(*this);
			deathblow_ef_flag_ = true;
		}
		effectmanager().DeathBlowEffectMove(*this);
	}
}

/**
 * @brief �K�E�Z�i�߂�j���
 */
void Player::DeathblowBackState() {

	if (player_state_ != DEATHBLOW_BACK)
		return;

	auto death_blow_back_time = player_->GetTrackPosition(DEATHBLOW_BACK);
	player_hit_flag_ = false;
	effectmanager().DeathBlowEffectStop();

	if (death_blow_back_time >= kAdjustDeathBlowBackTimeEnd) {
		SetPlayerState(WAIT);
		deathblow_ef_flag_ = false;
	}

	else if (death_blow_back_time >= kAdjustDeathBlowBackTimeOn && death_blow_back_time < kAdjustDeathBlowBackTimeEnd) {
		player_->Move(0.0f, kAdjustGroundDistRay - dist_, -kAdjustDeathBlowBackMoveZ);
	}

}

/**
 * @brief �v���C���[��p�̉e��ݒ�
 */
inline Matrix Player::Create_Shadow_Matrix(const D3DLIGHTTYPE light_type, const Vector3& light,
	const Vector3& pos, const Vector3& shadow_offset,
	const Vector3& normal) 

	{
		D3DXVECTOR4   Light;
			Light = D3DXVECTOR4(light + kAdjustShadowLightDist - pos, 0.0f);
			::D3DXVec4Normalize(&Light, &Light);

		D3DXPLANE     Plane;
		::D3DXPlaneFromPointNormal(&Plane, &(pos + shadow_offset), &normal);

		D3DXMATRIX   matT;
		::D3DXMatrixShadow(&matT, &Light, &Plane);

		return matT;
}

/**
 * @brief �v���C���[��`��
 */
void Player::Draw()
{
	if (player_state_ == DEATH) {
		player_->Draw();
	}

	//���G��Ԃ̓_�ŏ�Ԃ̕`��
	else if (invincible_time_ % kAdjustFlashInterval == 0) {
		auto cull_mode = GraphicsDevice.GetRenderState(D3DRS_CULLMODE);
		GraphicsDevice.SetRenderState(CullMode_None);
		player_->Draw();
		GraphicsDevice.SetRenderState(D3DRS_CULLMODE, cull_mode);
		
	}

	//�v���C���[�̉e�̕`��
	GraphicsDevice.BeginShadowRendering();
	Matrix mat;
	mat = Create_Shadow_Matrix(Light_Directional, Vector3_Zero, anime_pos_, kAdjustShadowMove, Vector3_Up);
	player_->DrawShadow(mat, kAdjustShadowDepth);
	GraphicsDevice.EndShadowRendering();
}







