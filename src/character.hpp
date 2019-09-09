#pragma once
#include "pack.hpp"
#include "fundamental_chars.hpp"

template <typename T>
using character = val<fundamental_chars::contains<same<T>::as>>;