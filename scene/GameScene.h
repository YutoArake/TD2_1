﻿#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "GlobalScene.h"
#include "Input.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Skydome/Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <memory>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void ChackAllCollisions();

	size_t GetScene() { return scene_; }

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	Model* model_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//カメラ上方向の角度
	float viewAngle = 0.0f;
	//自キャラ
	Player* player_ = nullptr;
	Model* modelPlayer_ = nullptr;
	//天球データ
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//デバッグカメラ有効化
	bool isDebugCameraActive_ = false;
	size_t scene_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};