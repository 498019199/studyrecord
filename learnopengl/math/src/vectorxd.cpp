#include <math/vectorxd.h>
#include "math_helper.h"
#include "math/math.h"

namespace MathWorker
{

template<typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>::Vector_T()  noexcept
{}

template<typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>::Vector_T(const ValTy* rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>
    ::DoCopy(&vec_[0], rhs);
}

template<typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>::Vector_T(const ValTy& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>
    ::DoAssign(&vec_[0], rhs);
}

template<typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>::Vector_T(const Vector_T& rhs) noexcept 
{
    MathHelper::vector_helper<ValTy, SIZE>
    ::DoCopy(&vec_[0], &rhs.vec_[0]);
}

template<typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>::Vector_T(Vector_T&& rhs) noexcept
    :vec_(std::move(rhs.vec_))
{}

template <typename ValTy, int SIZE>
template<typename U, int M>
Vector_T<ValTy, SIZE>::Vector_T(const Vector_T<U, M>& rhs) noexcept
{
    static_assert(M >= SIZE, "Could not convert to a smaller vector.");

    MathHelper::vector_helper<ValTy, SIZE>
        ::DoCopy(&vec_[0], &rhs.vec_[0]);
}

// 零向量
template <typename ValTy, int SIZE>
static Vector_T<ValTy, SIZE> 
const Vector_T<ValTy, SIZE>::Zero() noexcept
{
    static Vector_T<ValTy, SIZE> const zero(value_type(0));
    return zero;
}

// operator +
template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator+=(const Vector_T<U, SIZE>& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoAdd(&vec_[0], &vec_[0], &rhs.vec_[0]);
    return *this;
}

template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator+=(const U& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoAdd(&vec_[0], &vec_[0], rhs);
    return *this;
}

// operator -
template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator-=(const Vector_T<U, SIZE>& rhs) noexcept
{
    MathHelper::vector_helper<U, SIZE>::DoSub(&vec_[0], &vec_[0], &rhs.vec_[0]);
    return *this;
}

template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator-=(const U& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoSub(&vec_[0], &vec_[0], rhs);
    return *this;
}

// operator * 点积
template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator|(const Vector_T<U, SIZE>& rhs) noexcept
{
    return Dot<ValTy, SIZE>(*this, rhs);
}

template <typename ValTy, int SIZE>
template <typename U>
ValTy Vector_T<ValTy, SIZE>::operator^(const Vector_T<U, SIZE>& rhs) noexcept
{
    return Cross<ValTy, SIZE>(*this, rhs);
}

// operator * 数乘
template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator*=(const U& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoScale(&vec_[0], &vec_[0], rhs);
    return *this;
}

template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator*(const U& rhs) noexcept
{
    return this->operator*=(rhs);
}

// operator /
template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator/=(const Vector_T<U, SIZE>& rhs) noexcept
{
    MathHelper::vector_helper<U, SIZE>::DoDiv(&vec_[0], &vec_[0], &rhs.vec_[0]);
    return *this;
}

template <typename ValTy, int SIZE>
template <typename U>
const Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator/=(const U& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoScale(&vec_[0], &vec_[0], rhs);
    return *this;
}
    
// 复制构造
template <typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator=(const Vector_T<ValTy, SIZE>& rhs) noexcept
{
    if (this != &rhs)
        vec_ = rhs.vec_;
    return *this;
}

template <typename ValTy, int SIZE>
Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator=(Vector_T<ValTy, SIZE>&& rhs) noexcept
{
    vec_ = std::move(rhs.vec_);
    return *this;
}

template <typename ValTy, int SIZE>
template <typename U, int M>
Vector_T<ValTy, SIZE>& 
Vector_T<ValTy, SIZE>::operator=(Vector_T<U, M> const & rhs) noexcept
{
    static_assert(M >= SIZE, "Could not assign to a smaller vector.");

    MathHelper::vector_helper<ValTy, SIZE>::DoCopy(&vec_[0], &rhs.vec_[0]);
    return *this;
}



// 正
template <typename ValTy, int SIZE>
const Vector_T<ValTy, SIZE> 
Vector_T<ValTy, SIZE>::operator+() const  noexcept
{
    return *this;
}

// 负
template <typename ValTy, int SIZE>
const Vector_T<ValTy, SIZE> Vector_T<ValTy, SIZE>::operator-() const noexcept
{
    Vector_T tmp(*this);
    MathHelper::vector_helper<ValTy, SIZE>::DoNegate(&tmp.vec_[0], &this->vec_[0]);
    return tmp;
}

template <typename ValTy, int SIZE>
void Vector_T<ValTy, SIZE>::swap(Vector_T& rhs) noexcept
{
    MathHelper::vector_helper<ValTy, SIZE>::DoSwap(&vec_[0], &rhs[0]);
}

// operator ==
template <typename ValTy, int SIZE>
bool Vector_T<ValTy, SIZE>::operator==(const Vector_T& rhs) const noexcept
{
    return MathHelper::vector_helper<ValTy, SIZE>::DoEquip(&vec_[0], &rhs[0]);
}

template <typename ValTy, int SIZE>
bool Vector_T<ValTy, SIZE>::operator!=(const Vector_T& rhs) const noexcept
{
    return !(this->operator==(rhs));
}



// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator+(const Vector_T<U, SIZE>& lhs, const Vector_T<U, SIZE>& rhs) noexcept
// {
//     return lhs.operator+=(rhs);
// }

// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator-(const Vector_T<U, SIZE>& lhs, const Vector_T<U, SIZE>& rhs) noexcept
// {
//     return lhs.operator-=(rhs);
// }

// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator|(const Vector_T<U, SIZE>& lhs, const Vector_T<U, SIZE>& rhs) noexcept
// {
//     return lhs.operator|(rhs);
// }

// template <typename U, int SIZE>
// U operator^(const Vector_T<U, SIZE>& lhs, const Vector_T<U, SIZE>& rhs) noexcept
// {
//     return lhs.operator^(rhs);  
// }

// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator/(const Vector_T<U, SIZE>& lhs, const Vector_T<U, SIZE>& rhs) noexcept
// {
//     return lhs.operator/(rhs);  
// }

// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator*(const Vector_T<U, SIZE>& lhs, const U& rhs) noexcept
// {
//     return lhs.operator*=(rhs);
// }

// template <typename U, int SIZE>
// const Vector_T<U, SIZE>& 
// operator/(const Vector_T<U, SIZE>& lhs, const U& rhs) noexcept
// {
//     return lhs.operator/=(rhs);
// }
}