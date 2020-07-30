/**
 * @file SceneManager.cpp
 * @brief ゲームシーン管理クラスソースファイル
 * @author 佐藤雄希
 * @date 2020/7/21
 */
#include"SceneManager.h"
BaseScene* SceneManager::m_pScene = nullptr;  //シーンを空にする

void SceneManager::ChangeScene(SCENE scene) {

	if (m_pScene != nullptr) {
		delete m_pScene;
	}
	switch (scene) {
	case SCENE::TITLE:
		m_pScene = new TitleScene();
		break;
	case SCENE::MAIN:
		m_pScene = new MainScene();
		break;
	}
	m_pScene->Initialize();
}

void SceneManager::Update() {
	m_pScene->Update();     
}

void SceneManager::Draw3D() {
	m_pScene->Draw3D();  
}


void SceneManager::Draw2D() {
	m_pScene->Draw2D();
}