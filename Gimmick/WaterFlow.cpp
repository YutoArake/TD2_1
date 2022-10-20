#include "WaterFrow.h"

WaterFlow::~WaterFlow() { delete model_; }

//����������
void WaterFlow::Initialize(const Vector3& position, const Vector3& velocity) {

	//�����̃��f��
	model_ = Model::CreateFromOBJ("playerbullet", true);

	width_ = 10.0f;  //����
	height_ = 20.0f; //�c��

	//���[���h���W������
	worldTransform_.Initialize();
	//�����̏������W���Z�b�g
	worldTransform_.translation_ = position;
	speed_ = velocity;

	bright_ = 255; //���邳
}
void WaterFlow::Reset() { isActive_ = false; }

void WaterFlow::Update() {

	worldTransform_.translation_ += speed_;

	if (--deathTimer_ <= 0) {
		isActive_ = false;
	}

	//�s��X�V
	worldTransform_.Update(worldTransform_);
}

void WaterFlow::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}

Vector3 WaterFlow::GetWorldPosition() {
	//���[���h���W���擾
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void WaterFlow::OnCollision(){};