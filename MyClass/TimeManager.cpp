#include "TimeManager.h"

/**
 * @brief ���ԊǗ��N���X������������
 * @return ���true
 */
bool TimeManager::Initialize()
{
	//�e�ϐ��̏�����
	start_time_count_ = 3000.0f;
	time_limit_count_ = 7200;

	game_start_       = false;
	time_limit_over_  = false;

	return true;
}

/**
 * @brief �X�V�i�������Ԃ̌v�Z�j
 */
void TimeManager::Update()
{
	//�������Ԃ̌v�Z
	time_limit_count_ -= kAdjustTimeLimitMove;
	
	if (time_limit_count_ <= 0) {
		time_limit_over_ = true;
		result_manager().SetTimeOverFlag();
	}
}

/**
 * @brief �Q�[���J�n�J�E���g�_�E�����v�Z����
 */
void TimeManager::GameStartCount()
{
	if (start_time_count_ >= -kAdjustCountTimeMin) {
		start_time_count_ -= GameTimer.GetElapsedMilliSecond();

		if (start_time_count_ < 0) {
			game_start_ = true;
		}
	}
}

/**
 * @brief �������Ԃ��v�Z����
*/
void TimeManager::TimeLimitCount()
{
	if (result_manager().GetGameClearFlag() == false && result_manager().GetGameOverFlag() == false && result_manager().GetTimeOverFlag() == false) {
		//�������Ԃ̌v�Z
		time_limit_count_ -= kAdjustTimeLimitMove;

		if (time_limit_count_ <= 0) {
			time_over_subject_.notifyObservers(TIME_OVER_STATE);  //�^�C���I�[�o�[�ɂȂ������Ƃ��I�u�U�[�o�[�ɒʒm
		}
	}
}