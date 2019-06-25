#pragma once

template <typename T>
concept integer = static_cast<T>(1) / static_cast<T>(2) == 0;