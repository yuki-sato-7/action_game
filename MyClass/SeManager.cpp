/**
 * @file Se_Manager.cpp
 * @brief SE.BGM�Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "SeManager.h"
#include "Player.h"

/**
 * @brief SE.BGM�Ǘ��N���X������������
 * @return ���true
 */
bool SeManager::Initialize()
{
	//�eSE,BGM�̓ǂݍ���
	if (hit_se_ == nullptr) {  //��x�ǂ񂾂�ǂݍ��܂Ȃ�
		hit_se_         = SoundDevice.CreateSoundFromFile(_T("Se/hit_bgm.wav"));
		punch_se_       = SoundDevice.CreateSoundFromFile(_T("Se/enemy_punch.wav"));
		explosion_se_   = SoundDevice.CreateSoundFromFile(_T("Se/enmy_explosion.wav"));
		main_bgm_       = SoundDevice.CreateMusicFromFile(_T("Se/main_bgm.wav"));
		select_se_      = SoundDevice.CreateSoundFromFile(_T("Se/select_se.wav"));
		op_bgm_         = SoundDevice.CreateMusicFromFile(_T("Se/op_bgm.wav"));
		game_over_bgm_  = SoundDevice.CreateMusicFromFile(_T("Se/over_bgm.wav"));
		game_clear_bgm_ = SoundDevice.CreateMusicFromFile(_T("Se/clear_bgm.wav"));
	}

	return true;
}

/**
 * @brief OPBGM���Đ�����
 */
void SeManager::OpBgmPlay() {
	op_bgm_->Play();
}

/**
 * @brief OPBGM���~����
 */
void SeManager::OpBgmStop() {
	op_bgm_->Stop();
}

/**
 * @brief �Q�[���N���ABGM���Đ�����
 */
void SeManager::GcBgmPlay() {
	game_clear_bgm_->Play();
}

/**
 * @brief �Q�[���N���ABGM���~����
 */
void SeManager::GcBgmStop() {
	game_clear_bgm_->Stop();
}

/**
 * @brief ���艹���Đ�����
 */
void SeManager::SelectSePlay() {

	select_se_->Play();
}

/**
 * @brief �q�b�g�����Đ�����
 */
void SeManager::HitSe()
{
	hit_se_->Play();
}

/**
 * @brief ���C��BGM���Đ�����
 */
void SeManager::MainBgmPlay()
{
	main_bgm_->Play();
}

/**
 * @brief ���C��BGM���~����
 */
void SeManager::MainBgmStop()
{
    main_bgm_->Stop();
}

/**
 * @brief �Q�[���I�[�o�[BGM���Đ�����
 * @param[in] (player) �v���C���[�Ǘ��N���X
 */
void SeManager::GameOverBgmPlay()
{
    game_over_bgm_->Play();
}

/**
 * @brief �Q�[���I�[�o�[BGM���~����
 * @param[in] (player) �v���C���[�Ǘ��N���X
 */
void SeManager::GameOverBgmStop()
{
	game_over_bgm_->Stop();
}

/**
 * @brief �p���`�����Đ�����
 */
void SeManager::PunchSePlay()
{
	punch_se_->Play();
}

/**
 * @brief �G�̔��������Đ�����
 */
void SeManager::ExplosionSePlay()
{
	explosion_se_->Play();
}