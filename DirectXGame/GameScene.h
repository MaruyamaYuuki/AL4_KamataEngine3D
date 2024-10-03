#pragma once

#include <KamataEngine.h>
#include "audio/Audio.h"
#include "base/DirectXCommon.h"
#include "input/Input.h"
#include "3d/Model.h"
#include "2d/Sprite.h"
#include "3d/Camera.h"
#include "3d/WorldTransform.h"
#include "3d/ObjectColor.h"
#include "Player.h"
#include "3d/DebugCamera.h"

/// <summary>
///ゲームシーン
/// </summary>
class GameScene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// ビュープロジェクション
	KamataEngine::Camera camera_;
	// 自キャラ
	Player* player_ = nullptr;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
};


