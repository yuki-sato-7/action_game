/**
 * @file BaseScene.h
 * @brief �x�[�X�V�[���N���X�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
 
class BaseScene {
public:
	virtual ~BaseScene() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw3D() = 0;
	virtual void Draw2D() = 0;
};

