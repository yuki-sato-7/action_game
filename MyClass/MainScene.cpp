/**
 * @file MainScene.cpp
 * @brief ���C���V�[���Ǘ��N���X�\�[�X�t�@�C��
 * @author �����Y��
 * @date 2020/7/21
 */
#include "MainScene.h"

MainScene::~MainScene()
{
	//�t�H���g�f�[�^�̍폜
	RemoveFontResource(_T("Text/CAMELIAB.TTF"));

	MediaManager.ReleaseAllMedia();

	GraphicsDevice.ReleaseAllRenderTargets();
	GraphicsDevice.ReleaseAllStateBlocks();
	GraphicsDevice.ReleaseAllFonts();
	GraphicsDevice.ReleaseAllSprites();
	GraphicsDevice.ReleaseAllAnimationModels();
	GraphicsDevice.ReleaseAllModels();
	GraphicsDevice.ReleaseAllVertexBuffers();
	GraphicsDevice.ReleaseAllEffects();

}

void MainScene::Initialize() {

	//�t�@�C������t�H���g��ǂݍ���
	AddFontResource(_T("CAMELIAB.TTF"));
	time_limit_font_       = GraphicsDevice.CreateSpriteFont(_T("Cameliabold"), 60);
	game_start_count_font_ = GraphicsDevice.CreateSpriteFont(_T("Cameliabold"), 100);

	//�v���C���[�N���X�̏�����
	player.Initialize(enemy);
	
	//�w�i�N���X�̏�����
	ground.Initialize();

	//�J�����N���X�̏�����
	camera_main.Initialize(player);

	//�G�t�F�N�g�N���X�̏�����
	effectmanager().Initialize(camera_main, player);

	//UI�N���X�̏�����
	ui_manager().Initialize();

	//���ԊǗ��N���X�̏�����
	time_manager().Initialize();

	//�G�̐���
	enemy.CreateEnemy(player, Vector3(   0, 0, 1235));
	enemy.CreateEnemy(player, Vector3(   0, 0, -1235));
	enemy.CreateEnemy(player, Vector3( 839, 0, 45));
	enemy.CreateEnemy(player, Vector3( 844, 0, 850));
	enemy.CreateEnemy(player, Vector3(-950, 0, -756));
	enemy.CreateEnemy(player, Vector3(-925, 0, 788));
	enemy.CreateEnemy(player, Vector3( 755, 0, -942));
	enemy.CreateEnemy(player, Vector3( 370, 0, 400));
	enemy.CreateEnemy(player, Vector3(-370, 0, -300));
	enemy.CreateEnemy(player, Vector3( 370, 0, -400));
	enemy.CreateEnemy(player, Vector3(-370, 0, 300));

	//���C�g�N���X�̏�����
	my_light.Initialize();

	//���U���g��ʃN���X�̏�����
	result_manager().Initialize(enemy);

	//���C��BGM�̍Đ�
	se_manager().MainBgmPlay();

	//�Q�[���p�b�g���g�p�\�ɂ���
	InputDevice.CreateGamePad(1);

}

void MainScene::Update() {

	//�Q�[���p�b�g�̉������u�ԁA�����Ă����Ԏ擾
	pad_state_ = GamePad(0)->GetState();
	pad_buffer_ = GamePad(0)->GetBuffer();

	time_manager().GameStartCount();

	//�J�����N���X�̃A�b�v�f�[�g
	camera_main.Update(player, pad_buffer_, pad_state_);

	if (time_manager().GetGameStart() == true) {

		//�A�b�v�f�[�g�O�̃v���C���[���W�擾
		Vector3 old_pos = player.GetPlayerPos();

		//�v���C���[�N���X�̃A�b�v�f�[�g
		player.Update(ground, camera_main, enemy, pad_buffer_, pad_state_);

		//�Փ˔���N���X�̃A�b�v�f�[�g
		collision_enemy.Update(enemy, player);

		//�A�b�v�f�[�g��̃v���C���[���W�擾
		Vector3 new_pos = player.GetPlayerPos();

		//�G�N���X�̃A�b�v�f�[�g
		enemy.Update(player, ground);

		//�J�����̍��W�̎擾
		camera_main.GetCameraPos() += new_pos - old_pos;

		//UI�N���X�̃A�b�v�f�[�g
		ui_manager().Update();

		//�G�t�F�N�g�N���X�̃A�b�v�f�[�g
		effectmanager().Update(camera_main);

		//�������Ԃ̃J�E���g�X�^�[�g
		time_manager().TimeLimitCount();

		//���U���g��ʊǗ��N���X�̃A�b�v�f�[�g
		result_manager().Update();

		//���U���g��ʂɑJ��
		if (result_manager().GetGameClearFlag() == true ||
			result_manager().GetGameOverFlag() == true ||
			result_manager().GetTimeOverFlag() == true) {
			if (pad_buffer_.IsPressed(GamePad_Button8)) {
				se_manager().GcBgmStop();
				se_manager().GameOverBgmStop();
				SceneManager::ChangeScene(SceneManager::TITLE);
			}
		}
	}
}

void MainScene::Draw3D() {
	
	//���̃��f���`��
	ground.GetModel()->Draw();

	//�w�i�p���f���`��
	ground.GetModelWall()->Draw();

	//�G���f���̕`��
	enemy.Draw();

	//�v���C���[�N���X�̕`��
	player.Draw();

	//�G�t�F�N�g�N���X�̕`��
	effectmanager().Draw(camera_main);			
}

void MainScene::Draw2D() {

	//�J�E���g�_�E���^�C�}�[�̕`��
	if (time_manager().GetStartTimeCount() > 0) {
		SpriteBatch.DrawString(game_start_count_font_, Vector2(600.0f, 200.0f), Color(255, 255, 255),
			_T("%d"), time_manager().GetStartTimeCount() / 1000 + 1);
	}

	else if (time_manager().GetStartTimeCount() < 0.0f && time_manager().GetStartTimeCount() > -1000.0f) {
		SpriteBatch.DrawString(game_start_count_font_, Vector2(280.0f, 200.0f), Color(255, 255, 255),
			_T("GAME START"));
	}

	//�������Ԃ̕`��
	if (time_manager().GetTimeLimitCount() > 660.0f) {
		SpriteBatch.DrawString(time_limit_font_, Vector2(600.0f, 20.0f), Color(255, 255, 255),
			_T("%d"), time_manager().GetTimeLimitCount() / 60);
	}
	else {
		SpriteBatch.DrawString(time_limit_font_, Vector2(600.0f, 20.0f), Color(255, 0, 0),
			_T("%d"), time_manager().GetTimeLimitCount() / 60);
	}

	//UI�N���X�̕`��
	ui_manager().Draw();

	//���U���g��ʂ̕`��
	result_manager().Draw();
}

