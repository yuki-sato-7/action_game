/**
 * @file Effeksser_Manager.cpp
 * @brief �G�t�F�N�g�Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "EffeksserManager.h"
#include "Player.h"
#include "CameraMain.h"
#include "EnemyManager.h"

/**
 * @brief �G�t�F�N�g�Ǘ��N���X������������
 * @param[in] (camara_) �J�����N���X
 * @param[in] (player_) �v���C���[�N���X
 * @return ���true
 */
bool EffeksserManager::Initialize(CameraMain& camara_, Player& player_)
{                    	
	Effekseer.Attach(GraphicsDevice);

	//�e�G�t�F�N�g�̓ǂݍ���	
	slash_effect_      = Effekseer.CreateEffectFromFile(_T("Effekseer/slash/slash.efk"));
	dash_slash_effect_ = Effekseer.CreateEffectFromFile(_T("Effekseer/dash/dash.efk"));
	death_blow_        = Effekseer.CreateEffectFromFile(_T("Effekseer/death_blow/death_blow.efk"));
	explosion_effect_  = Effekseer.CreateEffectFromFile(_T("Effekseer/explosion/explosion.efk"));
	hit_effect_        = Effekseer.CreateEffectFromFile(_T("Effekseer/hit/hit.efk"));
	
	//�G�t�F�N�g���J�����ɃZ�b�g����
	Effekseer.SetCamera(camara_.GetCamera());
	
	return true;
}

/**
 * @brief �X�V�i�G�t�F�N�g���J�����ɓ��e����j
 * @param[in] (camara_) �J�����N���X
 */
void EffeksserManager::Update(CameraMain& camara_)
{
	Effekseer.Update();
	Effekseer.SetCamera(camara_.GetCamera());

	dash_ = dash_slash_effect_->GetPosition(dash_slash_effect_effect_ID);
}

/**
 * @brief�@�U���G�t�F�N�g���Đ�����
 * @param[in] (player) �v���C���[�N���X
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
 * @brief�@�q�b�g�G�t�F�N�g���Đ�����
 * @param[in] (player) �v���C���[�N���X
 * @param[in] (enemy_pos) �G�̍��W
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
 * @brief�@�_�b�V���U���G�t�F�N�g���Đ�����
 * @param[in] (player) �v���C���[�Ǘ��N���X
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
 * @brief�@�K�E�Z�G�t�F�N�g���Đ�����
 * @param[in] (player) �v���C���[�N���X
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
 * @brief�@�K�E�Z�G�t�F�N�g���~����
 */
void EffeksserManager::DeathBlowEffectStop()
{
	death_blow_->Stop(death_blow_effect_effect_id_);
}

/**
 * @brief�@�K�E�Z�G�t�F�N�g���v���C���[�ɉ����Ĉړ�������
 * @param[in] (player) �v���C���[�N���X
 */
void EffeksserManager::DeathBlowEffectMove(Player& player)
{
	death_blow_->Move(death_blow_effect_effect_id_, player.GetPlayerModel()->GetFrontVector() * kEffectAdjustDeathBlowMove);
}

/**
 * @brief�@�G�̔����G�t�F�N�g���Đ�����
 * @param[in] (enemy_pos) ���S�����G�̍��W
 */
void EffeksserManager::ExplosionPlay(Vector3 enemy_pos)
{
	int explosion_effect_effect_ID = explosion_effect_->Play(enemy_pos);
	explosion_effect_->SetScale(explosion_effect_effect_ID, kEffectAdjustExplosioScale);
}

/**
 * @brief�@�G�t�F�N�g��`�悷��
 * @param[in] (camara_) �J�����N���X
 */
void EffeksserManager::Draw(CameraMain& camara_)
{
	Effekseer.Draw();
}


