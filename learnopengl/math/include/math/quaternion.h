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

	Quaternion& operator=(const Quaternion & rhs) noexcept;
	Quaternion& operator=(Quaternion&& rhs) noexcept;

		// 赋值操作符
	const Quaternion& operator+=(const Quaternion & rhs) noexcept;
	const Quaternion& operator-=(const Quaternion & rhs) noexcept;
	const Quaternion& operator*=(const Quaternion & rhs) noexcept;
	const Quaternion& operator*=(float rhs) noexcept;
	const Quaternion& operator/=(float rhs) noexcept;
	
	// 取方向向量
	const Vector3D GetV() const noexcept;
	void SetV(const Vector3D& rhs) noexcept;

	bool operator==(const Quaternion& rhs) const noexcept;
	bool operator!=(const Quaternion& rhs) const noexcept;
};

}