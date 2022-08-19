#include "Enemy.h"
#include "Player.h"
// 初期化
void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("texture/enemy.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {1.0f, 1.0f, 30.0f};

	//初期フェーズ
	phase_ = Phase::Approach;
	//接近フェーズ初期化
	InitializeApproach();
}
// 接近フェーズ初期化
void Enemy::InitializeApproach() {
	//発射タイマー初期化
	fireTimer = kFireInterval;
}

//更新
void Enemy::Update() {
	//座標を移動させる
	switch (phase_) {
	case Enemy::Phase::Approach:

		UpdateApproach();
		break;

	case Enemy::Phase::Leave:
		UpdateLeave();
		break;
	}
	//弾更新
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Update();
	}

	//行列更新
	worldTransform_.Update(worldTransform_);
}

//弾発射
void Enemy::Fire() {

	assert(player_);

	//弾の速度
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0.1f, kBulletSpeed);

	//自機のワールド座標を取得
	player_->GetWorldPosition();
	//敵のワールド座標を取得
	GetWorldPosition();
	//敵→自機の差分ベクトルを求める
	velocity = GetWorldPosition() -= player_->GetWorldPosition();
	// ベクトルの正規化
	MyMathUtility::MyVector3Normalize(velocity);
	// ベクトルの長さを速さに合わせる
	
	////ベクトルと行列で掛け算
	//velocity = MyMathUtility::MyVector3TransformNormal(velocity, worldTransform_.matWorld_);
	////敵キャラの座標をコピー
	//Vector3 position = worldTransform_.translation_;

	//弾を生成し初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	//弾を登録
	enemyBullets_.push_back(std::move(newBullet));
}

//描画
void Enemy::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//弾描画
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullets_) {
		bullet->Draw(viewProjection);
	}
}

//状態変化用の更新関数
//接近
void Enemy::UpdateApproach() {
	//速度
	Vector3 velocity;

	//移動
	velocity = {0.0f, 0.0f, -0.1f};
	worldTransform_.translation_ += velocity;

	//発射タイマーカウントダウン
	fireTimer--;
	//指定時間に達した
	if (fireTimer <= 0) {
		//弾発射
		Fire();
		//発射タイマー初期化
		fireTimer = kFireInterval;
	}

	//指定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

//離脱
void Enemy::UpdateLeave() {
	//速度
	Vector3 velocity;

	//移動
	velocity = {0.1f, 0.1f, 0.0f};
	worldTransform_.translation_ += velocity;
}

//ワールド座標を取得
Vector3 Enemy::GetWorldPosition() {

	//ワールド座標を取得
	Vector3 worldPos;

	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}