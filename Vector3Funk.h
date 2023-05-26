#pragma once
#include<Vector3.h>
#include<Novice.h>

class Vector3Funk
{
public: //メンバ関数(メソッド)

	static Vector3 Cross(const Vector3& v1, const Vector3& v2) {
		
		return Vector3{
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x),
		};
	
	};

	static float Dot(const Vector3& v1, const Vector3& v2) {

		return float{
			v1.x * v2.x + v1.y * v2.y + v1.z * v2.z
		};

	};

	static void VectorScreenPrintf(int posX, int posY, const Vector3& v1,const char* ravel) {

		Novice::ScreenPrintf(posX, posY, "%s : %.2f,%.2f,%.2f,", ravel, v1.x, v1.y, v1.z);

	}

};

