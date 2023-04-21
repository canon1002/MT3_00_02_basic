#include <Novice.h>
#include"Matrix4.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// 行列・ベクトルの宣言
	Vector3 translate{ 4.1f,2.6f,0.8f };
	Vector3 scale{ 1.5f,5.2f,7.3f };
	Vector3 point{ 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};

	// 行列の計算
	Matrix4x4 translateMatrix = Matrix4::MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = Matrix4::MakeScaleMatrix(scale);
	Vector3 transformed = Matrix4::Transform(point, transformMatrix);
	

	
	// 表示用の変数
	const int kRowHeight = 30;
	const int kColumnWidth = 600;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 計算結果の表示
		Matrix4::VectorScreenPrintf(0, 0, transformed, "transfomed");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 2 , translateMatrix, "translateMatrix");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 2*3, scaleMatrix, "scaleMatrix");

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
