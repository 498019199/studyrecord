#pragma once


namespace MathWorker
{
class Vector3D;

struct Quaternion
{
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;

public:
    // (0, 0, 0, 0)
    static Quaternion ZeroQuat;

public:
	constexpr Quaternion() noexcept
	{
	}

	explicit constexpr Quaternion(const float * rhs) noexcept;
	constexpr Quaternion(const Vector3D& vec, float s) noexcept;
	Quaternion(const Quaternion & rhs) noexcept;
	Quaternion(Quaternion&& rhs) noexcept;
	constexpr Quaternion(float x, float y, float z, float w) noexcept;
};

}