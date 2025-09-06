#include "pch.h"
#include "Camera.h"
#include "World.h"
#include "InputManager.h"

void Camera::Update(float deltaTime)
{
    if (_inputVector.Length() > 0.0f)
    {
        _position += _inputVector * _speed * deltaTime;
        _inputVector = SimpleMath::Vector3::Zero;
    }
    if (_rotateInputVector.Length() > 0.0f)
    {
        _rotation += _rotateInputVector * _rotateSpeed * deltaTime;
        _rotateInputVector = SimpleMath::Vector3::Zero;
    }

    _worldTransform = SimpleMath::Matrix::CreateFromYawPitchRoll(_rotation) *
        SimpleMath::Matrix::CreateTranslation(_position);
}

void Camera::GetViewMatrix(OUT Matrix& view)
{
    SimpleMath::Vector3 eye = _worldTransform.Translation();
    SimpleMath::Vector3 target = _worldTransform.Translation() + GetForward();
    SimpleMath::Vector3 up = _worldTransform.Up();
    view = XMMatrixLookAtLH(eye, target, up);
}

void Camera::GetProjectionMatrix(OUT Matrix& projection)
{
    projection = XMMatrixPerspectiveFovLH(XMConvertToRadians(_fieldOfView), _aspectRatio, _nearPlane, _farPlane);
}

void Camera::AddInputVector(const SimpleMath::Vector3 input)
{
    _inputVector += input;
    _inputVector.Normalize();
}

void Camera::AddRotateInputVector(const SimpleMath::Vector3 input)
{
    _rotateInputVector += input;
}
