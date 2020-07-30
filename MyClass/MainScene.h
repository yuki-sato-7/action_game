/**
 * @file MainScene.h
 * @brief ���C���V�[���Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "BaseScene.h"
#include "SceneManager.h"
#include "MyLight.h"
#include "CameraMain.h"
#include "Player.h"
#include "Ground.h"
#include "EnemyManager.h"
#include "CollisionEnemy.h"
#include "Enemy.h"
#include "TimeManager.h"

class MainScene :public BaseScene {
public:
	virtual ~MainScene();

	void Initialize();
	void Update();
	void Draw3D();
	void Draw2D();

private:
	
	//�N���X�̑O���Q��
	Player player;
	Ground ground;
	EnemyManager enemy;
	MyLight my_light;
	CameraMain camera_main;
	CollisionEnemy collision_enemy;
	Camera camera_;

	//!�������ԗp�t�H���g�̓ǂݍ���
	FONT time_limit_font_;

	//!�Q�[���X�^�[�g�J�E���g�p�t�H���g�̓ǂݍ���
	FONT game_start_count_font_;

	//!�Q�[���p�b�g�̏�Ԏ擾
	GamePadBuffer   pad_buffer_;
	GamePadState   pad_state_;

	//!��������
	int timer__;
};

