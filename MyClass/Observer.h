/**
 * @file Observer.h
 * @brief �I�u�U�[�o�[�N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/8/1
 */
#pragma once
#include <list>
#include "Observer.h"

// �I�u�U�[�o�C���^�[�t�F�[�X
class IObserver {
public:
    /**
�@�@ * @brief �T�u�W�F�N�g����̒ʒm���󂯎��
     * @param[in] (notify) �ʒm���e
 �@�@*/
    virtual void ReceiveNotify(int notify) = 0;
};

// �T�u�W�F�N�g�N���X
class Subject {
public:
    /**
�@�@ * @brief �I�u�U�[�o�[�ɐV���ȃI�u�U�[�o�[��ǉ�
     * @param[in] (observer) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
    void addObserver(IObserver* observer)
    {
        observers_.push_back(observer); 
    }

    /**
�@�@ * @brief �I�u�U�[�o�[�̃��X�g����I�u�U�[�o�[���폜
     * @param[in] (observer) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
    void removeObserver(IObserver* observer)
    {
        observers_.remove(observer);   //���X�g�������
    }

    /**
�@�@ * @brief ���X�g�ɓo�^����Ă���I�u�U�[�o�[�̕ω���ʒm
     * @param[in] (notify) �I�u�U�[�o�[�̒ʒm���e
 �@�@*/
    void notifyObservers(int notify)
    {
        for (auto& observer : observers_)
            observer->ReceiveNotify(notify);    //�Ăяo��
    }

    /**
�@�@ * @brief �ʒm��S�č폜
 �@�@*/
    void alldelteObservers()
    {
        observers_.clear();
    }

private:
    //! ���X�g�̏��
    std::list<IObserver*>   observers_;
};
