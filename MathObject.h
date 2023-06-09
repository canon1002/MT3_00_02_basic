#pragma once
#include "Vector3Funk.h"
#include "Matrix4x4Funk.h"
#include <Novice.h>

/// <summary>
/// 直線
/// </summary>
struct Line
{
	Vector3 origin;
	Vector3 diff;
};

/// <summary>
/// 半直線
/// </summary>
struct Ray
{
	Vector3 origin;
	Vector3 diff;
};

/// <summary>
/// 線分
/// </summary>
struct Segment
{
	Vector3 origin;
	Vector3 diff;
};

void DrawGrid(const Matrix4x4& viewProjection,const Matrix4x4& viewport) 
{
	const float kGridHalfWidth= 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上の情報を使ってワールド座標系上の始点と終点を求める
		// スクリーン座標系まで返還をかける
		// 変換した座標を使って表示。色は薄い灰色(0xAAAAAAFF)原点は黒ぐらいが良い

	}


}