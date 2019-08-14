#pragma once
#include "fundamental_integers_signed.hpp"
#include "fundamental_integers_unsigned.hpp"
using fundamental_integers = fundamental_integers_signed::append<fundamental_integers_unsigned>;