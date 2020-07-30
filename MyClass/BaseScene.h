/**
 * @file BaseScene.h
 * @brief ベースシー基底クラス管理クラスヘッダーファイル
 * @author 佐藤雄希
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

