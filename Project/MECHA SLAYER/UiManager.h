/**
 * @file UiManager.h
 * @brief UI�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "Enum.h"


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
	bool GetDeathFlag() { return death_flag; };

	//SP�Q�[�W�̎c�ʂ��擾����
	float GetSpGauge() { return sp_; };

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

	const Vector3 kAdjustHpGaugeBarPos  = Vector3(12.0f, 10.0f, 0.0f);    //HP�Q�[�W(���j�̍��W����
	const Vector3 kAdjustHpGaugePos     = Vector3(95.0f, 14.0f, 0.0f);    //HP�Q�[�W�̍��W����
	const float kAdjustHpGaugeRectB     = 23.0f;                          //HP�Q�[����RECT���W����
	const Vector3 kAdjustSpGaugeBarPos  = Vector3(12.0f, 50.0f, 0.0f);    //SP�Q�[�W(���j�̍��W����
	const Vector3 kAdjustSpGaugePos     = Vector3(95.0f, 57.0f, 0.0f);    //SP�Q�[�W�̍��W����
	const float kAdjustSpGaugeRectB     = 19.0f;                          //SP�Q�[����RECT���W����

	//!HP�Q�[�W�i�g�j�̉摜
	SPRITE gauge_bar_;

	//!HP�Q�[�W�i���j�̉摜
	SPRITE yellow_gauge;

	//!HP�Q�[�W�i�΁j�̉摜
	SPRITE green_gauge;

	//!HP�Q�[�W�i�ԁj�̉摜
	SPRITE red_gauge;

	//!SP�Q�[�W�i�g�j�̉摜
	SPRITE sp_bar;

	//!SP�Q�[�W�i�j�̉摜
	SPRITE sp_gauge;

	//!HP�Q�[�W�i���j�̍ő�l
	float yellow_x;

	//!HP�Q�[�W�i�ԁj�̍ő�l
	float red_x;

	//!HP�Q�[�W�i�΁j�̍ő�l
	float green_x;

	//!HP�Q�[�W�̏��
	int hp_state;

	//!HP��1�x�̂݌���������
	bool hp_count_flag;

	//�Q�[���I�[�o�[�ɂȂ��������f
	bool death_flag;

	//!SP�Q�[�W�̍ő�l
	float sp_;


	UiManager() {} //�R���g���N�^�[

	UiManager(const UiManager&);
	UiManager& operator=(const UiManager&);
};

inline UiManager& Ui_manager() { return UiManager::GetInstance(); }