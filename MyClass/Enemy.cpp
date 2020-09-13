/**
 * @file Enemy.cpp
 * @brief �G�N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "Enemy.h"

/**
 * @brief�@�G�N���X������������
 * @param[in] (player) �v���C���[�N���X
 * @param[in] (enemy_pos_) �G�̏������W
 * @return ���true
 */
bool Enemy::Initialize(Player& player,Vector3& enemy_pos_)
{
	//�G���f���̓ǂݍ���
	enemy_ = GraphicsDevice.CreateAnimationModelFromFile(_T("Enemy/enemy.X"));
	enemy_->SetScale(1.0f);
	enemy_->SetPosition(enemy_pos_);

	Material mtrl;
	mtrl.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	mtrl.Ambient  = Color(0.25f, 0.25f, 0.25f);
	mtrl.Specular = Color(1.f, 1.f, 1.f);
	mtrl.Power    = 1.0f;
	mtrl.Emissive = Color(0.f, 0.f, 0.f);
	enemy_->SetMaterial(mtrl);
	GraphicsDevice.SetMaterial(mtrl);

	//�G���f���̏Փ˔���̈�
	enemy_obb_.Radius = Vector3(15.0f, 40.0f, 10.0f);  //���a
	enemy_obb_.Center = enemy_->GetPosition();
	Matrix rotation   = enemy_->GetDirectionQuaternion();
	enemy_obb_.SetAxis(rotation);

	SimpleShape shape;
	shape.Type   = Shape_Box;
	shape.Depth  = enemy_obb_.Radius.x * 2;  //���a
	shape.Height = enemy_obb_.Radius.y * 2;
	shape.Width  = enemy_obb_.Radius.z * 2;

	//�G���f���̏Փ˔���̈�
	hit_enemy_ob_ = GraphicsDevice.CreateModelFromSimpleShape(shape);
	hit_enemy_ob_->SetDirection(enemy_->GetDirectionQuaternion());
	hit_enemy_ob_->SetMaterial(mtrl);
	hit_enemy_ob_->SetPosition(enemy_obb_.Center);

	//�p���`�̏Փ˔���̈�
	shape.Type   = Shape_Box;
	shape.Depth  = 20.0f;  //���a
	shape.Height = 65.0f;
	shape.Width  = 13.0f;
	punch_       = GraphicsDevice.CreateModelFromSimpleShape(shape); GraphicsDevice.SetMaterial(mtrl);

	//�e�A�j���[�V���������[�v�����Ȃ�
	enemy_->SetTrackLoopMode(ATTACK, AnimationLoopMode_Once);
	enemy_->SetTrackLoopMode(MOVE,   AnimationLoopMode_Once);
	enemy_->SetTrackLoopMode(PUNCH,  AnimationLoopMode_Once);

	//�G�l�~�[�̍��W
	enemy_pos_  = enemy_->GetPosition();

	//�v���C���[�̍��W
	player_pos_ = player.GetPlayerPos();

	//�G���v���C���[�Ɍ�������
	float kakudo_ = MathHelper_Atan2(player_pos_.z - enemy_pos_.z, player_pos_.x - enemy_pos_.x);
	enemy_->SetRotation(0, -kakudo_ - kAdjustEnemyRota, 0);

	//�I�u�U�[�o�[�ɒǉ�
	time_manager().AddObserver(this);
	ui_manager().AddObserver(this);

	//�e�ϐ��̏�����
	enemy_state_          = WAITING;	
	SetEnemyState(MOVE);
	enemy_hp_             = 0.0f;
	wait_dist_            = 200.0f;
	hp_max_               = 3.0f;

	hit_flag_             = false;
	punch_se_flag_        = false;
	se_flag_              = false;
	rotation_flag_        = true;
	death_flag_           = false;
	attack_flag_          = false;
	survival_flag_        = false;
	hit_se_flag_          = false;
	left_side_jump_flag_  = false;
	right_side_jump_flag_ = false;
	side_jump_flag_       = false;
	back_side_jump_flag_  = false;
	forward_move_flag_    = false;
	back_move_flag_       = false;
    left_move_flag_       = false;
	right_move_flag_      = false;

	return true;
}

/**
 * @brief �X�V(�ړ��A��ԑJ�ځA�Փˌ��o)
 * @param[in] (player) �v���C���[�N���X
 * @param[in] (ground) �w�i���W�N���X
 * @param[in] (enemy_pos_) �G�Ǘ��N���X
 */
void Enemy::Update(Player& player, Ground& ground, EnemyManager& enemy_manager)
{
	//�G�l�~�[�̍��W
	enemy_pos_ = enemy_->GetPosition();

	//�v���C���[�̍��W
	player_pos_ = player.GetPlayerPos();

	//�A�j���[�V�����̍Đ����x����
	enemy_->AdvanceTime(kAdjustAdvanceTimeSpeed);

	//�G�ƃv���C���[�̋���
	player_dist_ = Vector3_Distance(player_pos_, enemy_pos_);

	//�X�e�[�W�̃��f���擾
	ground_wall_ = ground.GetCollisionModelWall();
	ground_ = ground.GetModel();

	//�n�ʂ̉��ʔ���
		ground_down_dist_ = FLT_MAX;
		if (ground_->IntersectRay(Vector3(enemy_pos_.x, kAdjustGroundDist + enemy_pos_.y, enemy_pos_.z), Vector3_Down, &ground_down_dist_))
			groud_dist_ = kAdjustGroundDist - ground_down_dist_;
		else {
			groud_dist_ = 0;
		}

	//�v���C���[�̌����Ă������
	player_angle_ = Vector3_Normalize(player.GetPlayerModel()->GetFrontVector());

	//�G���v���C���[�̕����Ɍ�����
	if (rotation_flag_ == true) {
		float kakudo = MathHelper_Atan2(player_pos_.z - enemy_pos_.z, player_pos_.x - enemy_pos_.x);
		enemy_->SetRotation(0, -kakudo - kAdjustEnemyRota, 0);
	}

	HitAreaControl();

	GroundDist(ground);

	switch (enemy_state_) {
	case MOVE:
		EnemyMove();
		break;

	case PUNCH:
		PunchState();
		break;

	case WAITING:
		WaitState(enemy_manager);
		break;

	case SIDE_JUMP:
		SideJumpState(enemy_manager);
		break;

	case WEAK_DAMAGE:
		WeakDamageState();
		break;

	case HEAVY_DAMAGE:
		HeavyDamageState(enemy_manager);
		break;

	case ATTACK:
		AttackState(enemy_manager);
		break;

	case END_WAITING:
		EndWaitState();
		break;

	case NORMAL:
		EnemyNormalSwitch(enemy_manager);
		break;

	case TIME_OVER_:
	case PLAYER_DEATH_:
		SetEnemyState(END_WAITING);
		break;
	}

	PunchAreaControl(enemy_manager);
}

/**
 * @brief�@�p���`��Ԃ̍U���͈͂�ݒ肷��
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::PunchAreaControl(EnemyManager& enemy_manager) {

	auto& enemys      = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
	auto enemys_it    = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
	while (enemys_it != enemys.end()) {
		punch_->SetPosition(enemy_pos_ + enemy_->GetFrontVector() * -kAdjustPunchArea);
		punch_->SetDirection(enemy_->GetDirectionQuaternion());
		enemys_it++;
	}
}

/**
 * @brief�@�G�̏Փ˔͈͂�ݒ肷��
 */
void Enemy::HitAreaControl() {
	//�G�l�~�[�̏Փ˔���̈���A�j���[�V�������f���ɍ��킹��
	hit_enemy_ob_->SetPosition(enemy_pos_);
	enemy_obb_.Center = enemy_->GetPosition();
	Matrix rotation   = enemy_->GetDirectionQuaternion();
	enemy_obb_.SetAxis(rotation);
	hit_enemy_ob_->SetDirection(enemy_->GetDirectionQuaternion());
	hit_enemy_ob_->SetPosition(enemy_obb_.Center + Vector3(0, kAdjustHitArea, 0));
}

/**
 * @brief�@�G���ҋ@��Ԃ̍ۂ̏���
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::WaitState(EnemyManager& enemy_manager)
{
	if (enemy_state_ != WAITING)
		return;

	auto wait_time = enemy_->GetTrackPosition(WAITING);
	EnemyDist(enemy_manager);

	if (forward_1_dist_ > forward_2_dist_) {
		forward_1_dist_ = forward_2_dist_;
	}

	if (forward_1_dist_ > wait_dist_) {
		SetEnemyState(NORMAL);
		return;
	}

	if (wait_time >= kAdjustWaitTimeEnd) {
		SetEnemyState(WAITING);
	}
}

/**
 * @brief�@�G���ҋ@��Ԃ̍ۂ̏���
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::EndWaitState()
{
	if (enemy_state_ != END_WAITING)
		return;

	auto end_wait_time = enemy_->GetTrackPosition(END_WAITING);
	ui_manager().AllDelteObserver(this);
	time_manager().AllDelteObserver(this);

	if (end_wait_time >= kAdjustWaitTimeEnd) {
		SetEnemyState(END_WAITING);
	}
}

/**
 * @brief�@�_���[�W���󂯂���́A�T�C�h�W�����v�����邽�߂ɓG���m�̋����𑪂鏈��
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::EnemyDist(EnemyManager& enemy_manager) {

	left_dist_max_   = FLT_MAX;
	right_dist_max_  = FLT_MAX;
	right_side_dist_ = FLT_MAX;
	left_side_dist_  = FLT_MAX;
	back_dist_       = FLT_MAX;
	forward_1_dist_  = FLT_MAX;
	forward_2_dist_  = FLT_MAX;

	auto wait_time = enemy_->GetTrackPosition(WAITING);
	auto& enemys = enemy_manager.GetEnemys(); //�G�l�~�[�I�u�W�F�N�g�����炤�@�z����擾
	auto enemys_it = enemys.begin();  //�G�l�~�[��擪���璲�ׂ�
	while (enemys_it != enemys.end()) {

		if ((*enemys_it).get() == this) {
			enemys_it++;
			continue;
		}

		if ((*enemys_it)->GetEnemyState() != HEAVY_DAMAGE && (*enemys_it)->GetEnemyState() != WEAK_DAMAGE && (*enemys_it)->GetEnemyState() != SIDE_JUMP) {
			(*enemys_it)->GetHitModel()->IntersectRay(enemy_pos_ + Vector3(0, kAdjustEnemyDistPosY, 0), enemy_->GetRightVector(), &right_side_dist_);
			(*enemys_it)->GetHitModel()->IntersectRay(enemy_pos_ + Vector3(0, kAdjustEnemyDistPosY, 0), -enemy_->GetRightVector(), &left_side_dist_);
			(*enemys_it)->GetHitModel()->IntersectRay(enemy_pos_ + Vector3(0, kAdjustEnemyDistPosY, 0) - enemy_->GetRightVector() * kAdjustEnemyDistFrontVec - enemy_->GetFrontVector() * kAdjustEnemyDistFrontVec, -enemy_->GetFrontVector(), &forward_1_dist_);
			(*enemys_it)->GetHitModel()->IntersectRay(enemy_pos_ + Vector3(0, kAdjustEnemyDistPosY, 0) + enemy_->GetRightVector() * kAdjustEnemyDistFrontVec - enemy_->GetFrontVector() * kAdjustEnemyDistFrontVec, -enemy_->GetFrontVector(), &forward_2_dist_);
			(*enemys_it)->GetHitModel()->IntersectRay(enemy_pos_ + Vector3(0, kAdjustEnemyDistPosY, 0), enemy_->GetFrontVector(), &back_dist_);

			if (left_dist_max_ > left_side_dist_) {
				left_dist_max_ = left_side_dist_;
			}

			if (right_dist_max_ > right_side_dist_) {
				right_dist_max_ = right_side_dist_;
			}
		}
		enemys_it++;
	}
}

/**
 * @brief�@�_���[�W���󂯂���́A�W�����v�����E�A���Ɍ��肷�邽�߂̏���
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::SideJumpState(EnemyManager& enemy_manager) {

	if (enemy_state_ != SIDE_JUMP)
		return;

	rotation_flag_ = false;

	EnemyDist(enemy_manager);

	if (side_jump_flag_ == false){

		if (left_dist_max_ > kAdjustSideJumpMaxDist && left_move_flag_ == true) {
			left_side_jump_flag_ = true;
			side_jump_flag_ = true;
		}

		else if (right_dist_max_ > kAdjustSideJumpMaxDist && right_move_flag_ == true) {
			right_side_jump_flag_ = true;
			side_jump_flag_ = true;
		}

		else {
			back_side_jump_flag_ = true;
			side_jump_flag_ = true;
		}
	}

	if (left_side_jump_flag_ == true) {
		LeftSideJumpState();
	}

	else if (right_side_jump_flag_ == true) {
		RightSideJumpState();
	}
	
	else if (back_side_jump_flag_ == true) {
		BackSideJumpState();
	}
}

/**
 * @brief�@�_���[�W���󂯂���́A���T�C�h�W�����v�����邽�߂̏���
 */
void Enemy::LeftSideJumpState() {

	auto side_jump_time = enemy_->GetTrackPosition(SIDE_JUMP);

	if (side_jump_time >= kAdjustJumpTimeEnd) {
		hit_flag_ = false;
		rotation_flag_ = true;
		side_jump_flag_ = false;
		left_side_jump_flag_ = false;
		SetEnemyState(NORMAL);
	}

	else if (side_jump_time >= kAdjustJumpTimeRise && side_jump_time < kAdjustJumpTimeFall) {
		enemy_->Move(-kAdjustJumpMoveX, -kAdjustJumpMoveY, 0);
	}

	else if (side_jump_time >= kAdjustJumpTimeTakeOff && side_jump_time < kAdjustJumpTimeRise) {
		enemy_->Move(-kAdjustJumpMoveX, kAdjustJumpMoveY, 0);
	}

	else
		enemy_->Move(0, groud_dist_, 0); 
}

/**
 * @brief�@�_���[�W���󂯂���́A�E�T�C�h�W�����v�����邽�߂̏���
 */
void Enemy::RightSideJumpState() {

	auto side_jump_time = enemy_->GetTrackPosition(SIDE_JUMP);

	if (side_jump_time >= kAdjustJumpTimeEnd) {
		hit_flag_ = false;
		rotation_flag_ = true;
		right_side_jump_flag_ = false;
		side_jump_flag_ = false;
		SetEnemyState(NORMAL);
	}

	else if (side_jump_time >= kAdjustJumpTimeRise && side_jump_time < kAdjustJumpTimeFall) {
		enemy_->Move(kAdjustJumpMoveX, -kAdjustJumpMoveY, 0);
	}

	else if (side_jump_time >= kAdjustJumpTimeTakeOff && side_jump_time < kAdjustJumpTimeRise) {
		enemy_->Move(kAdjustJumpMoveX, kAdjustJumpMoveY, 0);
	}

	else
		enemy_->Move(0, groud_dist_, 0);
}


/**
 * @brief�@�_���[�W���󂯂���́A���T�C�h�W�����v�����邽�߂̏���
 */
void Enemy::BackSideJumpState() {

	auto side_jump_time = enemy_->GetTrackPosition(SIDE_JUMP);

	if (side_jump_time >= kAdjustJumpTimeEnd) {
		hit_flag_ = false;
		rotation_flag_ = true;
		back_side_jump_flag_ = false;
		side_jump_flag_ = false;
		SetEnemyState(NORMAL);
	}

	else if (side_jump_time >= kAdjustJumpTimeRise && side_jump_time < kAdjustJumpTimeFall) {
		enemy_->Move(0, -kAdjustJumpMoveY, kAdjustJumpMoveZ);
	}

	else if (side_jump_time >= kAdjustJumpTimeTakeOff && side_jump_time < kAdjustJumpTimeRise) {
		enemy_->Move(0, kAdjustJumpMoveY, kAdjustJumpMoveZ);
	}

	else
		enemy_->Move(0, groud_dist_, 0);
}

/**
 * @brief�@�ړ��W�����v�̏�Ԃ̏���
 */
void Enemy::EnemyMove()
{
	if (enemy_state_ != MOVE)
		return;

	auto move_time = enemy_->GetTrackPosition(MOVE);

	rotation_flag_ = false;

	if (move_time >= kAdjustJumpTimeEnd) {
		SetEnemyState(NORMAL);
		rotation_flag_ = true;
	}

	else if (move_time >= kAdjustJumpTimeRise && move_time < kAdjustJumpTimeFall){
		enemy_->Move(0, -kAdjustJumpMoveY, -kAdjustJumpMoveZ);
	}

	else if (move_time >= kAdjustJumpTimeTakeOff && move_time < kAdjustJumpTimeRise) {
		enemy_->Move(0, kAdjustJumpMoveY, -kAdjustJumpMoveZ);
	}

	else
		enemy_->Move(0, groud_dist_, 0);
}


/**
 * @brief�@�ҋ@��Ԃ���v���C���[�Ƃ̏����𑪂�A���̏�Ԃ����肷�邽�߂̏���
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::EnemyNormalSwitch(EnemyManager& enemy_manager)
{
	if (enemy_state_ != NORMAL)
		return;

	rotation_flag_ = false;
	
	EnemyDist(enemy_manager);

	if (forward_1_dist_ > forward_2_dist_) {
		forward_1_dist_ = forward_2_dist_;
	}

	if (forward_1_dist_ < wait_dist_) {
		SetEnemyState(WAITING);
	}

	rotation_flag_ = true;
	if (enemy_state_ == WAITING)
		return;

	if (player_dist_ > kAdjustMoveDist) {
		if(forward_move_flag_ == true)
		SetEnemyState(MOVE);
		return;
	}

	else if (player_dist_ >= kAdjustAttackDist && player_dist_ < kAdjustMoveDist) {
		if (forward_move_flag_ == true)
		SetEnemyState(ATTACK);
		return;
	}

	SetEnemyState(PUNCH);
}

/**
 * @brief�@�G�̏�Ԃ�؂�ւ��邽�߂̏���
 * @param[in] (new_state) �G�̏��
 */
void Enemy::SetEnemyState(int new_state)
{
	enemy_->SetTrackEnable(enemy_state_, FALSE);
	enemy_->SetTrackEnable(new_state, TRUE);
	enemy_->SetTrackPosition(new_state, 0);
	enemy_state_ = new_state;
}

/**
 * @brief�@�_�b�V���U�����󂯂���̃_���[�W���
 * @param[in] (new_state) �G�̏��
 */
void Enemy::HeavyDamageState(EnemyManager& enemy_manager) {

	if (enemy_state_ != HEAVY_DAMAGE)
		return;

	enemy_pos_.y = 0.0f;  //�G��y���W��0�ɂ���
	enemy_->SetPosition(enemy_pos_); //�G�̍��W�ăZ�b�g����

	if (hit_flag_ == true) {
		auto enemy_damage_time = enemy_->GetTrackPosition(HEAVY_DAMAGE);
		if (se_flag_ == false) {     //�q�b�gSE��炷
			rotation_flag_ = false;
			Vector3 ene_pos = enemy_->GetPosition();
			ene_pos += player_angle_ * kAdjustHeavyDamagePos;
			enemy_->SetPosition(ene_pos);
			se_manager().HitSe();
			se_flag_ = true;
		}

		if (enemy_damage_time >= kAdjustHeavyDamageTimeEnd) {  //�_���[�W��Ԃ��畜�A������T�C�h�W�����v��ԂɈڍs����
			SetEnemyState(SIDE_JUMP);
			SideJumpState(enemy_manager);
			rotation_flag_ = true;
		}
	}
}

/**
 * @brief�@�ʏ�U�����󂯂���̃_���[�W���
 */
void Enemy::WeakDamageState() {

	if (enemy_state_ != WEAK_DAMAGE)
		return;
	
	if (hit_flag_ == true) {
		auto enemy_damage_time = enemy_->GetTrackPosition(WEAK_DAMAGE);
		
		if (enemy_damage_time >= kAdjustWeakDamageTimeEnd) {   //�_���[�W��Ԃ��畜�A������T�C�h�W�����v��ԂɈڍs����
			SetEnemyState(SIDE_JUMP);
			rotation_flag_ = true;
			hit_se_flag_ = false;
		}

		else {
			if (hit_se_flag_ == false) {
				se_manager().HitSe();
				hit_se_flag_ = true;
			}
			rotation_flag_ = false;
			Vector3 ene_pos = enemy_->GetPosition();
			ene_pos += player_angle_ * kAdjustWeakDamagePos;
			enemy_->SetPosition(ene_pos);
			enemy_->Move(0.0f, groud_dist_, 0.0f);
		}
	}
}

/**
 * @brief �ʏ�U�����
 * @param[in] (enemy_manager) �G�Ǘ��N���X
 */
void Enemy::AttackState(EnemyManager& enemy_manager){

	if (enemy_state_ != ATTACK)
		return;
	
	auto enemy_attack_time = enemy_->GetTrackPosition(ATTACK);

	if (enemy_attack_time >= kAdjustAttackTimeEnd){
		SetEnemyState(NORMAL);
		rotation_flag_ = false;
	}

	else if (enemy_attack_time >= kAdjustAttackTimeOn && enemy_attack_time < kAdjustAttackTimeEnd){
		rotation_flag_ = false;
		attack_flag_ = false;
	}

	else if (enemy_attack_time >= 0) {
		attack_flag_ = true;
		enemy_->Move(0, groud_dist_, -kAdjustAttackPosZ);
		rotation_flag_ = false;
	}

}

/**
 * @brief �p���`�U�����
 */
void Enemy::PunchState() {

	if (enemy_state_ != PUNCH)
		return;

	auto enemy_punch_time = enemy_->GetTrackPosition(PUNCH);

	if (enemy_punch_time >= kAdjustPunchTimeEnd) {
		SetEnemyState(NORMAL);
		rotation_flag_ = true;
		punch_se_flag_ = false;
	}


	else if (enemy_punch_time > kAdjustPunchTimeOff) {
		attack_flag_ = false;
	}

	else if (enemy_punch_time >= kAdjustPunchTimeOn) {
		attack_flag_ = true;
	}

	else if (enemy_punch_time >= kAdjustPunchTimeReserve && enemy_punch_time < kAdjustPunchTimeOn) {
		enemy_->Move(0, groud_dist_, kAdjustPunchPosZ);
		if (punch_se_flag_ == false) {
			se_manager().PunchSePlay();
			punch_se_flag_ = true;
			rotation_flag_ = false;
		}
	}
}

/**
 * @brief �_�b�V���U���̃_���[�W��ԂɑJ�ڂ�����
 */
void Enemy::EnemyHeavyDamageSwitch() {
	hit_flag_ = true;
	se_flag_ = false;
	SetEnemyState(HEAVY_DAMAGE);
}

/**
 * @brief �ʏ�U���̃_���[�W��ԂɑJ�ڂ�����
 */
void Enemy::EnemyWeakDamageSwitch() {
	hit_flag_ = true;
	SetEnemyState(WEAK_DAMAGE);
}


/**
 * @brief �c��HP���Ǘ����� HP�������Ȃ����甚���G�t�F�N�g���o��
 */
void Enemy::HpManager() {
	if (death_flag_)
		return;

	enemy_hp_ += kAdjustDamageCount;
	if (enemy_hp_ > hp_max_) {
		death_flag_ = true;
		time_manager().RemoveObserver(this);     //�I�u�U�[�o�[�̃��X�g�����������
		ui_manager().RemoveObserver(this);
		se_manager().ExplosionSePlay();
		effectmanager().ExplosionPlay(enemy_pos_);	
		survival_flag_ = true;
	}
}

/**
 * @brief �K�E�Z���󂯂���ɔ����G�t�F�N�g���o��
 */
void Enemy::DeathBolwHit() {
	if (death_flag_)
		return;

	enemy_hp_ += kAdjustDeathBlowDamageCount;
	if (enemy_hp_ > hp_max_) {
		death_flag_ = true;
		time_manager().RemoveObserver(this);   //�I�u�U�[�o�[�̃��X�g�����������
		ui_manager().RemoveObserver(this);
		se_manager().ExplosionSePlay();
		effectmanager().ExplosionPlay(enemy_pos_);
		survival_flag_ = true;
	}
}

/**
 * @brief �G��`�悷��
 */
void Enemy::Draw()
{
	enemy_->Draw();

	GraphicsDevice.BeginShadowRendering();
	Matrix mat;
	mat = Matrix_CreateShadow(Light_Directional, kAdjustShadowLightPos, enemy_pos_, kAdjustShadowPos, Vector3_Up);
	enemy_->DrawShadow(mat, kAdjustShadowScale);
	GraphicsDevice.EndShadowRendering();
}

/**
 * @brief �ǂƂ̋����𑪒肷��
 * @param[in] (ground) �w�i�X�e�[�W�N���X
 */
void Enemy::GroundDist(Ground& ground) {

	enemy_forward_direction_ = FLT_MAX;
	enemy_back_direction_ = FLT_MAX;
	enemy_left_direction_ = FLT_MAX;
	enemy_right_direction_ = FLT_MAX;

	//�O������
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), -enemy_->GetFrontVector(), &enemy_forward_direction_);
	//�������
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), enemy_->GetFrontVector(), &enemy_back_direction_);
	//������
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), -enemy_->GetRightVector(), &enemy_left_direction_);
	//�E����
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), enemy_->GetRightVector(), &enemy_right_direction_);

	if (enemy_forward_direction_ < kAdjustGroundMaxDist) {
		forward_move_flag_ = false;
	}

	else {
		forward_move_flag_ = true;
	}

	if (enemy_back_direction_ < kAdjustGroundMaxDist) {
		back_move_flag_ = false;
	}

	else {
		back_move_flag_ = true;
	}

	if (enemy_left_direction_ < kAdjustGroundMaxDist) {
		left_move_flag_ = false;
	}

	else {
		left_move_flag_ = true;
	}

	if (enemy_right_direction_ < kAdjustGroundMaxDist) {
		right_move_flag_ = false;
	}

	else {
		right_move_flag_ = true;
	}
}

