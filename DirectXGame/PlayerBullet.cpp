#include "PlayerBullet.h"
#include "assert.h"
#include "base/TextureManager.h"

void PlayerBullet::Initialize(KamataEngine::Model* model, const KamataEngine::Vector3 position, const KamataEngine::Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = KamataEngine::TextureManager::Load("Black.png");
	objectColor_.Initialize();

	worldTranform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTranform_.translation_ = position;
	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	// 座標を移動させる
	worldTranform_.translation_.x += velocity_.x;
	worldTranform_.translation_.y += velocity_.y;
	worldTranform_.translation_.z += velocity_.z;

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTranform_.UpdateMatrix(); 
}

void PlayerBullet::Draw(const KamataEngine::Camera& camera) {
	// モデルの描画
	model_->Draw(worldTranform_, camera, textureHandle_, &objectColor_);
}