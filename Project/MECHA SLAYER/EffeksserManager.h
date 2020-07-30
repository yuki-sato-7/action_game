/**
 * @file Effeksser_Manager.h
 * @brief �G�t�F�N�g�Ǘ��N���X�w�b�_�[�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#pragma once
#include "ESGLib.h"
#include "SeManager.h"

class Player;
class CameraMain;
class EnemyManager;
class Enemy;


class EffeksserManager
{
public:

	/**
	 * @brief �G�t�F�N�g�Ǘ��N���X������������
	 * @param[in] (camara_) �J�����N���X
	 * @param[in] (player_) �v���C���[�N���X
	 * @return ���true
	 */
	virtual bool Initialize(CameraMain& camara_, Player& player_);

	/**
	 * @brief �X�V�i�G�t�F�N�g���J�����ɓ��e����j
	 * @param[in] (camara_) �J�����N���X
	 */
	virtual void Update(CameraMain& camara_);

	/**
     * @brief �G�t�F�N�g��`�悷��
     * @param[in] (camara_) �J�����N���X
     */
	virtual void Draw(CameraMain& camara_);

	/**
     * @brief �U���G�t�F�N�g���Đ�����
     * @param[in] (player) �v���C���[�N���X
     */
	virtual void SlashEffectPlay(Player& player);

	/**
     * @brief �q�b�g�G�t�F�N�g���Đ�����
     * @param[in] (player) �v���C���[�N���X
	 * @param[in] (enemy_pos) �G�̍��W
     */
	virtual void HitEffectPlay(Player& player, Vector3& enemy_pos);

	/**
	 * @brief �_�b�V���U���G�t�F�N�g���Đ�����
	 * @param[in] (player) �v���C���[�Ǘ��N���X
	 */
	virtual void DashSlashEffectPlay(Player& player);

	/**
     * @brief �K�E�Z�G�t�F�N�g���Đ�����
     * @param[in] (player) �v���C���[�N���X
     */
	virtual void DeathBlowEffectPlay(Player& player);

	/**
     * @brief �K�E�Z�G�t�F�N�g���v���C���[�ɉ����Ĉړ�������
     * @param[in] (player) �v���C���[�N���X
     */
	virtual void DeathBlowEffectMove(Player& player);

	/**
	 *@brief �G�̔����G�t�F�N�g���Đ�����
	 * @param[in](enemy_pos) ���S�����G�̍��W
     */
	virtual void ExplosionPlay(Vector3 enemy_pos);

	/**
     * @brief �K�E�Z�G�t�F�N�g���~����
     */
	virtual void DeathBlowEffectStop();

	// �V���O���g���C���X�^���X�̎擾
	static EffeksserManager& GetInstance()
	{
		static EffeksserManager effect_manager;
		return effect_manager;
	}

private:
	// �萔
	const float kEffectAdjustAngle          = 45.0f;    //�G�t�F�N�g�̊p�x����
	const float kEffectAdjustPos            = 60.0f;    //�U���A�q�b�g�G�t�F�N�g�̍��W����
	const float kEffectAdjustDashSlashPos   = 30.0f;    //�_�b�V���U���̍��W����
	const float kEffectAdjustScale          = 8.0f;     //�U���A�q�b�g�G�t�F�N�g�̑傫������
	const float kEffectAdjustDeathBlowPos   = 30.0f;    //�K�E�Z�G�t�F�N�g�̍��W����
	const float kEffectAdjustDeathBlowScale = 6.0f;     //�K�E�Z�G�t�F�N�g�̑傫������
	const float kEffectAdjustDeathBlowMove  = 8.0f;     //�K�E�Z�G�t�F�N�g�̈ړ��ʒ���
	const float kEffectAdjustExplosioScale  = 20.0f;    //�����G�t�F�N�g�̑傫������



	//!�U���G�t�F�N�g
	EFFEKSEER slash_effect_;

	//!�_�b�V���U���G�t�F�N�g
	EFFEKSEER dash_slash_effect_;

	//!�����G�t�F�N�g
	EFFEKSEER explosion_effect_;

	//!�K�E�Z�G�t�F�N�g
	EFFEKSEER death_blow_;

	//!�q�b�g�G�t�F�N�g
	EFFEKSEER hit_effect_;

	//!�K�E�ZID
	int death_blow_effect_effect_id_;

	//!�G�t�F�N�g�̌���
	Vector3 effect_dir_;


	EffeksserManager() {} 

	EffeksserManager(const EffeksserManager&);
	EffeksserManager& operator=(const EffeksserManager&);
};

inline EffeksserManager& effectmanager() { return EffeksserManager::GetInstance(); }



