/**
 * @file SceneManager.h
 * @brief ゲームシーン管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "BaseScene.h"
#include"MainScene.h"
#include"TitleScene.h"


/*
*シーン管理クラス
*/
class SceneManager {
public:
	enum SCENE {
		TITLE,
		MAIN,
	};
	static void ChangeScene(SCENE scene);//シーンを引数によって変える関数
	static void Update();//現在のシーンの更新関数
	static void Draw3D();//現在のシーンの描画関数
	static void Draw2D();//現在のシーンの描画関数

	static BaseScene* m_pScene;           //現在のシーン
};

