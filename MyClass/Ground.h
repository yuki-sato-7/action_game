/**
 * @file Ground.h
 * @brief 背景ステージクラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"

class Ground
{
public:

	/**
     * @brief 背景ステージクラスを初期化する
     * @return 常にtrue
     */
	virtual bool Initialize();

	//!床モデルの取得
	MODEL GetModel() { return ground_; }

	//!壁ズリ判定用のモデルの取得
	MODEL GetModelWall() { return ground_wall_; }

	//!壁モデルの取得
	MODEL GetModelWall2() { return ground_wall2_; }

private:

	//!床のモデル
	MODEL ground_;

	//!壁ズリ判定用の壁モデル
	MODEL ground_wall_;

	//!壁のモデル
	MODEL ground_wall2_;
};


