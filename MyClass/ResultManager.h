/**
 * @file Result_Manager.h
 * @brief ���U���g��ʊǗ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "SeManager.h"
#include "Enum.h"
#include "TimeManager.h"
#include "UiManager.h"
#include "EnemyManager.h"
#include "Observer.h"

class ResultManager : public IObserver
{
public:

	/**
 �@�@* @brief ���U���g�Ǘ��N���X������������
�@�@ * @return ���true
�@�@ */
	virtual bool Initialize(EnemyManager& enemy_manager);

	/**
 �@�@* @brief ���U���g�Ǘ��N���X��`�悷��
 �@�@*/
	virtual void Update();

	/**
 �@�@* @brief ���U���g�Ǘ��N���X��`�悷��
 �@�@*/
	virtual void Draw();

	//�Q�[���I�[�o�[��Ԃ��擾
	bool GetGameOverFlag() { return game_over_flag_; };

	//�^�C���[�I�[�o�[���擾
	bool GetTimeOverFlag() { return time_over_flag_; };

	//�Q�[���N���A��Ԃ��擾
	bool GetGameClearFlag() { return game_clear_flag_; };

	//�Q�[���I�[�o�[��Ԃɂ���
	void  ResultManager::SetGameOverFlag() {
		game_over_flag_ = true;
	};

	//�Q�[���N���A��Ԃɂ���
	void  ResultManager::SetGameClearFlag() {
		game_clear_flag_ = true;
	};

	//�^�C���I�[�o�[��Ԃɂ���
	void  ResultManager::SetTimeOverFlag() {
		time_over_flag_ = true;
	};

	/**
	 * @brief �I�u�U�[�o�[����ʒm�ŏ�Ԃ�؂�ւ���
	 * @param[in] (notify) �I�u�U�[�o�[����̒ʒm���e
	 */
	void ReceiveNotify(int notify) {
		switch (notify) {
		case TIME_OVER_STATE:
			SetTimeOverFlag();
			break;

		case GAME_OVER_STATE:
			SetGameOverFlag();
			break;

		case GAME_CLEAR_STATE:
			SetGameClearFlag();
			break;
		}
	}

	// �V���O���g���C���X�^���X�̎擾
	static ResultManager& GetInstance()
	{
		static ResultManager result_manager;
		return result_manager;
	}

private:
	//�萔
	const float kAdjustAlphaChange_ = 0.02f;    //�����̓����x��
	const float kAdjustAlphaMax     = 1.0f;     //�����̓����x�i�ő�j

	//!�Q�[���I�[�o�[���
	SPRITE game_over_;

	//!�Q�[���N���A���
	SPRITE game_clear_;

	//!�^�C���I�[�o�[���
	SPRITE time_over_;

	//!�߂�{�^���\��
	SPRITE return_button_;

	//!�Q�[���I�[�o�[��Ԃ�
	bool game_over_flag_;

	//!�Q�[���N���A��Ԃ�
	bool game_clear_flag_;

	//!�^�C���I�[�o�[��Ԃ�
	bool time_over_flag_;

	//!�Q�[���N���ABGM��炵����
	bool game_clear_bgm_flag_;

	//!�^�C���I�[�o�[BGM��炵����
	bool game_over_bgm_flag_;

	//!�����̓����x
	float alpha_clear_;

	//!�����̓����x
	float alpha_state_;
	

	ResultManager() {} 

	ResultManager(const ResultManager&);
	ResultManager& operator=(const ResultManager&);
};

inline ResultManager& result_manager() { return ResultManager::GetInstance(); }