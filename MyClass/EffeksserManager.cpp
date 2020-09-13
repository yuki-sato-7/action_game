/**
 * @file Effeksser_Manager.cpp
 * @brief エフェクト管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "EffeksserManager.h"
#include "Player.h"
#include "CameraMain.h"
#include "EnemyManager.h"

/**
 * @brief エフェクト管理クラスを初期化する
 * @param[in] (camara_) カメラクラス
 * @param[in] (player_) プレイヤークラス
 * @return 常にtrue
 */
bool EffeksserManager::Initialize(CameraMain& camara_, Player& player_)
{                    	
	Effekseer.Attach(GraphicsDevice);

	//各エフェクトの読み込み	
	slash_effect_      = Effekseer.CreateEffectFromFile(_T("Effekseer/slash/slash.efk"));
	dash_slash_effect_ = Effekseer.CreateEffectFromFile(_T("Effekseer/dash/dash.efk"));
	death_blow_        = Effekseer.CreateEffectFromFile(_T("Effekseer/death_blow/death_blow.efk"));
	explosion_effect_  = Effekseer.CreateEffectFromFile(_T("Effekseer/explosion/explosion.efk"));
	hit_effect_        = Effekseer.CreateEffectFromFile(_T("Effekseer/hit/hit.efk"));
	
	//エフェクトをカメラにセットする
	Effekseer.SetCamera(camara_.GetCamera());
	
	return true;
}

/**
 * @brief 更新（エフェクトをカメラに投影する）
 * @param[in] (camara_) カメラクラス
 */
void EffeksserManager::Update(CameraMain& camara_)
{
	Effekseer.Update();
	Effekseer.SetCamera(camara_.GetCamera());

	dash_ = dash_slash_effect_->GetPosition(dash_slash_effect_effect_ID);
}

/**
 * @brief　攻撃エフェクトを再生する
 * @param[in] (player) プレイヤークラス
 */
void EffeksserManager::SlashEffectPlay(Player& player)
{
	int slash_effect_effect_ID = slash_effect_->Play(player.GetPlayerPos() + player.GetPlayerModel()->GetFrontVector()* 30.0f);
	slash_effect_->SetScale(slash_effect_effect_ID, kEffectAdjustScale);

	Vector3 player_forward = player.GetPlayerModel()->GetFrontVector();
	effect_dir_ = Vector3_Zero;
	effect_dir_.y = MathHelper_ToRadians(-MathHelper_Atan2(player_forward.z, player_forward.x) - kEffectAdjustAngle);
	slash_effect_->SetRotation(slash_effect_effect_ID, effect_dir_);
}

/**
 * @brief　ヒットエフェクトを再生する
 * @param[in] (player) プレイヤークラス
 * @param[in] (enemy_pos) 敵の座標
 */
void EffeksserManager::HitEffectPlay(Player& player, Vector3& enemy_pos)
{
    int hit_effect_effect_ID = hit_effect_->Play(enemy_pos);
	hit_effect_->SetScale(hit_effect_effect_ID, kEffectAdjustScale);
	Vector3 player_forward = player.GetPlayerModel()->GetFrontVector();
	effect_dir_ = Vector3_Zero;
	effect_dir_.y = MathHelper_ToRadians(-MathHelper_Atan2(player_forward.z, player_forward.x) - kEffectAdjustAngle);
	hit_effect_->SetRotation(hit_effect_effect_ID, effect_dir_);
}

/**
 * @brief　ダッシュ攻撃エフェクトを再生する
 * @param[in] (player) プレイヤー管理クラス
 */
void EffeksserManager::DashSlashEffectPlay(Player& player)
{
	dash_slash_effect_effect_ID = dash_slash_effect_->Play(player.GetPlayerPos());
	dash_slash_effect_->SetScale(dash_slash_effect_effect_ID, kEffectAdjustScale);

	Vector3 player_forward = player.GetPlayerModel()->GetFrontVector();
	effect_dir_ = Vector3_Zero;
	effect_dir_.y = MathHelper_ToRadians(-MathHelper_Atan2(player_forward.z, player_forward.x) - kEffectAdjustAngle);
	dash_slash_effect_->SetRotation(dash_slash_effect_effect_ID, effect_dir_);
}

/**
 * @brief　必殺技エフェクトを再生する
 * @param[in] (player) プレイヤークラス
 */
void EffeksserManager::DeathBlowEffectPlay(Player& player)
{
	death_blow_effect_effect_id_ = death_blow_->Play(player.GetPlayerPos() + player.GetPlayerModel()->GetFrontVector() * kEffectAdjustDeathBlowPos);
	death_blow_->SetScale(death_blow_effect_effect_id_, kEffectAdjustDeathBlowScale);

	Vector3 player_forward = player.GetPlayerModel()->GetFrontVector();
	effect_dir_ = Vector3_Zero;
	effect_dir_.y = MathHelper_ToRadians(-MathHelper_Atan2(player_forward.z, player_forward.x) - kEffectAdjustAngle);
	death_blow_->SetRotation(death_blow_effect_effect_id_, effect_dir_);
}

/**
 * @brief　必殺技エフェクトを停止する
 */
void EffeksserManager::DeathBlowEffectStop()
{
	death_blow_->Stop(death_blow_effect_effect_id_);
}

/**
 * @brief　必殺技エフェクトをプレイヤーに沿って移動させる
 * @param[in] (player) プレイヤークラス
 */
void EffeksserManager::DeathBlowEffectMove(Player& player)
{
	death_blow_->Move(death_blow_effect_effect_id_, player.GetPlayerModel()->GetFrontVector() * kEffectAdjustDeathBlowMove);
}

/**
 * @brief　敵の爆発エフェクトを再生する
 * @param[in] (enemy_pos) 死亡した敵の座標
 */
void EffeksserManager::ExplosionPlay(Vector3 enemy_pos)
{
	int explosion_effect_effect_ID = explosion_effect_->Play(enemy_pos);
	explosion_effect_->SetScale(explosion_effect_effect_ID, kEffectAdjustExplosioScale);
}

/**
 * @brief　エフェクトを描画する
 * @param[in] (camara_) カメラクラス
 */
void EffeksserManager::Draw(CameraMain& camara_)
{
	Effekseer.Draw();
}


