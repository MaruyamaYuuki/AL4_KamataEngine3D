#pragma once

#include "3d/WorldTransform.h"
#include "3d/Model.h"
#include "3d/ObjectColor.h"

/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	///初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model,uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// オブジェクトカラー
	KamataEngine::ObjectColor objectColor_;
};