#include <math/matrix.h>
#include <math/math.h>
namespace MathWorker
{

template <typename Valty>
Matrix4_T<Valty>::Matrix4_T(const Valty* rhs) noexcept
{
	for (Matrix4_T::size_type i = 0; i < row_num; ++i)
	{
		this->m_[i] = Vector_T<Valty, col_num>(rhs);
		rhs += col_num;
	}
}

template <typename Valty>
Matrix4_T<Valty>::Matrix4_T(const Matrix4_T& rhs) noexcept
	:m_(std::move(rhs.m_))
{

}

template <typename Valty>
Matrix4_T<Valty>::Matrix4_T(Matrix4_T&& rhs) noexcept
    :m_(std::move(rhs.m_))
{

}

template <typename Valty>
Matrix4_T<Valty>::Matrix4_T(Valty f11, Valty f12, Valty f13, Valty f14
    , Valty f21, Valty f22, Valty f23, Valty f24
    , Valty f31, Valty f32, Valty f33, Valty f34
    , Valty f41, Valty f42, Valty f43, Valty f44) noexcept
{
    m_[0][0] = f11; m_[0][1] = f12; m_[0][2] = f13; m_[0][3] = f14;
    m_[1][0] = f21; m_[1][1] = f22; m_[1][2] = f23; m_[1][3] = f24;
    m_[2][0] = f31; m_[2][1] = f32; m_[2][2] = f33; m_[2][3] = f34;
    m_[3][0] = f41; m_[3][1] = f42; m_[3][2] = f43; m_[3][3] = f44;
}

template <typename Valty>
Vector_T<Valty, 4> Matrix4_T<Valty>::Col(size_t index) const noexcept
{
	Vector_T<Valty, col_num> tmp;
	for (Matrix4_T::size_type i = 0; i < row_num; ++i)
	{
		tmp[i] = this->m_[i][index];
	}

	return tmp;
}

template <typename Valty>
const Vector_T<Valty, 4>& Matrix4_T<Valty>::Row(size_t index)  const noexcept
{
	return this->m_[index];
}

template <typename Valty>
void Matrix4_T<Valty>::Col(size_t index, const Vector_T<Valty, 4>& rhs) noexcept
{
	for (Matrix4_T::size_type i = 0; i < row_num; ++i)
	{
		this->m_[i][index] = rhs[i];
	}
}

template <typename Valty>
void Matrix4_T<Valty>::Row(size_t index, const Vector_T<Valty, 4>& rhs) noexcept
{
	this->m_[index] = rhs;
}

template <typename Valty>
Matrix4_T<Valty> Matrix4_T<Valty>::operator-() const noexcept
{
	Matrix4_T<Valty> tmp(*this);
	tmp.m_ = -this->m_;
	return tmp;
}

template <typename Valty>
Matrix4_T<Valty> Matrix4_T<Valty>::operator+() const noexcept
{
	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& Matrix4_T<Valty>::operator=(Matrix4_T&& rhs) noexcept
{
	this->m_ = std::move(rhs.m_);
	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator=(const Matrix4_T& rhs) noexcept
{
	if (this != &rhs)
	{
		this->m_ = rhs.m_;
	}

	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator/=(value_type rhs) noexcept
{
	return this->operator*=(RecipSqrt(rhs));
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator*=(value_type rhs) noexcept
{
	for (size_type i = 0; i < row_num; ++i)
	{
		this->m_[i] *= rhs;
	}
	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator*=(const Matrix4_T& rhs) noexcept
{
	*this = Mul(*this, rhs);
	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator-=(const Matrix4_T& rhs) noexcept
{
	this->m_ -= rhs.m_;
	return *this;
}

template <typename Valty>
Matrix4_T<Valty>& 
Matrix4_T<Valty>::operator+=(const Matrix4_T<Valty>& rhs) noexcept
{
	this->m_ += rhs.m_;
	return *this;
}


template <typename Valty>
const Matrix4_T<Valty> & 
Matrix4_T<Valty>::Zero() noexcept
{
    static const Matrix4_T out(0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0);
    return out;
}

template <typename Valty>
const Matrix4_T<Valty> & 
Matrix4_T<Valty>::Identity() noexcept
{
    static const Matrix4_T out(1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
    return out;
}

template <typename Valty>
bool Matrix4_T<Valty>::operator==(const Matrix4_T<Valty>& rhs) const noexcept
{
	return m_ == rhs.m_;
}

// 实例化模板
template class Matrix4_T<float>;
}