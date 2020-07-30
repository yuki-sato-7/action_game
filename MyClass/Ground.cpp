/**
 * @file Ground.cpp
 * @brief �w�i�X�e�[�W�N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "Ground.h"

/**
 * @brief�@�w�i�X�e�[�W�N���X������������
 * @return ���true
 */
bool Ground::Initialize()
{
	//�}�e���A���̐ݒ�
	Material mtrl;
	mtrl.Diffuse = Color(1.0f, 1.0f, 1.0f);
	mtrl.Ambient = Color(0.25f, 0.25f, 0.25f);
	
	//�����f���̓ǂݍ���
	ground_ = GraphicsDevice.CreateModelFromFile(_T("Ground/ground/Coliseum_model_2.X"));
	ground_->SetScale(1.3f);
	ground_->SetPosition(0, 0, 0);
	ground_->SetMaterial(mtrl);

	//�ǃY������p�̃��f���̓ǂݍ���
	ground_wall_ = GraphicsDevice.CreateModelFromFile(_T("Ground/collision_wall/wall.X"));
	ground_wall_->SetScale(1.0f);
	ground_wall_->SetPosition(0, 0, 0);

	////�ǃ��f���̓ǂݍ���
	ground_wall2_ = GraphicsDevice.CreateModelFromFile(_T("Ground/wall/Coliseum_model.X"));
	ground_wall2_->SetScale(1.0f);
	ground_wall2_->SetPosition(0, 0, 0); 
	ground_wall2_->SetMaterial(mtrl);

	return true;
}