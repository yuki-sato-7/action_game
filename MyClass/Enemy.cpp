/**
 * @file Enemy.cpp
 * @brief 敵クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "Enemy.h"

/**
 * @brief　敵クラスを初期化する
 * @param[in] (player) プレイヤークラス
 * @param[in] (enemy_pos_) 敵の初期座標
 * @return 常にtrue
 */
bool Enemy::Initialize(Player& player,Vector3& enemy_pos_)
{
	//敵モデルの読み込み
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

	//敵モデルの衝突判定領域
	enemy_obb_.Radius = Vector3(15.0f, 40.0f, 10.0f);  //半径
	enemy_obb_.Center = enemy_->GetPosition();
	Matrix rotation   = enemy_->GetDirectionQuaternion();
	enemy_obb_.SetAxis(rotation);

	SimpleShape shape;
	shape.Type   = Shape_Box;
	shape.Depth  = enemy_obb_.Radius.x * 2;  //直径
	shape.Height = enemy_obb_.Radius.y * 2;
	shape.Width  = enemy_obb_.Radius.z * 2;

	//敵モデルの衝突判定領域
	hit_enemy_ob_ = GraphicsDevice.CreateModelFromSimpleShape(shape);
	hit_enemy_ob_->SetDirection(enemy_->GetDirectionQuaternion());
	hit_enemy_ob_->SetMaterial(mtrl);
	hit_enemy_ob_->SetPosition(enemy_obb_.Center);

	//パンチの衝突判定領域
	shape.Type   = Shape_Box;
	shape.Depth  = 20.0f;  //直径
	shape.Height = 65.0f;
	shape.Width  = 13.0f;
	punch_       = GraphicsDevice.CreateModelFromSimpleShape(shape); GraphicsDevice.SetMaterial(mtrl);

	//各アニメーションをループさせない
	enemy_->SetTrackLoopMode(ATTACK, AnimationLoopMode_Once);
	enemy_->SetTrackLoopMode(MOVE,   AnimationLoopMode_Once);
	enemy_->SetTrackLoopMode(PUNCH,  AnimationLoopMode_Once);

	//エネミーの座標
	enemy_pos_  = enemy_->GetPosition();

	//プレイヤーの座標
	player_pos_ = player.GetPlayerPos();

	//敵をプレイヤーに向かせる
	float kakudo_ = MathHelper_Atan2(player_pos_.z - enemy_pos_.z, player_pos_.x - enemy_pos_.x);
	enemy_->SetRotation(0, -kakudo_ - kAdjustEnemyRota, 0);

	//オブザーバーに追加
	time_manager().AddObserver(this);
	ui_manager().AddObserver(this);

	//各変数の初期化
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
 * @brief 更新(移動、状態遷移、衝突検出)
 * @param[in] (player) プレイヤークラス
 * @param[in] (ground) 背景座標クラス
 * @param[in] (enemy_pos_) 敵管理クラス
 */
void Enemy::Update(Player& player, Ground& ground, EnemyManager& enemy_manager)
{
	//エネミーの座標
	enemy_pos_ = enemy_->GetPosition();

	//プレイヤーの座標
	player_pos_ = player.GetPlayerPos();

	//アニメーションの再生速度調整
	enemy_->AdvanceTime(kAdjustAdvanceTimeSpeed);

	//敵とプレイヤーの距離
	player_dist_ = Vector3_Distance(player_pos_, enemy_pos_);

	//ステージのモデル取得
	ground_wall_ = ground.GetCollisionModelWall();
	ground_ = ground.GetModel();

	//地面の凹凸判定
		ground_down_dist_ = FLT_MAX;
		if (ground_->IntersectRay(Vector3(enemy_pos_.x, kAdjustGroundDist + enemy_pos_.y, enemy_pos_.z), Vector3_Down, &ground_down_dist_))
			groud_dist_ = kAdjustGroundDist - ground_down_dist_;
		else {
			groud_dist_ = 0;
		}

	//プレイヤーの向いている方向
	player_angle_ = Vector3_Normalize(player.GetPlayerModel()->GetFrontVector());

	//敵をプレイヤーの方向に向ける
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
 * @brief　パンチ状態の攻撃範囲を設定する
 * @param[in] (enemy_manager) 敵管理クラス
 */
void Enemy::PunchAreaControl(EnemyManager& enemy_manager) {

	auto& enemys      = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
	auto enemys_it    = enemys.begin();  //エネミーを先頭から調べる
	while (enemys_it != enemys.end()) {
		punch_->SetPosition(enemy_pos_ + enemy_->GetFrontVector() * -kAdjustPunchArea);
		punch_->SetDirection(enemy_->GetDirectionQuaternion());
		enemys_it++;
	}
}

/**
 * @brief　敵の衝突範囲を設定する
 */
void Enemy::HitAreaControl() {
	//エネミーの衝突判定領域をアニメーションモデルに合わせる
	hit_enemy_ob_->SetPosition(enemy_pos_);
	enemy_obb_.Center = enemy_->GetPosition();
	Matrix rotation   = enemy_->GetDirectionQuaternion();
	enemy_obb_.SetAxis(rotation);
	hit_enemy_ob_->SetDirection(enemy_->GetDirectionQuaternion());
	hit_enemy_ob_->SetPosition(enemy_obb_.Center + Vector3(0, kAdjustHitArea, 0));
}

/**
 * @brief　敵が待機状態の際の処理
 * @param[in] (enemy_manager) 敵管理クラス
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
 * @brief　敵が待機状態の際の処理
 * @param[in] (enemy_manager) 敵管理クラス
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
 * @brief　ダメージを受けた後の、サイドジャンプをするために敵同士の距離を測る処理
 * @param[in] (enemy_manager) 敵管理クラス
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
	auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
	auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
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
 * @brief　ダメージを受けた後の、ジャンプを左右、後ろに決定するための処理
 * @param[in] (enemy_manager) 敵管理クラス
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
 * @brief　ダメージを受けた後の、左サイドジャンプをするための処理
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
 * @brief　ダメージを受けた後の、右サイドジャンプをするための処理
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
 * @brief　ダメージを受けた後の、後ろサイドジャンプをするための処理
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
 * @brief　移動ジャンプの状態の処理
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
 * @brief　待機状態からプレイヤーとの処理を測り、次の状態を決定するための処理
 * @param[in] (enemy_manager) 敵管理クラス
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
 * @brief　敵の状態を切り替えるための処理
 * @param[in] (new_state) 敵の状態
 */
void Enemy::SetEnemyState(int new_state)
{
	enemy_->SetTrackEnable(enemy_state_, FALSE);
	enemy_->SetTrackEnable(new_state, TRUE);
	enemy_->SetTrackPosition(new_state, 0);
	enemy_state_ = new_state;
}

/**
 * @brief　ダッシュ攻撃を受けた後のダメージ状態
 * @param[in] (new_state) 敵の状態
 */
void Enemy::HeavyDamageState(EnemyManager& enemy_manager) {

	if (enemy_state_ != HEAVY_DAMAGE)
		return;

	enemy_pos_.y = 0.0f;  //敵のy座標を0にする
	enemy_->SetPosition(enemy_pos_); //敵の座標再セットする

	if (hit_flag_ == true) {
		auto enemy_damage_time = enemy_->GetTrackPosition(HEAVY_DAMAGE);
		if (se_flag_ == false) {     //ヒットSEを鳴らす
			rotation_flag_ = false;
			Vector3 ene_pos = enemy_->GetPosition();
			ene_pos += player_angle_ * kAdjustHeavyDamagePos;
			enemy_->SetPosition(ene_pos);
			se_manager().HitSe();
			se_flag_ = true;
		}

		if (enemy_damage_time >= kAdjustHeavyDamageTimeEnd) {  //ダメージ状態から復帰したらサイドジャンプ状態に移行する
			SetEnemyState(SIDE_JUMP);
			SideJumpState(enemy_manager);
			rotation_flag_ = true;
		}
	}
}

/**
 * @brief　通常攻撃を受けた後のダメージ状態
 */
void Enemy::WeakDamageState() {

	if (enemy_state_ != WEAK_DAMAGE)
		return;
	
	if (hit_flag_ == true) {
		auto enemy_damage_time = enemy_->GetTrackPosition(WEAK_DAMAGE);
		
		if (enemy_damage_time >= kAdjustWeakDamageTimeEnd) {   //ダメージ状態から復帰したらサイドジャンプ状態に移行する
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
 * @brief 通常攻撃状態
 * @param[in] (enemy_manager) 敵管理クラス
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
 * @brief パンチ攻撃状態
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
 * @brief ダッシュ攻撃のダメージ状態に遷移させる
 */
void Enemy::EnemyHeavyDamageSwitch() {
	hit_flag_ = true;
	se_flag_ = false;
	SetEnemyState(HEAVY_DAMAGE);
}

/**
 * @brief 通常攻撃のダメージ状態に遷移させる
 */
void Enemy::EnemyWeakDamageSwitch() {
	hit_flag_ = true;
	SetEnemyState(WEAK_DAMAGE);
}


/**
 * @brief 残りHPを管理する HPが無くなったら爆発エフェクトを出す
 */
void Enemy::HpManager() {
	if (death_flag_)
		return;

	enemy_hp_ += kAdjustDamageCount;
	if (enemy_hp_ > hp_max_) {
		death_flag_ = true;
		time_manager().RemoveObserver(this);     //オブザーバーのリストから消去する
		ui_manager().RemoveObserver(this);
		se_manager().ExplosionSePlay();
		effectmanager().ExplosionPlay(enemy_pos_);	
		survival_flag_ = true;
	}
}

/**
 * @brief 必殺技を受けた後に爆発エフェクトを出す
 */
void Enemy::DeathBolwHit() {
	if (death_flag_)
		return;

	enemy_hp_ += kAdjustDeathBlowDamageCount;
	if (enemy_hp_ > hp_max_) {
		death_flag_ = true;
		time_manager().RemoveObserver(this);   //オブザーバーのリストから消去する
		ui_manager().RemoveObserver(this);
		se_manager().ExplosionSePlay();
		effectmanager().ExplosionPlay(enemy_pos_);
		survival_flag_ = true;
	}
}

/**
 * @brief 敵を描画する
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
 * @brief 壁との距離を測定する
 * @param[in] (ground) 背景ステージクラス
 */
void Enemy::GroundDist(Ground& ground) {

	enemy_forward_direction_ = FLT_MAX;
	enemy_back_direction_ = FLT_MAX;
	enemy_left_direction_ = FLT_MAX;
	enemy_right_direction_ = FLT_MAX;

	//前方方向
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), -enemy_->GetFrontVector(), &enemy_forward_direction_);
	//後方方向
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), enemy_->GetFrontVector(), &enemy_back_direction_);
	//左方向
	ground_wall_->IntersectRay(enemy_pos_ + Vector3(0, 20, 0) - enemy_->GetRightVector(), -enemy_->GetRightVector(), &enemy_left_direction_);
	//右方向
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

