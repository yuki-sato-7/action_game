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
	yellow_gauge   = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/yellow.png"));
	green_gauge    = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/green.png"));
	red_gauge      = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/red.png"));
	gauge_bar_     = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/black.png"));
	sp_bar         = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/SP_1.png"));
	sp_gauge       = GraphicsDevice.CreateSpriteFromFile(_T("Ui/Hp/SP_2.png"));

	//�e�ϐ��̏�����
	hp_state = GREEN_2;
	red_x    = 73.6f;
	yellow_x = 220.8f;
	green_x  = 368.0f;
	sp_      = 319.0f;

	hp_count_flag = false;
	death_flag    = false;

	return true;
}

/**
 * @brief �X�V�iHP�o�[�̐ؑցj
 */
void UiManager::Update()
{
	if (hp_state == GREEN_1) {
		if (green_x > kAdjustGreenGaugeMax) {
			green_x -= kAdjustGaugeMoveSpeed;
		}
		else {
			hp_count_flag = false;
		}

	}

	if (hp_state == YELLOW_2) {
		if (green_x > kAdjustYellowGaugeMax2) {
			green_x -= kAdjustGaugeMoveSpeed;
		}

		else {
			hp_count_flag = false;
		}
	}

	if (hp_state == YELLOW_1) {
		if (yellow_x > kAdjustYellowGaugeMax1) {
			yellow_x -= kAdjustGaugeMoveSpeed;
		}
		else {
			hp_count_flag = false;
		}

	}

	if (hp_state == RED_2) {
		if (yellow_x > kAdjustRedGaugeMax) {
			yellow_x -= kAdjustGaugeMoveSpeed;
		}

		else {
			hp_count_flag = false;
		}
	}

	if (hp_state == RED_1) {
		if (red_x > 0) {
			red_x -= kAdjustGaugeMoveSpeed;
		}

		else {
			death_flag = true;
		}
	}
}

/**
 * @brief �v���C���[�̎󂯂��_���[�W���J�E���g����
 */
void UiManager::DamageHpCount()
{	
	if (hp_count_flag == false) {
		hp_state -= 1;
		hp_count_flag = true;
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

	SpriteBatch.Draw(*red_gauge, kAdjustHpGaugePos, Rect(0, 0, red_x, kAdjustHpGaugeRectB));

	if (yellow_x > kAdjustRedGaugeMax) {
		SpriteBatch.Draw(*yellow_gauge, kAdjustHpGaugePos, Rect(0, 0, yellow_x, kAdjustHpGaugeRectB));
	}

	if (green_x > kAdjustYellowGaugeMax2) {
		SpriteBatch.Draw(*green_gauge, kAdjustHpGaugePos, Rect(0, 0, green_x, kAdjustHpGaugeRectB));
	}

	SpriteBatch.Draw(*sp_bar, kAdjustSpGaugeBarPos);

	SpriteBatch.Draw(*sp_gauge, kAdjustSpGaugePos, Rect(0, 0, sp_, kAdjustSpGaugeRectB));

}