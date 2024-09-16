#pragma once
#include "Vector3Funk.h"
#include "Matrix4x4Funk.h"
#include <Novice.h>

/// <summary>
/// 球
/// </summary>
struct Sphere {
	Vector3 center;
	float radius;
};

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