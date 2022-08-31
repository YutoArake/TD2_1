#pragma once
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Model.h"
#include "MyMathUtility.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>
//自機クラスの前方宣言
class Player;

//敵
class Enemy {
  public:
	~Enemy();
	//弾発射間隔
	static const int kFireInterval = 60;
	//初期化
	void Initialize(Model* model);
	//接近フェーズ初期化
	void InitializeApproach();
	//リセット処理
	void Reset();
	//パラメータ
	void Stage1Parameter();
	//更新
	void Update();
	//弾発射
	void Fire();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	//描画
	void Draw(const ViewProjection& viewProjection);

	//状態変化用の更新関数
	//接近
	void UpdateApproach();
	//攻撃
	void UpdateAttack();
	//離脱
	void UpdateLeave();

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollisionPlayer();
	void OnCollisionOption();

	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() { return enemyBullets_; }

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;
	//デバックテキスト
	DebugText* debugText_ = nullptr;
	//モデル
	Model* model_ = nullptr;
	Model* modelDead_ = nullptr;
	Model* modelBullet_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//行動フェーズ
	enum class Phase {
		Approach, //接近
		Attack,   //攻撃
		Leave,    //離脱
	};

	//フェーズ
	Phase phase_;
	//弾発射タイマー
	int32_t fireTimer = 0;

	//自機
	Player* player_ = nullptr;
	//死亡フラグとライフ
	bool isDead_ = false;
	int life_ = 15;
	//反転フラグ
	bool isReverse_ = false;

  public:
	bool IsDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
};
