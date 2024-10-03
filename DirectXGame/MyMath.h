#include "math/Vector3.h"
#include "math/Matrix4x4.h"
#include <cmath>

class MyMath {
public:
	static KamataEngine::Matrix4x4 Multiply(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);
	static KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);
	static KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);
	static KamataEngine::Matrix4x4 MakeRotateXMatrix(float radius);
	static KamataEngine::Matrix4x4 MakeRotateYMatrix(float radius);
	static KamataEngine::Matrix4x4 MakeRotateZMatrix(float radius);
	static KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);
	static KamataEngine::Vector3 Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix);
};