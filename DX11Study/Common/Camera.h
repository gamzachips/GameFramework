#pragma once
class Camera
{
public:
    Camera() {}
    void Update(float deltaTime); //By Input

    void GetViewMatrix(OUT Matrix& view);
    void GetProjectionMatrix(OUT Matrix& projection);

    SimpleMath::Vector3& GetPosition() { return _position; }
    SimpleMath::Vector3& GetRotation() { return _rotation; }
    SimpleMath::Vector3 GetForward() { return -_worldTransform.Forward(); }
    SimpleMath::Vector3 GetRight() { return _worldTransform.Right(); }

    float& GetFOV() { return _fieldOfView; }
    float& GetNear() { return _nearPlane; }
    float& GetFar() { return _farPlane; }
    void AddInputVector(const SimpleMath::Vector3 input);
    void AddRotateInputVector(const SimpleMath::Vector3 input);
    void SetSpeed(float speed) { _speed = speed; }
    void SetRotateSpeed(float speed) { _rotateSpeed = speed; }

private:
    SimpleMath::Vector3 _position = { 0.0f, 0.0f, -500.0f };
    SimpleMath::Vector3 _rotation = { 0.0f, 0.0f, 0.0f };
    SimpleMath::Matrix _worldTransform ;
    SimpleMath::Vector3 _inputVector;
    SimpleMath::Vector3 _rotateInputVector;
    float _speed = 200.f;
    float _rotateSpeed = 5.f;

    float _fieldOfView = 45;
    float _aspectRatio = (float)GWinSizeX / GWinSizeY;
    float _nearPlane = 0.1f;
    float _farPlane = 1000000.f;
};

