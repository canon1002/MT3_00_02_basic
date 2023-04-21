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
	Vector3 rotate{ 0.4f,1.43f,-0.8f };

	// 行列の計算
	Matrix4x4 rotateXMatrix = Matrix4::MekeRoatateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Matrix4::MekeRoatateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Matrix4::MekeRoatateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Matrix4::Multiply(rotateXMatrix, Matrix4::Multiply(rotateYMatrix, rotateZMatrix));
	
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
		Matrix4::MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 2 * 3, rotateYMatrix, "rotateYMatrix");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 2 * 6, rotateZMatrix, "rotateZMatrix");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 2 * 9, rotateXYZMatrix, "rotateXYZMatrix");

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
