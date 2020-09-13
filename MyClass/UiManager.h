/**
 * @file UiManager.h
 * @brief UI�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "Enum.h"
#include "Observer.h"


class UiManager
{
public:

    /**
�@�@ * @brief UI�Ǘ��N���X������������
     * @return ���true
     */
    virtual bool Initialize();

    /**
     * @brief�@UI�Ǘ��N���X���A�b�v�f�[�g����
     */
    virtual void Update();

    /**
     * @brief UI�Ǘ��N���X��`�悷��
     */
    virtual void Draw();

    /**
�@�@ * @brief �v���C���[�̎󂯂��_���[�W���J�E���g����
�@�@ */
    void DamageHpCount();

	/**
     * @brief SP�Q�[�W���񕜂�����
     */
	void SpGaugeUp();

	/**
     * @brief �K�E�Z���g�p�������SP�Q�[�W��0�ɂ���
     */
	void SpGaugeDown();

	//HP��0�ɂȂ��������f
	bool GetDeathFlag() { return death_flag_; };

	//SP�Q�[�W�̎c�ʂ��擾����
	float GetSpGauge() { return sp_; };

	/**
�@�@ * @brief �I�u�U�[�o�[�ɐV���ȃI�u�U�[�o�[��ǉ�
	 * @param[in] (observer) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AddObserver(IObserver* observer)
	{
		game_over_subject_.addObserver(observer);
	}

	/**
�@�@ * @brief �I�u�U�[�o�[�̃��X�g����I�u�U�[�o�[���폜
	 * @param[in] (observer) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void RemoveObserver(IObserver* observer)
	{
		game_over_subject_.removeObserver(observer);
	}

	/**
�@�@ * @brief ���X�g�ɓo�^����Ă���I�u�U�[�o�[�̕ω���ʒm
	 * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
	void AllDelteObserver(IObserver* observer)
	{
		game_over_subject_.alldelteObservers();
	}

	// �V���O���g���C���X�^���X�̎擾
	static UiManager& GetInstance()
	{
		static UiManager Ui_manager;
		return Ui_manager;
	}

private:
	//�萔
	const float kAdjustGreenGaugeMax    = 294.0f;                         //�΃Q�[�W2��MAX�l
	const float kAdjustYellowGaugeMax2  = 220.8f;                         //���F�Q�[�W2��MAX�l
	const float kAdjustYellowGaugeMax1  = 147.2f;                         //���F�Q�[�W1��MAX�l
	const float kAdjustRedGaugeMax      = 73.6f;                          //���F�Q�[�W1��MAX�l
	const float kAdjustGaugeMoveSpeed   = 1.0f;                           //HP�Q�[���̌���X�s�[�h����
	const float kAdjustHpState          = -1.0f;                          //HP�Q�[���̏�Ԃ�J�ڂ�����
	
	const float kAdjustSpGaugeMax       = 319.0f;                         //SP�Q�[�W��MAX�l
	const float kAdjustSpGaugeMoveSpeed = 0.5f;                           //SP�Q�[�W�̉񕜗ʒ���

	const Vector3 kAdjustHpGaugeBarPos  = Vector3(12.0f, 10.0f, 0.0f);    //HP�Q�[�W(�g�j�̍��W����
	const Vector3 kAdjustHpGaugePos     = Vector3(95.0f, 15.0f, 0.0f);    //HP�Q�[�W�̍��W����
	const float   kAdjustHpGaugeRectB   = 23.0f;                          //HP�Q�[����RECT���W����
	const Vector3 kAdjustSpGaugeBarPos  = Vector3(12.0f, 50.0f, 0.0f);    //SP�Q�[�W(�g�j�̍��W����
	const Vector3 kAdjustSpGaugePos     = Vector3(95.0f, 57.0f, 0.0f);    //SP�Q�[�W�̍��W����
	const float   kAdjustSpGaugeRectB   = 19.0f;                          //SP�Q�[����RECT���W����

	//!HP�Q�[�W�i�g�j�̉摜
	SPRITE gauge_bar_;

	//!HP�Q�[�W�i���j�̉摜
	SPRITE yellow_gauge_;

	//!HP�Q�[�W�i�΁j�̉摜
	SPRITE green_gauge_;

	//!HP�Q�[�W�i�ԁj�̉摜
	SPRITE red_gauge_;

	//!SP�Q�[�W�i�g�j�̉摜
	SPRITE sp_bar_;

	//!SP�Q�[�W�i�j�̉摜
	SPRITE sp_gauge_;

	//!HP�Q�[�W�i���j�̍ő�l
	float yellow_x_;

	//!HP�Q�[�W�i�ԁj�̍ő�l
	float red_x_;

	//!HP�Q�[�W�i�΁j�̍ő�l
	float green_x_;

	//!HP�Q�[�W�̏��
	int hp_state_;

	//!HP��1�x�̂݌���������
	bool hp_count_flag_;

	//�Q�[���I�[�o�[�ɂȂ��������f
	bool death_flag_;

	//!SP�Q�[�W�̍ő�l
	float sp_;

	Subject game_over_subject_;


	UiManager() {} //�R���g���N�^�[

	UiManager(const UiManager&);
	UiManager& operator=(const UiManager&);
};

inline UiManager& ui_manager() { return UiManager::GetInstance(); }