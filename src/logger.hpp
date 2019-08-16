#pragma once

struct bim
{
	bim();
	bim(const bim&);
	bim(bim&&) noexcept;
	bim& operator=(const bim&);
	bim& operator=(bim&&);
	~bim();
};