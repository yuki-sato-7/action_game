/**
 * @file Observer.h
 * @brief オブザーバークラスヘッダーファイル
 * @author 佐藤雄希
 * @date 2020/8/1
 */
#pragma once
#include <list>
#include "Observer.h"

// オブザーバインターフェース
class IObserver {
public:
    /**
　　 * @brief サブジェクトからの通知を受け取る
     * @param[in] (notify) 通知内容
 　　*/
    virtual void ReceiveNotify(int notify) = 0;
};

// サブジェクトクラス
class Subject {
public:
    /**
　　 * @brief オブザーバーに新たなオブザーバーを追加
     * @param[in] (observer) オブザーバーの通知内容
 　　*/
    void addObserver(IObserver* observer)
    {
        observers_.push_back(observer); 
    }

    /**
　　 * @brief オブザーバーのリストからオブザーバーを削除
     * @param[in] (observer) オブザーバーの通知内容
 　　*/
    void removeObserver(IObserver* observer)
    {
        observers_.remove(observer);   //リストから消す
    }

    /**
　　 * @brief リストに登録されているオブザーバーの変化を通知
     * @param[in] (notify) オブザーバーの通知内容
 　　*/
    void notifyObservers(int notify)
    {
        for (auto& observer : observers_)
            observer->ReceiveNotify(notify);    //呼び出す
    }

    /**
　　 * @brief 通知を全て削除
 　　*/
    void alldelteObservers()
    {
        observers_.clear();
    }

private:
    //! リストの情報
    std::list<IObserver*>   observers_;
};
