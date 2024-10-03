#include "3d/WorldTransform.h"
#include "MyMath.h"

void KamataEngine::WorldTransform::UpdateMatrix() {
	matWorld_ = MyMath::MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファに転送する
	TransferMatrix();
}