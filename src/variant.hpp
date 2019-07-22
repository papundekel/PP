template <typename ...T>
class variant
{

public:
	union
	{
		T... value;
	};
};