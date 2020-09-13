/**
 * @file SeManager.h
 * @brief SE,BGM�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"

class Player;

class SeManager
{
public:

	/**
 �@�@* @brief SE.BGM�Ǘ��N���X������������
�@�@ * @return ���true
�@�@ */
	virtual bool Initialize();

	/**
�@�@ * @brief �q�b�g�����Đ�����
 �@�@*/
	void HitSe();

	/**
�@�@ * @brief ���C��BGM���Đ�����
 �@�@*/
	void MainBgmPlay();

	/**
�@�@ * @brief ���C��BGM���~����
 �@�@*/
	void MainBgmStop();

	/**
 �@�@* @brief �Q�[���I�[�o�[BGM���Đ�����
 �@�@*/
	void GameOverBgmPlay();

	/**
 �@�@* @brief �Q�[���I�[�o�[BGM���~����
 �@�@*/
	void GameOverBgmStop();

	/**
 �@�@* @brief �p���`�����Đ�����
 �@�@*/
	void PunchSePlay();

	/**
 �@�@* @brief �G�̔��������Đ�����
 �@�@*/
	void ExplosionSePlay();

	/**
 �@�@* @brief OPBGM���Đ�����
 �@�@*/
	void OpBgmPlay();

	/**
�@�@ * @brief OPBGM���~����
�@�@ */
	void OpBgmStop();

	/**
     * @brief �Q�[���N���ABGM���Đ�����
     */
	void GcBgmPlay();

	/**
     * @brief �Q�[���N���ABGM���~����
     */
	void GcBgmStop();

	/**
     * @brief ���艹���Đ�����
     */
	void SelectSePlay();

	static SeManager& GetInstance()
	{
		static SeManager se_manager;
		return se_manager;
	}

private:

	//!�U���q�b�g��
	SOUND hit_se_;

	//!���C��BGM
	MUSIC main_bgm_;

	//!�Q�[���I�[�o�[BGM
	MUSIC game_over_bgm_;

	//!�p���`SE
	SOUND punch_se_;

	//!����SE
	SOUND explosion_se_;

	//!���艹SE
	SOUND select_se_;

	//!OPBGM
	MUSIC op_bgm_;

	//!�N���ABGM
	MUSIC game_clear_bgm_;

	//!BGM,SE��ǂݍ��񂾂��m�F
	bool load_sound_;


	SeManager() {} 

	SeManager(const SeManager&);
	SeManager& operator=(const SeManager&);
};

inline SeManager& se_manager() { return SeManager::GetInstance(); }


