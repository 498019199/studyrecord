#pragma once
#include <array>

namespace MathWorker
{

template <typename ValTy, int SIZE>
class Vector_T
{
    template<typename ValTy, int SIZE>
    friend class Vector_T;
	typedef std::array<ValTy, SIZE> DetailType;
public:
    typedef typename DetailType::value_type value_type;
	typedef value_type* pointer;
	typedef  value_type const * const_pointer;
	typedef typename DetailType::reference reference;
	typedef typename DetailType::const_reference const_reference;
	typedef typename DetailType::iterator iterator;
	typedef typename DetailType::const_iterator const_iterator;
	typedef typename DetailType::size_type size_type;
	typedef typename DetailType::difference_type difference_type;
	enum{ elem_num = SIZE };

public:
	Vector_T()  noexcept;
	explicit Vector_T(const ValTy* rhs) noexcept;
	explicit Vector_T(const ValTy& rhs) noexcept;
	Vector_T(const Vector_T& rhs) noexcept;
	Vector_T(Vector_T&& rhs) noexcept;
	template<typename U, int M>
	Vector_T(const Vector_T<U, M>& rhs) noexcept;

	Vector_T(const ValTy& x, const ValTy& y) noexcept
		:vec_ {x, y}
	{
		static_assert(2 == elem_num, "must be 2D vecotr");
	}
	Vector_T(ValTy&& x, ValTy&& y) noexcept
		: vec_{ std::move(x), std::move(y) }
	{
		static_assert(2 == elem_num, "must be 2D vecotr");
	}
	Vector_T(const ValTy& x, const ValTy& y, const ValTy& z) noexcept
		: vec_{ x, y , z}
	{
		static_assert(3 == elem_num, "must be 3D vecotr");
	}
	Vector_T(ValTy&& x, ValTy&& y, ValTy&& z) noexcept
		: vec_{ std::move(x), std::move(y) , std::move(z) }
	{
		static_assert(3 == elem_num, "must be 3D vecotr");
	}
	Vector_T(const ValTy& x, const ValTy& y, const ValTy& z, const ValTy& w) noexcept
		: vec_{ x, y , z, w }
	{
		static_assert(4 == elem_num, "must be 4D vecotr");
	}
	Vector_T(ValTy&& x, ValTy&& y, ValTy&& z, ValTy&& w) noexcept
		: vec_{ std::move(x), std::move(y) , std::move(z), std::move(w) }
	{
		static_assert(4 == elem_num, "must be 4D vecotr");
	}

	// size
	size_t size() noexcept
	{
		return elem_num;
	}

	size_t size() const noexcept
	{
		return elem_num;
	}

	// 零向量
	static Vector_T const Zero() noexcept;

	iterator begin() noexcept
	{
		return vec_.begin();
	}
	constexpr const_iterator begin() const noexcept
	{
		return vec_.begin();
	}
	iterator end() noexcept
	{
		return vec_.end();
	}
	constexpr const_iterator end() const noexcept
	{
		return vec_.end();
	}
	reference operator[](size_type off) noexcept
	{
		return vec_[off];
	}
	constexpr const_reference operator[](size_type off) const noexcept
	{
		return vec_[off];
	}
	reference x() noexcept
	{
		return vec_[0];
	}
	constexpr const_reference x() const noexcept
	{
		return vec_[0];
	}
	reference y() noexcept
	{
		static_assert(elem_num >= 2, "must be 2D vecotr");
		return vec_[1];
	}
	constexpr const_reference y() const noexcept
	{
		static_assert(elem_num >= 2, "must be 2D vecotr");
		return vec_[1];
	}
	reference z() noexcept
	{
		static_assert(elem_num >= 3, "must be 3D vecotr");
		return vec_[2];
	}
	constexpr const_reference z() const noexcept
	{
		static_assert(elem_num >= 3, "must be 3D vecotr");
		return vec_[2];
	}
	reference w() noexcept
	{
		static_assert(elem_num >= 4, "must be 4D vecotr");
		return vec_[3];
	}
	constexpr const_reference w() const noexcept
	{
		static_assert(elem_num >= 4, "must be 4D vecotr");
		return vec_[3];
	}

	// operator +
	template <typename U>
	const Vector_T& operator+=(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator+=(const U& rhs) noexcept;

	template <typename U>
	const Vector_T& operator+(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator+(const U& rhs) noexcept;

	// operator -
	template <typename U>
	const Vector_T& operator-=(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator-=(const U& rhs) const noexcept;

	template <typename U>
	const Vector_T& operator-(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator-(const U& rhs) const noexcept;

	// operator 叉积
	Vector_T operator^(const Vector_T& rhs) const noexcept;
	// operator 点积
	ValTy operator|(const Vector_T& rhs) const noexcept;

	// operator * 数乘
	template <typename U>
	const Vector_T& operator*=(const U& rhs) const noexcept;

	template <typename U>
	const Vector_T& operator*(const U& rhs) const noexcept;
	
	 // operator /
	template <typename U>
	const Vector_T& operator/=(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator/=(const U& rhs) const noexcept;

	template <typename U>
	const Vector_T& operator/(const Vector_T<U, SIZE>& rhs) const noexcept;
	template <typename U>
	const Vector_T& operator/(const U& rhs) const noexcept;

	// 复制构造
	Vector_T& operator=(const Vector_T& rhs) noexcept;
	Vector_T& operator=(Vector_T&& rhs) noexcept;

	template <typename U, int M>
	Vector_T& operator=(Vector_T<U, M> const & rhs) noexcept;

	// 正
	const Vector_T operator+() const  noexcept;
	// 负
	const Vector_T operator-() const noexcept;

	void swap(Vector_T& rhs) noexcept;

	// operator ==
	bool operator==(const Vector_T& rhs) const noexcept;
	// operator ==
	bool operator!=(const Vector_T& rhs) const noexcept;
private:
	DetailType vec_;
};
}