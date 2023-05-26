#include <Novice.h>
#include "Matrix4x4Funk.h"
#include"Vector3Funk.h"
#include <stdint.h>

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const float kWindowSizeX = 1280.0f;
const float kWindowSizeY = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// 三角形の座標
	Vector3 kLocalVertices[3];
	kLocalVertices[0] = { 0.0f,2.0f,0.0f };
	kLocalVertices[1] = { 2.0f,0.0f,0.0f };
	kLocalVertices[2] = { -2.0f,0.0f,0.0f };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };
	Vector3 cross = Vector3Funk::Cross(v1, v2);

	// 行列・ベクトルの宣言
	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraPosition = { 0.0f,0.0f,-10.0f };

	Matrix4x4 worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	Matrix4x4 cameraMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
	Matrix4x4 viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.45f, kWindowSizeX / kWindowSizeY, 0.1f, 100.0f);
	Matrix4x4 viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
	Matrix4x4 viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, kWindowSizeX, kWindowSizeY, 0.0f, 1.0f);

	Vector3 screenVertices[3] = {};
	Vector3 cameraFace;

	//Matrix4x4 orthographicMatrix = Matrix4x4Funk::MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	//Matrix4x4 perspectiveFovMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.63f, 1.33f, 0.1f, 1000.0f);

	// 行列の計算
	Vector3 ndcVertex[3];

	Vector3 v3[3] = {};
	for (uint32_t i = 0; i < 3; i++) {
		ndcVertex[i] = Matrix4x4Funk::Transform(kLocalVertices[i], worldViewProjectionMatrix);
		screenVertices[i] = Matrix4x4Funk::Transform(ndcVertex[i], viewportMatrix);
	}


	// 表示用の変数
	const int kRowHeight = 30;
	const int kColumnWidth = 600;

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// キー入力
		if (keys[DIK_W]) {
			cameraPosition.z += 1.0f;
		}
		if (keys[DIK_S]) {
			cameraPosition.z -= 1.0f;
		}
		if (keys[DIK_A]) {
			cameraPosition.x -= 1.0f;
		}
		if (keys[DIK_D]) {
			cameraPosition.x += 1.0f;
		}


		if (keys[DIK_SPACE]) {
			rotate.y = 0.0f;
		}

		// Y軸回転を行う
		rotate.y += 0.04f;

		// 行列の更新
		worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		cameraMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
		projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.45f, kWindowSizeX / kWindowSizeY, 0.1f, 100.0f);
		viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
		worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
		viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, kWindowSizeX, kWindowSizeY, 0.0f, 1.0f);

		//
		for (uint32_t i = 0; i < 3; i++) {
			ndcVertex[i] = Matrix4x4Funk::Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Matrix4x4Funk::Transform(ndcVertex[i], viewportMatrix);
		}



		Vector3 a, b, c = {};
		a = { ndcVertex[1].x - ndcVertex[0].x, ndcVertex[1].y - ndcVertex[0].y, ndcVertex[1].z - ndcVertex[0].z };
		b = { ndcVertex[2].x - ndcVertex[1].x, ndcVertex[2].y - ndcVertex[1].y, ndcVertex[2].z - ndcVertex[1].z };
		cameraFace = Matrix4x4Funk::Transform({ 0,0,1 }, viewMatrix);

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///

		// 行列の数値を表示
		Vector3Funk::VectorScreenPrintf(0, 0, cross, "Cross");

		if (Vector3Funk::Dot(cameraFace, Vector3Funk::Cross(a, b)) < 0) {

			// 描画
			Novice::DrawTriangle(
				int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
				int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid
			);

		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
