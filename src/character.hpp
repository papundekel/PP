#pragma once
#include "pack.hpp"
#include "fundamental_chars.hpp"

template <typename T>
struct character : value_t<fundamental_chars::contains<same<T>::as>> {};