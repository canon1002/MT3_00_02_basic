#include <Novice.h>
#include"Matrix4x4.h"

const char kWindowTitle[] = "LD2A_12_ワタナベユウタ_";
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE,_In_opt_ HINSTANCE,_In_ LPSTR,_In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowSizeX, kWindowSizeY);

	// 行列・ベクトルの宣言
	Vector3 scale{ 1.2f,0.79f,-2.1f };
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Vector3 translate{ 2.7f,-4.15f,1.57f };

	// 行列の計算
	Matrix4x4 worldMatrix = Matrix4x4Ex::MakeAffineMatrix(scale, rotate, translate);

	
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
		Matrix4x4Ex::MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

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
