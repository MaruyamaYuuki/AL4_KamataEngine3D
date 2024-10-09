#define NOMINMAX
#include "Player.h"
#include <assert.h>
#include "2d/ImGuiManager.h"
#include <algorithm>
#include "DirectXTex.h"

Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	objectColor_.Initialize();
	input_ = KamataEngine::Input::GetInstance();
}

void Player::Update() {

	// キャラクター旋回処理
	Rotate();

	// キャラクター移動処理
	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharactorSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharactorSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharactorSpeed;
	}

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharactorSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharactorSpeed;
	}

	// 座標変更
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 移動限界座標
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 18.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = std::max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = std::min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = std::max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = std::min(worldTransform_.translation_.y, +kMoveLimitY);


#ifdef _DEBUG
	ImGui::Begin(" ");
	ImGui::DragFloat3("Player", &worldTransform_.translation_.x,1.0f);
	ImGui::End();
#endif

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();


}

void Player::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera, textureHandle_, &objectColor_);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Player::Rotate() {
	/// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {

		// 自キャラの座標をコピー
		KamataEngine::Vector3 position = worldTransform_.translation_;

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, position);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}