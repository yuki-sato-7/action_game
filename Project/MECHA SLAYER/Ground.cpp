/**
 * @file Ground.cpp
 * @brief 背景ステージクラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include "Ground.h"

/**
 * @brief　背景ステージクラスを初期化する
 * @return 常にtrue
 */
bool Ground::Initialize()
{
	//マテリアルの設定
	Material mtrl;
	mtrl.Diffuse = Color(1.0f, 1.0f, 1.0f);
	mtrl.Ambient = Color(0.25f, 0.25f, 0.25f);
	
	//床モデルの読み込み
	ground_ = GraphicsDevice.CreateModelFromFile(_T("Ground/ground/Coliseum_model_2.X"));
	ground_->SetScale(1.3f);
	ground_->SetPosition(0, 0, 0);
	ground_->SetMaterial(mtrl);

	//壁ズリ判定用のモデルの読み込み
	ground_wall_ = GraphicsDevice.CreateModelFromFile(_T("Ground/collision_wall/wall.X"));
	ground_wall_->SetScale(1.0f);
	ground_wall_->SetPosition(0, 0, 0);

	////壁モデルの読み込み
	ground_wall2_ = GraphicsDevice.CreateModelFromFile(_T("Ground/wall/Coliseum_model.X"));
	ground_wall2_->SetScale(1.0f);
	ground_wall2_->SetPosition(0, 0, 0); 
	ground_wall2_->SetMaterial(mtrl);

	return true;
}