/**
 * @file Ground.h
 * @brief �w�i�X�e�[�W�N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"

class Ground
{
public:

	/**
     * @brief �w�i�X�e�[�W�N���X������������
     * @return ���true
     */
	virtual bool Initialize();

	//!�����f���̎擾
	MODEL GetModel() { return ground_; }

	//!�ǃY������p�̃��f���̎擾
	MODEL GetModelWall() { return ground_wall_; }

	//!�ǃ��f���̎擾
	MODEL GetModelWall2() { return ground_wall2_; }

private:

	//!���̃��f��
	MODEL ground_;

	//!�ǃY������p�̕ǃ��f��
	MODEL ground_wall_;

	//!�ǂ̃��f��
	MODEL ground_wall2_;
};


