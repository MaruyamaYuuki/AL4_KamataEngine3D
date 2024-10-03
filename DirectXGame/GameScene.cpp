#include "GameScene.h"
#include "base/TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete model_; 
	// 自キャラの解放
	delete player_;
	delete debugCamera_;
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
	// デバッグカメラの生成
	debugCamera_ = new KamataEngine::DebugCamera(720, 1280);
}

void GameScene::Update() {
	// 自キャラの更新
	player_->Update();
	// カメラの処理
	if (isDebugCameraActive_) {
    	//デバッグカメラの更新
    	debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}


	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_L)) {
		if (!isDebugCameraActive_)
			isDebugCameraActive_ = true;
		else
			isDebugCameraActive_ = false;
	}
	#endif
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