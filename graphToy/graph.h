#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
using std::string;
using std::hash;
class Edge
{
public:
	string src;
	string pred;
	string tgt;
	struct EdgeHash
	{
		size_t operator()(const Edge& rhs) const
		{
			return hash<string>()(rhs.src) ^
				hash<string>()(rhs.tgt) ^
				hash<string>()(rhs.pred);
		}
	};
	struct EdgeCmp
	{
		bool operator()(const Edge& lhs, const Edge& rhs) const {
			return lhs.src == rhs.src &&
				lhs.tgt == rhs.tgt &&
				lhs.pred == rhs.pred;
		}
	};
};

using EdgeSet = std::unordered_set<Edge, Edge::EdgeHash, Edge::EdgeCmp>;
using VertexSet = std::unordered_set<string>;
class Graph
{
public:
	void addEdge(const Edge &e);
	void removeEdge(const Edge &e);

	EdgeSet& hasSrc(string src);
	EdgeSet& hasTgt(string tgt);
	EdgeSet  hasSrcVertexSet(VertexSet v);
	EdgeSet  hasTgtVertexSet(VertexSet v);
	EdgeSet& hasPred(string desc);
	EdgeSet hasV(string v);
private:
	std::unordered_map<string, EdgeSet> SrcToEdgeSetMap;
	std::unordered_map<string, EdgeSet> TgtToEdgeSetMap;
	std::unordered_map<string, EdgeSet> DescToEdgeSetMap;
};


EdgeSet hasPred(const EdgeSet &es, string pred);
EdgeSet hasTgt(const EdgeSet &es, string tgt);
EdgeSet hasSrc(const EdgeSet &es, string src);

VertexSet getSrcVertexSet(const EdgeSet &es);
VertexSet getTgtVertexSet(const EdgeSet &es);