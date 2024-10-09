#pragma once
#include "3d/Camera.h"
#include "3d/WorldTransform.h"
#include "3d/ObjectColor.h"
#include "3d/Model.h"
#include "math/Vector3.h"

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <pram name="model">モデル</param>
	/// <pram name="potision">初期座標</pram>
	void Initialize(KamataEngine::Model* model, const KamataEngine::Vector3 position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// pram name="camera">ビュープロジェクション</pram>
	void Draw(const KamataEngine::Camera& camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTranform_;
	// モデルのポインタ
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// オブジェクトカラー
	KamataEngine::ObjectColor objectColor_;
};