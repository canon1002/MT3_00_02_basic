#include <Novice.h>
#include"Matrix4.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// 行列の宣言
	Matrix4x4 m1 = { 
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	};

	Matrix4x4 m2 = {
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	// 行列の計算
	Matrix4x4 resultAdd = Matrix4::Add(m1, m2);
	Matrix4x4 resultSubtract = Matrix4::Subtract(m1, m2);
	Matrix4x4 resultMulttiply = Matrix4::Multiply(m1, m2);
	Matrix4x4 inverseM1 = Matrix4::Inverse(m1);
	Matrix4x4 inverseM2 = Matrix4::Inverse(m2);
	Matrix4x4 transposeM1 = Matrix4::Transpose(m1);
	Matrix4x4 transposeM2 = Matrix4::Transpose(m2);
	Matrix4x4 identity = Matrix4::MakeIdentity();
	
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
		Matrix4::MatrixScreenPrintf(0, 0, resultAdd, "Add");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 4, resultSubtract, "Subtract");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 4 * 2, resultMulttiply, "Multtiply");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 4 * 3, inverseM1, "inverseM1");
		Matrix4::MatrixScreenPrintf(0, kRowHeight * 4 * 4, inverseM2, "inverseM2");
		Matrix4::MatrixScreenPrintf(kColumnWidth, 0, transposeM1, "transposeM1");
		Matrix4::MatrixScreenPrintf(kColumnWidth, kRowHeight * 4, transposeM2, "transposeM2");
		Matrix4::MatrixScreenPrintf(kColumnWidth, kRowHeight * 4 * 2, identity, "identity");

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
