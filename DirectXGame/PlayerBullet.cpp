#include "PlayerBullet.h"
#include "assert.h"
#include "base/TextureManager.h"

void PlayerBullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3 position) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = KamataEngine::TextureManager::Load("Black.png");
	objectColor_.Initialize();

	worldTranform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTranform_.translation_ = position;
}

void PlayerBullet::Update() { 
	worldTranform_.UpdateMatrix(); 
}

void PlayerBullet::Draw(const KamataEngine::Camera& camera) {
	// モデルの描画
	model_->Draw(worldTranform_, camera, textureHandle_, &objectColor_);
}