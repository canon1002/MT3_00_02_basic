#include <Novice.h>
#include"Matrix4x4Funk.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// 行列・ベクトルの宣言
	Matrix4x4 orthographicMatrix = Matrix4x4Funk::MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
	Matrix4x4 perspectiveFovMatrix = Matrix4x4Funk::MakePerspectiveMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix4x4 viewportMatrix = Matrix4x4Funk::MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

	// 行列の計算


	
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

		// 行列の数値を表示
		Matrix4x4Funk::MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		Matrix4x4Funk::MatrixScreenPrintf(0, 100, perspectiveFovMatrix, "perspectiveFovMatrix");
		Matrix4x4Funk::MatrixScreenPrintf(0, 200, viewportMatrix, "viewportMatrix");
		

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
