/**
 * @file Player.cpp
 * @brief プレイヤークラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "Player.h"
#include "CameraMain.h"
#include "Enemy.h"

/**
 * @brief　プレイヤークラスを初期化する
 * @return 常にtrue
 */
bool Player::Initialize(EnemyManager& enemy_manager)
{
	//プレイヤーモデルの設定
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

	//プレイヤーの攻撃判定用領域モデルの設定
	SimpleShape shape;
	shape.Type   = Shape_Box;
	shape.Width  = 50.0f;
	shape.Depth  = 40.0f;
	shape.Height = 30.0f;
	attack_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape);
	attack_area_->SetDirection(0.0f, 0.0f, 0.0f);//向き
	attack_area_->SetMaterial(mtrl);
	hit_judge_  = false;

	//プレイヤーの必殺技判定用領域モデルの設定
	SimpleShape shape3;
	shape3.Type      = Shape_Box;
	shape3.Depth     = 59.0f; 
	shape3.Height    = 45.0f;
	shape3.Width     = 37.0f;
	death_blow_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape3);
	death_blow_area_->SetDirection(0.0f, 0.0f, 0.0f);//向き
	death_blow_area_->SetMaterial(mtrl);

	//プレイヤーの衝突判定領域モデルの設定
	SimpleShape shape2;
	shape2.Type   = Shape_Box;
	shape2.Depth  = 17.0f;  //直径
	shape2.Height = 65.0f;
	shape2.Width  = 13.0f;
	hit_area_ = GraphicsDevice.CreateModelFromSimpleShape(shape2);
	hit_area_->SetDirection(player_->GetDirectionQuaternion());
	hit_area_->SetMaterial(mtrl);
	hit_area_->SetPosition(player_->GetPosition());
	GraphicsDevice.SetMaterial(mtrl);

	//各アニメーションをループさせない
	player_->SetTrackLoopMode(DEATH, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_WAIT, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_WAITBACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_DASH, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(ATTACK_DASHBACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DEATHBLOW, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DEATHBLOW_BACK, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(DAMAGE, AnimationLoopMode_Once);
	player_->SetTrackLoopMode(STEP, AnimationLoopMode_Once);

	//オブザーバーに追加
	time_manager().AddObserver(this);
	ui_manager().AddObserver(this);
	enemy_manager.AddObserver(this);
	
	//各変数の初期化
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
 * @brief 更新(移動、状態遷移、衝突検出、壁ズリ、無敵状態)
 * @param[in] (ground) 背景ステージクラス
 * @param[in] (camera_main) カメラクラス
 * @param[in] (enemy_manager) 敵管理クラス
 * @param[in] (pad_buffer) ゲームパッドの状態取得情
 * @param[in] (pad_state) ゲームパッドの状態取得
 */
void Player::Update(Ground& ground, CameraMain& camera_main, EnemyManager& enemy_manager, GamePadBuffer& pad_buffer, GamePadState& pad_state)
{

	//プレイヤーの座標
	anime_pos_ = player_->GetPosition();

	//モーションの再生スピード調整
	player_->AdvanceTime(kAdjustAdvanceTimeSpeed);

	//ステージのモデル
	ground_ = ground.GetModel();
	ground_wall_ = ground.GetCollisionModelWall();

	//地面の凹凸判定
	ground_->IntersectRay(anime_pos_ + Vector3(0, kAdjustGroundDistRay, 0), Vector3_Down, &dist_);

	//ゲームパットの判定
	pad_x_ = -(((float)pad_state.X - Axis_Center) / (Axis_Max - Axis_Center));
	pad_y_ = (((float)pad_state.Y - Axis_Center) / (Axis_Max - Axis_Center));
	lb_ = (((float)pad_state.X2 - Axis_Center) / (Axis_Max - Axis_Center));

	//四角形を円にマッピングして斜め方向に倒した時のスピードを調整する
	pad_x_x_ = pad_x_ * Math_Sqrt(1.0f - 0.5f * pad_y_ * pad_y_);
	pad_y_y_ = pad_y_ * Math_Sqrt(1.0f - 0.5f * pad_x_ * pad_x_);

	//アナログスティックの傾け具合
	pad_angle_ = Math_Sqrt(pad_x_x_ * pad_x_x_ + pad_y_y_ * pad_y_y_);

	//プレイヤーのy座標
	angle_ = MathHelper_Atan2(-float(pad_state.X - Axis_Center) / float(Axis_Max - Axis_Center),
		float(pad_state.Y - Axis_Center) / float(Axis_Max - Axis_Center));

	//進行ベクトル
	Vector3 F = player_->GetFrontVector();

	//壁までの距離測定
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


	//壁との壁ズリ
	if (wall_dist_min_ < kAdjustGroundMaxDist) {
		ground_block_ = true;
		// 内積を求める
		float  a = Vector3_Dot(-F, vec_x);
		//壁に平行なベクトルを求める
		parallel_vec_ = F + a * vec_x;
		//壁ずりの速度を設定
		if (player_state_ == WALK || player_state_ == RUN || player_state_ == DASH) {
			ground_wall_->IntersectRay(anime_pos_, parallel_vec_, &wall_dist_3_, &vec3);
			if (wall_dist_3_ > kAdjustGroundWallMaxDist) {
				anime_pos_ += parallel_vec_ * kAdjustGroundWallSpeed;
			}

		}
		//キャラにセット（覚え）させる
		player_->SetPosition(anime_pos_);
	}

	else {
		ground_block_ = false;
	}


	Vector3 front = player_->GetFrontVector();
	Vector3 normal_vector1_;  //!敵との平行ベクトル
	Vector3 normal_vector2_;
	Vector3 normal_vectorx1_;
	Vector3 normal_vectorx2_;
	float enemy_dist1_  = FLT_MAX;   //!敵との距離
	float enemy_dist2_  = FLT_MAX;
	float enemy_distx1_ = FLT_MAX;
	float enemy_distx2_ = FLT_MAX;

	if (player_state_ != DAMAGE) {
		auto& enemys = enemy_manager.GetEnemys(); //エネミーオブジェクトをもらう　配列を取得
		auto enemys_it = enemys.begin();  //エネミーを先頭から調べる
		while (enemys_it != enemys.end()) {

			if ((*enemys_it)->GetEnemyState() != WEAK_DAMAGE && (*enemys_it)->GetEnemyState() != HEAVY_DAMAGE) {                //倒れている敵とは壁ズリをしない

				(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY1, 0), front, &enemy_dist1_, &normal_vector1_);
				(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY2, 0), front, &enemy_dist2_, &normal_vector2_);

				if (enemy_dist2_ < enemy_dist1_) {
					enemy_dist1_ = enemy_dist2_;
					normal_vector1_ = normal_vector2_;
				}

				//敵との壁ズリ
				if (enemy_dist1_ < kAdjustEnemydWallMaxDist) {
					wall_bolck_ = true;
					// 内積を求める
					float  a = Vector3_Dot(-front, normal_vector1_);
					//敵に平行なベクトルを求める
					Vector3  p = front + a * normal_vector1_;
					//壁ずりの速度を設定
					if (player_state_ == WALK || player_state_ == RUN || player_state_ == DASH || player_state_ == DAMAGE) {
						//壁ズリ中の判定
						(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY1, 0), front, &enemy_distx1_, &normal_vectorx1_);
						(*enemys_it)->GetHitModel()->IntersectRay(anime_pos_ + Vector3(0, kAdjustEnemyWallDistPosY2, 0), front, &enemy_distx2_, &normal_vectorx2_);

						if (enemy_distx2_ < enemy_distx1_) {
							enemy_distx1_ = enemy_distx2_;
							normal_vectorx1_ = normal_vectorx2_;
						}

						if (enemy_distx1_ > kAdjustEnemyMinxDist) {
							anime_pos_ += p * kAdjustGroundWallSpeed;    //壁ズリ方向
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

	//spゲージの回復
	if (player_state_ != DEATHBLOW && player_state_ != DEATHBLOW_BACK) {
		ui_manager().SpGaugeUp();
	}

	PlayerMoveSwitch(camera_main, pad_buffer, pad_state);

	HitAreaControl();

	AttackAreaControl();

	InvincibleTime();
}

/**
 * @brief プレイヤーの攻撃範囲を設定する
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
 * @brief プレイヤーの衝突範囲を設定する
 */
void Player::HitAreaControl() {

	hit_area_->SetPosition(anime_pos_);
	hit_area_->SetDirection(player_->GetDirectionQuaternion());
}

/**
 * @brief ダッシュ状態
 * @param[in] (camera_main) カメラクラス
 * @param[in] (pad_buffer) ゲームパッドの状態取得情報
 * @param[in] (pad_state) ゲームパッドの状態取得
 */
void Player::DashState(CameraMain& camera_main, GamePadBuffer& pad_buffer, GamePadState& pad_state) {

	if (player_state_ != DASH)
		return;

	if (operation_flag_ == false) {
		//スティックを倒している場合
		if (pad_y_y_ != 0 || pad_x_x_ != 0) {
			//カメラの進行ベクトル取得
			auto camera_dir = camera_main.GetCamera().GetFrontVector();
			//y座標は使用しないので0にしておく
			camera_dir.y = 0;
			//進行ベクトルを正規化
			camera_dir = Vector3_Normalize(camera_dir);
			//正規化したベクトルからビュー行列を取得する
			Matrix   mat = Matrix_CreateLookAt(Vector3_Zero, camera_dir, Vector3_Up);
			//ビュー行列の逆行列からワールド行列を求める
			mat = Matrix_Invert(mat);
			//ワールド行列からクォータニオン（角度）に変換
			camer_qt_ = Quaternion_CreateFromRotationMatrix(mat);
			//カメラの向きにプレイヤーを向かせる
			player_->SetDirection(camer_qt_);
			//スティックの傾きに合わせてプレイヤーの軸を回転させる
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
 * @brief ダッシュ攻撃状態
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
 * @brief ダッシュ攻撃（戻り）状態
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
 * @brief 回避状態
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
 * @brief 攻撃状態
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
 * @brief 攻撃（戻り）状態
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
 * @brief ダメージ状態に遷移させる
 * @param[in] (knockbackVector) カメラクラス
 * @param[in] (enemy) 攻撃を受けた敵の情報
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
 * @brief ダメージ状態
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
 * @brief 通常状態にから次の状態に遷移させる
 * @param[in] (camera_main) カメラクラス
 * @param[in] (pad_buffer) ゲームパッドの情報取得
 * @param[in] (pad_state) ゲームパッドの情報取得
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
					//スティックを倒している場合
					if (pad_y_y_ != 0 || pad_x_x_ != 0) {
						//カメラの進行ベクトル取得
						auto camera_dir = camera_main.GetCamera().GetFrontVector();
						camera_dist_ = MathHelper_Atan2(camera_dir.z, camera_dir.x);
						//y座標は使用しないので0にしておく
						camera_dir.y = 0;
						//進行ベクトルを正規化
						camera_dir = Vector3_Normalize(camera_dir);
						//正規化したベクトルからカメラ行列を取得する
						Matrix   mat = Matrix_CreateLookAt(Vector3(0, 0, 0), camera_dir, Vector3_Up);
						//カメラ行列の逆行列からビュー行列を求める
						mat = Matrix_Invert(mat);
						//ビュー行列からクォータニオン（角度）に変換
						camer_qt_ = Quaternion_CreateFromRotationMatrix(mat);
						//カメラの向きにプレイヤーを向かせる
						player_->SetDirection(camer_qt_);
						//スティックの傾きに合わせてプレイヤーの軸を回転 させる
						player_->Rotation(0, angle_ + kAdjustPlayerRota, 0);
					}

					//スティックを倒していない場合
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
 * @brief 死亡状態
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
 * @brief プレイヤーの状態を切り替えるための処理
 * @param[in] (new_state) プレイヤーの状態
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
 * @brief ダメージを受けた後の無敵状態を管理
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
 * @brief 必殺技状態
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
 * @brief 必殺技（戻り）状態
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
 * @brief プレイヤー専用の影を設定
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
 * @brief プレイヤーを描画
 */
void Player::Draw()
{
	if (player_state_ == DEATH) {
		player_->Draw();
	}

	//無敵状態の点滅状態の描画
	else if (invincible_time_ % kAdjustFlashInterval == 0) {
		auto cull_mode = GraphicsDevice.GetRenderState(D3DRS_CULLMODE);
		GraphicsDevice.SetRenderState(CullMode_None);
		player_->Draw();
		GraphicsDevice.SetRenderState(D3DRS_CULLMODE, cull_mode);
		
	}

	//プレイヤーの影の描画
	GraphicsDevice.BeginShadowRendering();
	Matrix mat;
	mat = Create_Shadow_Matrix(Light_Directional, Vector3_Zero, anime_pos_, kAdjustShadowMove, Vector3_Up);
	player_->DrawShadow(mat, kAdjustShadowDepth);
	GraphicsDevice.EndShadowRendering();
}







