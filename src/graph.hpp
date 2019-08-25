#pragma once
template <typename W, typename F>
class graph
{
public:
	class vertex
	{
	public:
		W data;

		std::vector<pair<vertex*, F>> adjacent;

		vertex(const W& data)
			: data(data)
			, adjacent()
		{}
		template <typename it, typename it_end>
		vertex(const W& data, range<it, it_end> r)
			: data(data)
			, adjacent(r)
		{}
	};

	size_t count;
	vertex* V;

	template <typename it, typename it_end>
	graph(range<it, it_end> r)
		: count(distance(r))
		, V(allocate<vertex>(count))
	{
		u_copy(r, range(V, V + count));
	}

	void add_edge(size_t from, size_t to, const F & value = F())
	{
		V[from].adjacent.push_back(pair{ V + to, value });
	}

	void add_edge(vertex * from, vertex * to, const F & value = F())
	{
		if (from >= V && from < V + count)
			if (find(range(from->adjacent), to) == from->adjacent.end())
				from->adjacent.push_back(pair{ to, value });
	}

	F distance(vertex * from, vertex * to)
	{
		std::list<std::tuple<vertex*, bool, F>> queue;
	}

	~graph()
	{
		destroy(range(V, V + count));
		deallocate(V);
	}
};