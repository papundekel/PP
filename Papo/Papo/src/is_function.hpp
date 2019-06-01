#pragma once

template <typename T>						   constexpr bool is_function						= false;
template <typename return_t, typename ...args> constexpr bool is_function<return_t(args...)>	=  true;
template <typename return_t, typename ...args> constexpr bool is_function<return_t(args......)> =  true;