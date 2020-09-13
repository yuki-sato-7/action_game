/**
 * @file TitleScene.h
 * @brief タイトルシーン管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */

#pragma once

#include "BaseScene.h"
#include "MyLight.h"
#include "SeManager.h"
#include "SceneManager.h"
#include "Enum.h"

class TitleScene :public BaseScene {
public:
	virtual ~TitleScene();

	void Initialize();
	void Update();
	void Draw3D();
	void Draw2D();

	/**
	 * @brief　文字を点滅させる処理
	 */
	void FlashInterval();

private:
	// 定数
	const float kAdjustTittleTime   = 50.0f;    //操作画面に移行する時間調整
	const float kAdjustTittleState  = 1.0f;     //操作画面に移行する状態
	const float kAdjustAlphaChange  = 0.01f;    //文字の透明度の変化量調整
	const float kAdjustAlphaMax     = 1.0f;     //文字の透明度（最大）
	
	//!タイトル画面
	SPRITE tittle_;

	//!スタートボタン
	SPRITE press_start_;

	//!操作説明書画面
	SPRITE operation_explanation_;

	//!操作説明書画面（ボタン）
	SPRITE operation_button;

	//!ゲームパットの状態取得
	GamePadBuffer   pad_buffer_;
	GamePadState    pad_state_;
	
	//!タイトル画面の遷移
	int tittle_state_;

	//!画面遷移に必要時間
	int tittle_count_;

	//!次の画面に遷移するための状態管理
	bool next_flag_;

	//!セレクト音の状態管理
	bool select_se_flag_;

	//!文字の透明度
	float alpha_clear_;

	//!文字の透明度
	float alpha_state_;

};
