/**
 * @file Result_Manager.cpp
 * @brief ���U���g��ʊǗ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "ResultManager.h"

/**
 * @brief ���U���g�Ǘ��N���X������������
 * @return ���true
 */
bool ResultManager::Initialize()
{
	//�e�摜�̓ǂݍ���
	game_over_       = GraphicsDevice.CreateSpriteFromFile(_T("UI/Game Over.png"));
	game_clear_      = GraphicsDevice.CreateSpriteFromFile(_T("UI/GAME CLEAR_.png"));
	time_over_       = GraphicsDevice.CreateSpriteFromFile(_T("UI/TIME UP.png"));
	return_button_   = GraphicsDevice.CreateSpriteFromFile(_T("UI/RETURN_TO_ TITLE.png"));

	//�e�ϐ��̏�����
	game_over_flag_      = false;
	game_clear_flag_     = false;
	time_over_flag_      = false;
	game_clear_bgm_flag_ = false;
	game_over_bgm_flag_  = false;
	alfa_state_          = 0.0f;

	return true;
}

/**
 * @brief ���U���g�Ǘ��N���X��`�悷��
 * @return ���true
 */
void ResultManager::Update() {

	if (game_over_flag_ == true || time_over_flag_ == true) {
		if (game_over_bgm_flag_ == false) {
			se_manager().MainBgmStop();
			se_manager().GameOverBgmPlay();
			game_over_bgm_flag_ = true;
		}
	}

	else if (game_clear_flag_ == true) {
		if (game_clear_bgm_flag_ == false) {
			se_manager().MainBgmStop();
			se_manager().GcBgmPlay();
			game_clear_bgm_flag_ = true;
		}
	}

	if (alfa_state_ == ALFA_MAX)
	{
		alfa_clear_ -= kAdjustAlfaChange_;

		if (alfa_clear_ <= 0.0f)
		{
			alfa_clear_ = 0.0f;
			alfa_state_ = ALFA_MIN;
		}
	}
	//�A���t�@���₷
	if (alfa_state_ == ALFA_MIN)
	{
		alfa_clear_ += kAdjustAlfaChange_;

		if (alfa_clear_ >= kAdjustAlfaMAX)
		{
			alfa_clear_ = kAdjustAlfaMAX;
			alfa_state_ = ALFA_MAX;
		}
	}		
}

/**
 * @brief ���U���g�Ǘ��N���X��`�悷��
 * @return ���true
 */
void ResultManager::Draw()
{
	if (game_over_flag_ == true) {
		SpriteBatch.Draw(*game_over_,     Vector3_Zero);
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
	}

	else if(game_clear_flag_ == true) {
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
		SpriteBatch.Draw(*game_clear_,    Vector3_Zero);
		
	}
	
	else if (time_over_flag_ == true) {
		SpriteBatch.Draw(*time_over_,     Vector3_Zero);
		SpriteBatch.Draw(*return_button_, Vector3_Zero, alfa_clear_);
	}

}

