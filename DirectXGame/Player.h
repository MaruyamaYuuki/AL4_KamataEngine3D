#pragma once

#include "3d/WorldTransform.h"
#include "3d/Model.h"
#include "3d/ObjectColor.h"
#include "input/Input.h"
#include "math/Vector3.h"
#include "PlayerBullet.h"
#include <list>

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

    /// <summary>
    /// 旋回
    /// </summary>
	void Rotate();

    /// <summary>
    /// 攻撃
    /// </summary>
	void Attack();

    /// <summary>
    /// デストラクタ 
    /// </summary>
	~Player();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// オブジェクトカラー
	KamataEngine::ObjectColor objectColor_;
	// キーボード入力
	KamataEngine::Input* input_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;
};