#pragma once
#include <cstdint>
#include <tuple>

namespace CommonWorker
{

template<typename R,typename...ARGS>
struct task_function
{
	using Function = R(*)(ARGS...);
	using TupleSequence = std::make_index_sequence<sizeof...(ARGS)>;

    explicit task_function(Function _pfun, ARGS... args)
	{
		fun_ = _pfun,
		args_ = std::make_tuple(args...);
	}

	R DoCall()
	{
		return DoCall_Impl(TupleSequence());
	}

private:
	template<size_t... Index>
	R DoCall_Impl(std::index_sequence<Index...>)
	{
		return (*fun_)(std::get<Index>(args_)...);
	}

	Function fun_;
	std::tuple<ARGS...> args_;
};

template<typename R,typename...ARGS>
decltype(auto) MakeTaskFunction(R(*fun)(ARGS...), ARGS... args)
{
	return task_function(fun,args...);
}

}