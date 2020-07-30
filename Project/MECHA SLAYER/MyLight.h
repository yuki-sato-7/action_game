/**
 * @file MyLight.h
 * @brief ライト管理クラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"


class MyLight
{
public:

	/**
     * @brief ライト管理クラスを初期化する
     * @return 常にtrue
     */
	virtual bool Initialize();
};

