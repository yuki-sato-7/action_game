/**
 * @file HpGauge.cpp
 * @brief UI�Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "UiManager.h"

/**
 * @brief UI�Ǘ��N���X������������
 * @return ���true
 */
bool UiManager::Initialize()
{
	//�eUI�̓ǂݍ���
	yellow_gauge_   = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/yellow.png"));
	green_gauge_    = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/green.png"));
	red_gauge_      = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/red.png"));
	gauge_bar_     = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/black.png"));
	sp_bar_         = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/SP_1.png"));
	sp_gauge_       = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/SP_2.png"));

	//�e�ϐ��̏�����
	hp_state_ = GREEN_2;
	red_x_    = 73.6f;
	yellow_x_ = 220.8f;
	green_x_  = 368.0f;
	sp_      = 319.0f;

	hp_count_flag_ = false;
	death_flag_    = false;

	return true;
}

/**
 * @brief �X�V�iHP�o�[�̐ؑցj
 */
void UiManager::Update()
{
	if (hp_state_ == GREEN_1) {
		if (green_x_ > kAdjustGreenGaugeMax) {
			green_x_ -= kAdjustGaugeMoveSpeed;
		}
		else {
			hp_count_flag_ = false;
		}

	}

	if (hp_state_ == YELLOW_2) {
		if (green_x_ > kAdjustYellowGaugeMax2) {
			green_x_ -= kAdjustGaugeMoveSpeed;
		}

		else {
			hp_count_flag_ = false;
		}
	}

	if (hp_state_ == YELLOW_1) {
		if (yellow_x_ > kAdjustYellowGaugeMax1) {
			yellow_x_ -= kAdjustGaugeMoveSpeed;
		}
		else {
			hp_count_flag_ = false;
		}

	}

	if (hp_state_ == RED_2) {
		if (yellow_x_ > kAdjustRedGaugeMax) {
			yellow_x_ -= kAdjustGaugeMoveSpeed;
		}

		else {
			hp_count_flag_ = false;
		}
	}

	if (hp_state_ == RED_1) {
		if (red_x_ > 0) {
			red_x_ -= kAdjustGaugeMoveSpeed;
		}

		if(red_x_ <= 0){
			game_over_subject_.notifyObservers(GAME_OVER_STATE);      //�Q�[���I�[�o�[�ɂȂ������Ƃ��I�u�U�[�o�[�ɒʒm
		}
	}
}

/**
 * @brief �v���C���[�̎󂯂��_���[�W���J�E���g����
 */
void UiManager::DamageHpCount()
{	
	if (hp_count_flag_ == false) {
		hp_state_ -= 1;
		hp_count_flag_ = true;
	}
}

/**
 * @brief SP�Q�[�W���񕜂�����
 */
void UiManager::SpGaugeUp() {
	if (sp_ < kAdjustSpGaugeMax) {
		sp_ += kAdjustSpGaugeMoveSpeed;
	}
}

/**
 * @brief �K�E�Z���g�p�������SP�Q�[�W��0�ɂ���
 */
void UiManager::SpGaugeDown() {
	sp_ = 0.0f;
}

/**
 * @brief UI�Ǘ��N���X��`�悷��
 */
void UiManager::Draw()
{
	SpriteBatch.Draw(*gauge_bar_, kAdjustHpGaugeBarPos);

	SpriteBatch.Draw(*red_gauge_, kAdjustHpGaugePos, Rect(0, 0, red_x_, kAdjustHpGaugeRectB));

	if (yellow_x_ > kAdjustRedGaugeMax) {
		SpriteBatch.Draw(*yellow_gauge_, kAdjustHpGaugePos, Rect(0, 0, yellow_x_, kAdjustHpGaugeRectB));
	}

	if (green_x_ > kAdjustYellowGaugeMax2) {
		SpriteBatch.Draw(*green_gauge_, kAdjustHpGaugePos, Rect(0, 0, green_x_, kAdjustHpGaugeRectB));
	}

	SpriteBatch.Draw(*sp_bar_, kAdjustSpGaugeBarPos);

	SpriteBatch.Draw(*sp_gauge_, kAdjustSpGaugePos, Rect(0, 0, sp_, kAdjustSpGaugeRectB));

}