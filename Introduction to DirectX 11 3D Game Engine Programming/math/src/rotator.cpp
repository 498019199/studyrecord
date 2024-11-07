#include <math/rotator.h>
namespace MathWorker
{
template<typename T>
Rotator_T<T>::Rotator_T(const Rotator_T & rhs) noexcept
	:rot_(rhs.rot_)
{
    
}

template<typename T>
Rotator_T<T>::Rotator_T(Rotator_T&& rhs) noexcept
	:rot_(std::move(rhs.rot_))
{
    
}

template<typename T>
constexpr Rotator_T<T>::Rotator_T(T inF)
{
    this->rot_.pitch() = inF;
	this->rot_.yaw() = inF;
	this->rot_.roll() = inF;
}

template<typename T>
constexpr Rotator_T<T>::Rotator_T(T in_x, T in_y, T in_z) noexcept
{
    this->rot_.pitch() = in_x;
	this->rot_.yaw() = in_y;
	this->rot_.roll() = in_z;
}

template<typename T>
const Rotator_T<T>& Rotator_T<T>::operator-=(const Rotator_T<T> & rhs) noexcept
{
    this->rot_ -= rhs.rot_;
	return *this;
}

template<typename T>
const Rotator_T<T>& Rotator_T<T>::operator+=(const Rotator_T<T> & rhs) noexcept
{
    this->rot_ += rhs.rot_;
	return *this;    
}

template<typename T>
const Rotator_T<T>& Rotator_T<T>::operator*=(const Rotator_T<T> & rhs) noexcept
{
    this->rot_ *= rhs.rot_;
	return *this;
}

template<typename T>
const Rotator_T<T>& Rotator_T<T>::operator*=(T rhs) noexcept
{
    this->rot_ *= static_cast<T>(rhs);
	return *this;
}

template<typename T>
const Rotator_T<T>& Rotator_T<T>::operator/=(T rhs) noexcept
{
    this->rot_ /= static_cast<T>(rhs);
	return *this;    
}

template<typename T>
Rotator_T<T>& Rotator_T<T>::operator=(const Rotator_T & rhs) noexcept
{
    if (this != &rhs)
	{
		this->rot_ = rhs.rot_;
	}

	return *this;
}

template<typename T>
Rotator_T<T>& Rotator_T<T>::operator=(Rotator_T&& rhs) noexcept
{
    this->rot_ = std::move(rhs.rot_);
	return *this;
}

template<typename T>
Rotator_T<T> const Rotator_T<T>::operator-() const noexcept
{
    return *this;
}

template<typename T>
Rotator_T<T> const Rotator_T<T>::operator+() const noexcept
{
    return 	Rotator_T<T>(-rot_.x(), -rot_.y(), -rot_.z()); 
}

template<typename T>
bool Rotator_T<T>::operator==(Rotator_T<T> const & rhs) const noexcept
{
    this->rot_ == rhs.rot_;
}

template<typename T>
bool Rotator_T<T>::operator!=(Rotator_T<T> const & rhs) const noexcept
{
    this->rot_ != rhs.rot_;
}

template<typename T>
Rotator_T<T> Rotator_T<T>::operator+(const Rotator_T & rhs) const noexcept
{
    return Rotator_T<T>(*this).operator+=(rhs);
}

template<typename T>
Rotator_T<T> Rotator_T<T>::operator-(const Rotator_T & rhs) const noexcept
{
    return Rotator_T<T>(*this).operator-=(rhs);    
}

template<typename T>
Rotator_T<T> Rotator_T<T>::operator*(const Rotator_T & rhs) const noexcept
{
    return Rotator_T<T>(*this).operator*=(rhs);
}

template<typename T>
Rotator_T<T> Rotator_T<T>::operator*(T rhs) const noexcept
{
    return Rotator_T<T>(*this).operator*=(rhs);
}

template<typename T>
Rotator_T<T> Rotator_T<T>::operator/(T rhs) const noexcept
{
    return Rotator_T<T>(*this).operator/=(rhs);    
}


}