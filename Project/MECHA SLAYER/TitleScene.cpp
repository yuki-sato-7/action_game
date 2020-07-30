/**
 * @file TitleScene.cpp
 * @brief �^�C�g���V�[���Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "TitleScene.h"

void TitleScene::Initialize() {

	//�e�摜�̓ǂݍ���
	tittle_                = GraphicsDevice.CreateSpriteFromFile(_T("UI/tittle_ui.png"));
	press_start_           = GraphicsDevice.CreateSpriteFromFile(_T("UI/press_start.png"));
	operation_explanation_ = GraphicsDevice.CreateSpriteFromFile(_T("UI/operation_explanation.png"));
	operation_button       = GraphicsDevice.CreateSpriteFromFile(_T("UI/main_button.png"));

	//�e�ϐ��̏�����
	tittle_count_   = 0.0f;
	tittle_state_   = 0.0f;
	alfa_state_     = 0.0f;

    next_flag_      = false;
	select_se_flag_ = false;

	se_manager().Initialize();
	se_manager().OpBgmPlay();
	InputDevice.CreateGamePad(1);

}

void TitleScene::Update() {

	//�Q�[���p�b�g�̉������u�ԁA�����Ă����Ԏ擾
	pad_state_  = GamePad(0)->GetState();
	pad_buffer_ = GamePad(0)->GetBuffer();

	FlashInterval();

	if (pad_buffer_.IsPressed(GamePad_Button8)) {
		if (select_se_flag_ == false) {
			se_manager().SelectSePlay();
			select_se_flag_ = true;
		}
		next_flag_ = true;
	}

	if (next_flag_ == true) {
		tittle_count_++;
		if (tittle_count_ >= kAdjustTittleTime) {
			tittle_state_ = kAdjustTittleState;
		}
	}

	if (tittle_state_ == kAdjustTittleState) {
		if (pad_buffer_.IsPressed(GamePad_Button8)) {
			se_manager().SelectSePlay();
			//���C���V�[���𐶐�����
			SceneManager::ChangeScene(SceneManager::MAIN);
		}
	}
}

void TitleScene::Draw3D() {

}

void TitleScene::Draw2D() {

	if (tittle_state_ == 0) {
		SpriteBatch.Draw(*tittle_,Vector3_Zero);
		SpriteBatch.Draw(*press_start_,Vector3_Zero,alfa_clear_);
	}

	else if (tittle_state_ == 1) {
		SpriteBatch.Draw(*operation_explanation_,Vector3_Zero);
		SpriteBatch.Draw(*operation_button, Vector3_Zero, alfa_clear_);
	}
}

/**
 * @brief�@������_�ł����鏈��
 */
void TitleScene::FlashInterval() {

	if (alfa_state_ == ALFA_MIN)
	{
		alfa_clear_ -= kAdjustAlfaChange_;

		if (alfa_clear_ <= 0.0f)
		{
			alfa_clear_ = 0.0f;
			alfa_state_ = ALFA_MAX;
		}
	}
	//�A���t�@���₷
	if (alfa_state_ == ALFA_MAX)
	{
		alfa_clear_ += kAdjustAlfaChange_;

		if (alfa_clear_ >= kAdjustAlfaMAX)
		{
			alfa_clear_ = kAdjustAlfaMAX;
			alfa_state_ = ALFA_MIN;
		}
	}
	
}