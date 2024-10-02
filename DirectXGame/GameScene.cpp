#include "GameScene.h"
#include "base/TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	// 自キャラの解放
	delete player_;
}

void GameScene::Initialize() { 
	dxCommon_ = KamataEngine::DirectXCommon::GetInstance(); 
	input_ = KamataEngine::Input::GetInstance();
	audio_ = KamataEngine::Audio::GetInstance();

	textureHandle_ = KamataEngine::TextureManager::Load("test.png");
	// 3Dモデルの生成
	model_ = KamataEngine::Model::Create();
	// ビュープロジェクションの初期化
	camera_.Initialize();
	//自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの処理を追加できる
	/// </summary>
	
	// スプライト処理後描画
	KamataEngine::Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	//3Dオブジェクト描画前処理
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	//自キャラの描画
	player_->Draw(camera_);
	
	// 3Dオブジェクト描画後処理
	KamataEngine::Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	KamataEngine::Sprite::PreDraw(commandList);

	///<summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	// スプライト描画後処理
	KamataEngine::Sprite::PostDraw();

#pragma endregion
}