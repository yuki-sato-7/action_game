/**
 * @file TimeManager.h
 * @brief ���ԊǗ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "ResultManager.h"
#include "Observer.h"
#include "Enum.h"

class TimeManager
{
public:

	/**
 �@�@* @brief ���ԊǗ��N���X������������
�@�@ * @return ���true
�@�@ */
	virtual bool Initialize();

	/**
�@�@ * @brief �X�V�i�������Ԃ̌v�Z�j
 �@�@*/
	virtual void Update();

	/**
�@�@ * @brief �Q�[���J�n�J�E���g�_�E�����v�Z����
 �@�@*/
	void GameStartCount();

	/**
�@�@ * @brief �������Ԃ��v�Z����
 �@�@*/
	void TimeLimitCount();
	
	//�Q�[���X�^�[�g�̃J�E���g���擾����
	int GetStartTimeCount() { return start_time_count_; }; 

	//�������Ԃ��擾����
	int GetTimeLimitCount() { return time_limit_count_; };

	//�Q�[���X�^�[�g���擾����
	bool GetGameStart() { return game_start_; };

	//�Q�[���X�^�[�g���擾����
	bool GetTimeLimitOver() { return time_limit_over_; };

	/**
�@�@ * @brief �I�u�U�[�o�[�ɐV���ȃI�u�U�[�o�[��ǉ�
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AddObserver(IObserver* observer)
	{
		time_over_subject_.addObserver(observer);
	}

	/**
�@�@ * @brief �I�u�U�[�o�[�̃��X�g����I�u�U�[�o�[���폜
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void RemoveObserver(IObserver* observer)
	{
		time_over_subject_.removeObserver(observer);
	}

	/**
�@�@ * @brief ���X�g�ɓo�^����Ă���I�u�U�[�o�[�̕ω���ʒm
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AllDelteObserver(IObserver* observer)
	{
		time_over_subject_.alldelteObservers();
	}

	static TimeManager& GetInstance()
	{
		static TimeManager time_manager;
		return time_manager;
	}

private:
	// �萔
	const float kAdjustTimeLimitMove = 1.0f;     //�������Ԃ̕ω����鑬�x����
	const float kAdjustCountTimeMin  = 2000.0f;  //�J�E���g�_�E�����������Ԓ���

	//!�Q�[���X�^�[�g�̃J�E���g
	int start_time_count_;

	//!��������
	int time_limit_count_;

	//!�Q�[���X�^�[�g�����f
	bool game_start_;

	//!��������
	int time_limit_over_;

	Subject time_over_subject_;

	TimeManager() {} 

	TimeManager(const TimeManager&);
	TimeManager& operator=(const TimeManager&);
};

inline TimeManager& time_manager() { return TimeManager::GetInstance(); }


