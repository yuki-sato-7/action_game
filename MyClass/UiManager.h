/**
 * @file UiManager.h
 * @brief UI管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "Enum.h"
#include "Observer.h"


class UiManager
{
public:

    /**
　　 * @brief UI管理クラスを初期化する
     * @return 常にtrue
     */
    virtual bool Initialize();

    /**
     * @brief　UI管理クラスをアップデートする
     */
    virtual void Update();

    /**
     * @brief UI管理クラスを描画する
     */
    virtual void Draw();

    /**
　　 * @brief プレイヤーの受けたダメージをカウントする
　　 */
    void DamageHpCount();

	/**
     * @brief SPゲージを回復させる
     */
	void SpGaugeUp();

	/**
     * @brief 必殺技を使用した後にSPゲージを0にする
     */
	void SpGaugeDown();

	//HPが0になったか判断
	bool GetDeathFlag() { return death_flag_; };

	//SPゲージの残量を取得する
	float GetSpGauge() { return sp_; };

	/**
　　 * @brief オブザーバーに新たなオブザーバーを追加
	 * @param[in] (observer) オブザーバーの通知内容
 　　*/
	void AddObserver(IObserver* observer)
	{
		game_over_subject_.addObserver(observer);
	}

	/**
　　 * @brief オブザーバーのリストからオブザーバーを削除
	 * @param[in] (observer) オブザーバーの通知内容
 　　*/
	void RemoveObserver(IObserver* observer)
	{
		game_over_subject_.removeObserver(observer);
	}

	/**
　　 * @brief リストに登録されているオブザーバーの変化を通知
	 * @param[in] (notify) オブザーバーの通知内容
 　　*/
	void AllDelteObserver(IObserver* observer)
	{
		game_over_subject_.alldelteObservers();
	}

	// シングルトンインスタンスの取得
	static UiManager& GetInstance()
	{
		static UiManager Ui_manager;
		return Ui_manager;
	}

private:
	//定数
	const float kAdjustGreenGaugeMax    = 294.0f;                         //緑ゲージ2のMAX値
	const float kAdjustYellowGaugeMax2  = 220.8f;                         //黄色ゲージ2のMAX値
	const float kAdjustYellowGaugeMax1  = 147.2f;                         //黄色ゲージ1のMAX値
	const float kAdjustRedGaugeMax      = 73.6f;                          //黄色ゲージ1のMAX値
	const float kAdjustGaugeMoveSpeed   = 1.0f;                           //HPゲームの減るスピード調整
	const float kAdjustHpState          = -1.0f;                          //HPゲームの状態を遷移させる
	
	const float kAdjustSpGaugeMax       = 319.0f;                         //SPゲージのMAX値
	const float kAdjustSpGaugeMoveSpeed = 0.5f;                           //SPゲージの回復量調整

	const Vector3 kAdjustHpGaugeBarPos  = Vector3(12.0f, 10.0f, 0.0f);    //HPゲージ(枠）の座標調整
	const Vector3 kAdjustHpGaugePos     = Vector3(95.0f, 15.0f, 0.0f);    //HPゲージの座標調整
	const float   kAdjustHpGaugeRectB   = 23.0f;                          //HPゲームのRECT座標調整
	const Vector3 kAdjustSpGaugeBarPos  = Vector3(12.0f, 50.0f, 0.0f);    //SPゲージ(枠）の座標調整
	const Vector3 kAdjustSpGaugePos     = Vector3(95.0f, 57.0f, 0.0f);    //SPゲージの座標調整
	const float   kAdjustSpGaugeRectB   = 19.0f;                          //SPゲームのRECT座標調整

	//!HPゲージ（枠）の画像
	SPRITE gauge_bar_;

	//!HPゲージ（黄）の画像
	SPRITE yellow_gauge_;

	//!HPゲージ（緑）の画像
	SPRITE green_gauge_;

	//!HPゲージ（赤）の画像
	SPRITE red_gauge_;

	//!SPゲージ（枠）の画像
	SPRITE sp_bar_;

	//!SPゲージ（青）の画像
	SPRITE sp_gauge_;

	//!HPゲージ（黄）の最大値
	float yellow_x_;

	//!HPゲージ（赤）の最大値
	float red_x_;

	//!HPゲージ（緑）の最大値
	float green_x_;

	//!HPゲージの状態
	int hp_state_;

	//!HPを1度のみ減少させる
	bool hp_count_flag_;

	//ゲームオーバーになったか判断
	bool death_flag_;

	//!SPゲージの最大値
	float sp_;

	Subject game_over_subject_;


	UiManager() {} //コントラクター

	UiManager(const UiManager&);
	UiManager& operator=(const UiManager&);
};

inline UiManager& ui_manager() { return UiManager::GetInstance(); }