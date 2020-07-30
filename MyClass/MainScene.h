/**
 * @file MainScene.h
 * @brief メインシーン管理クラスヘッダーファイル
 * @author 佐藤雄希
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
	
	//クラスの前方参照
	Player player;
	Ground ground;
	EnemyManager enemy;
	MyLight my_light;
	CameraMain camera_main;
	CollisionEnemy collision_enemy;
	Camera camera_;

	//!制限時間用フォントの読み込み
	FONT time_limit_font_;

	//!ゲームスタートカウント用フォントの読み込み
	FONT game_start_count_font_;

	//!ゲームパットの状態取得
	GamePadBuffer   pad_buffer_;
	GamePadState   pad_state_;

	//!制限時間
	int timer__;
};

