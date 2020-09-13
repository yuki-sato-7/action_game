/**
 * @file SeManager.h
 * @brief SE,BGM管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"

class Player;

class SeManager
{
public:

	/**
 　　* @brief SE.BGM管理クラスを初期化する
　　 * @return 常にtrue
　　 */
	virtual bool Initialize();

	/**
　　 * @brief ヒット音を再生する
 　　*/
	void HitSe();

	/**
　　 * @brief メインBGMを再生する
 　　*/
	void MainBgmPlay();

	/**
　　 * @brief メインBGMを停止する
 　　*/
	void MainBgmStop();

	/**
 　　* @brief ゲームオーバーBGMを再生する
 　　*/
	void GameOverBgmPlay();

	/**
 　　* @brief ゲームオーバーBGMを停止する
 　　*/
	void GameOverBgmStop();

	/**
 　　* @brief パンチ音を再生する
 　　*/
	void PunchSePlay();

	/**
 　　* @brief 敵の爆発音を再生する
 　　*/
	void ExplosionSePlay();

	/**
 　　* @brief OPBGMを再生する
 　　*/
	void OpBgmPlay();

	/**
　　 * @brief OPBGMを停止する
　　 */
	void OpBgmStop();

	/**
     * @brief ゲームクリアBGMを再生する
     */
	void GcBgmPlay();

	/**
     * @brief ゲームクリアBGMを停止する
     */
	void GcBgmStop();

	/**
     * @brief 決定音を再生する
     */
	void SelectSePlay();

	static SeManager& GetInstance()
	{
		static SeManager se_manager;
		return se_manager;
	}

private:

	//!攻撃ヒット時
	SOUND hit_se_;

	//!メインBGM
	MUSIC main_bgm_;

	//!ゲームオーバーBGM
	MUSIC game_over_bgm_;

	//!パンチSE
	SOUND punch_se_;

	//!爆発SE
	SOUND explosion_se_;

	//!決定音SE
	SOUND select_se_;

	//!OPBGM
	MUSIC op_bgm_;

	//!クリアBGM
	MUSIC game_clear_bgm_;

	//!BGM,SEを読み込んだか確認
	bool load_sound_;


	SeManager() {} 

	SeManager(const SeManager&);
	SeManager& operator=(const SeManager&);
};

inline SeManager& se_manager() { return SeManager::GetInstance(); }


