#include "MyMath.h"

KamataEngine::Matrix4x4 MyMath::Multiply(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// 1. 平行移動行列
KamataEngine::Matrix4x4 MyMath::MakeTranslateMatrix(const KamataEngine::Vector3& translate) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			} else {
				result.m[i][j] = 0;
			}
		}
	}
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}
// 2. 拡大縮小行列
KamataEngine::Matrix4x4 MyMath::MakeScaleMatrix(const KamataEngine::Vector3& scale) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			} else {
				result.m[i][j] = 0;
			}
		}
	}
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	return result;
}
// 1. X軸回転行列
KamataEngine::Matrix4x4 MyMath::MakeRotateXMatrix(float radius) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			} else {
				result.m[i][j] = 0;
			}
		}
	}
	result.m[1][1] = float(std::cos(radius));
	result.m[1][2] = float(std::sin(radius));

	result.m[2][1] = float(-std::sin(radius));
	result.m[2][2] = float(std::cos(radius));
	return result;
}
// 2. Y軸回転行列
KamataEngine::Matrix4x4 MyMath::MakeRotateYMatrix(float radius) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			} else {
				result.m[i][j] = 0;
			}
		}
	}
	result.m[0][0] = float(std::cos(radius));
	result.m[0][2] = float(-std::sin(radius));

	result.m[2][0] = float(std::sin(radius));
	result.m[2][2] = float(std::cos(radius));
	return result;
}
// 3. Z軸回転行列
KamataEngine::Matrix4x4 MyMath::MakeRotateZMatrix(float radius) {
	KamataEngine::Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				result.m[i][j] = 1;
			} else {
				result.m[i][j] = 0;
			}
		}
	}
	result.m[0][0] = float(std::cos(radius));
	result.m[0][1] = float(std::sin(radius));

	result.m[1][0] = float(-std::sin(radius));
	result.m[1][1] = float(std::cos(radius));
	return result;
}

KamataEngine::Matrix4x4 MyMath::MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate) {
	KamataEngine::Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	KamataEngine::Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	KamataEngine::Matrix4x4 rotateMatrix = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

	KamataEngine::Matrix4x4 SRResult = Multiply(scaleMatrix, rotateMatrix);
	KamataEngine::Matrix4x4 SRTResult = Multiply(SRResult, translateMatrix);
	return SRTResult;
}

KamataEngine::Vector3 MyMath::Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix) {
	KamataEngine::Vector3 result;
	result.x = matrix.m[0][0] * vector.x + matrix.m[1][0] * vector.y + matrix.m[2][0] * vector.z + matrix.m[3][0];
	result.y = matrix.m[0][1] * vector.x + matrix.m[1][1] * vector.y + matrix.m[2][1] * vector.z + matrix.m[3][1];
	result.z = matrix.m[0][2] * vector.x + matrix.m[1][2] * vector.y + matrix.m[2][2] * vector.z + matrix.m[3][2];
	float w = matrix.m[0][3] * vector.x + matrix.m[1][3] * vector.y + matrix.m[2][3] * vector.z + matrix.m[3][3];
	if (w != 0.0f)
		result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}