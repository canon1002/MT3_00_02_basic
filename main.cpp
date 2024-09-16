#include <Novice.h>
#include "Matrix4x4Funk.h"
#include "Vector3Funk.h"
#include "MathTool.h"
#include <stdint.h>
#include <ImGuiManager.h>

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const float kWindowSizeX = 1280.0f;
const float kWindowSizeY = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, int(kWindowSizeX), int(kWindowSizeY));

	// 行列・ベクトルの宣言
	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraPosition = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	// ワールドからスクリーンへ
	Matrix4x4 worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	Matrix4x4 cameraMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
	Matrix4x4 viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.45f, kWindowSizeX / kWindowSizeY, 0.1f, 100.0f);
	Matrix4x4 viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
	Matrix4x4 worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
	Matrix4x4 viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, kWindowSizeX, kWindowSizeY, 0.0f, 1.0f);

	// 表示用の変数
	const int kRowHeight = 30;
	const int kColumnWidth = 600;

	//
	// 課題用変数　ここから
	//

	// 球
	Sphere sphere = {
		{0,0,0} ,
		1,
	};

	//
	//　課題用変数　ここまで
	//


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


		// 行列の更新
		worldMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		cameraMatrix = Matrix4x4Funk::MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraPosition);
		viewMatrix = Matrix4x4Funk::Inverse(cameraMatrix);
		projectionMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.45f, kWindowSizeX / kWindowSizeY, 0.1f, 100.0f);
		viewprojectionMatrix = Matrix4x4Funk::Multiply(viewMatrix, projectionMatrix);
		worldViewProjectionMatrix = Matrix4x4Funk::Multiply(worldMatrix, viewprojectionMatrix);
		viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(0, 0, kWindowSizeX, kWindowSizeY, 0.0f, 1.0f);

		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTransrate", &cameraPosition.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///



		///
		/// ↓描画処理ここから
		///

		// グリッド線の表示
		DrawGrid(worldViewProjectionMatrix, viewportMatrix);

		// 球体を表示
		DrawSphere(sphere,worldViewProjectionMatrix, viewportMatrix,0x33FF33FF);

		// 行列の数値を表示
		

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
