/**
 * @file MyLight.cpp
 * @brief ���C�g�Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "MyLight.h"

/**
 * @brief�@���C�g�Ǘ��N���X������������
 * @return ���true
 */
bool MyLight::Initialize()
{
	//�X�e�[�W�S�̂��Ƃ炷���C�g
	Light light;
	light.Type      = Light_Directional;
	light.Direction = Vector3_Down;
	light.Diffuse   = Color(1.0f, 1.0f, 1.0f);
	light.Ambient   = Color(1.0f, 1.0f, 1.0f);

	//�X�e�[�W�����Ƃ炷���C�g
	Light light2;
	light2.Type      = Light_Directional;
	light2.Direction = Vector3_Up;
	light2.Diffuse   = Color(1.0f, 1.0f, 1.0f);
	light2.Specular  = Color(0.5f, 0.5f, 0.5f);
	light2.Ambient   = Color(1.0f, 1.0f, 1.0f);

	GraphicsDevice.SetLight(light,0);
	GraphicsDevice.SetLight(light2,1);
	GraphicsDevice.EnableLight(0, TRUE);
	GraphicsDevice.EnableLight(1, TRUE);

	return true;
}

