#include <unordered_set>
#include <unordered_map>
#include <string>

#include "graph.h"

using std::string;
using std::hash;


void Graph::addEdge(const Edge &e)
{
	SrcToEdgeSetMap[e.src].insert(e);
	TgtToEdgeSetMap[e.tgt].insert(e);
	DescToEdgeSetMap[e.pred].insert(e);
}
void Graph::removeEdge(const Edge &e)
{
	SrcToEdgeSetMap[e.src].erase(e);
	TgtToEdgeSetMap[e.tgt].erase(e);
	DescToEdgeSetMap[e.pred].erase(e);
}
EdgeSet& Graph::hasSrc(string src)
{
	return SrcToEdgeSetMap[src];
}
EdgeSet& Graph::hasTgt(string tgt)
{
	return TgtToEdgeSetMap[tgt];
}

EdgeSet Graph::hasSrcVertexSet(VertexSet v)
{
	EdgeSet ret{};
	for (string s : v) {
		auto es = SrcToEdgeSetMap[s];
		ret.insert(es.begin(),es.end());
	}
	return std::move(ret);
}

EdgeSet Graph::hasTgtVertexSet(VertexSet v)
{
	EdgeSet ret{};
	for (string s : v) {
		auto es = TgtToEdgeSetMap[s];
		ret.insert(es.begin(), es.end());
	}
	return std::move(ret);
}

EdgeSet& Graph::hasPred(string desc)
{
	return DescToEdgeSetMap[desc];
}
EdgeSet Graph::hasV(string v)
{
	EdgeSet res{};
	auto SrcEdgeSet = hasSrc(v);
	auto TgtEdgeSet = hasTgt(v);
	res.insert(SrcEdgeSet.begin(), SrcEdgeSet.end());
	res.insert(TgtEdgeSet.begin(), TgtEdgeSet.end());
	return res;
}

Graph initExpGraph();

int main()
{
	Graph g = initExpGraph();
	auto es = g.hasV("Bllizard");
	auto es2 = hasPred(es, "isCreatedBy");
	VertexSet v1 = getSrcVertexSet(es2);
	auto es3 = hasPred(g.hasTgtVertexSet(v1),"enjoys");
	auto v2 = getSrcVertexSet(es3);
	return 0;
}



Graph initExpGraph()
{
	Graph g;
	g.addEdge({ "hgz","is","naive" });
	g.addEdge({ "hgz","likes","programming" });
	g.addEdge({ "Dijkstra","likes","programming" });
	g.addEdge({ "Dijkstra","is","Cool!!" });
	g.addEdge({ "Bllizard","is","Cool!!" });
	g.addEdge({ "hgz","enjoys","Overwatch" });
	g.addEdge({ "Overwatch","isCreatedBy","Bllizard" });
	g.addEdge({ "WoW","isCreatedBy","Bllizard" });
	g.addEdge({ "StarCraft","isCreatedBy","Bllizard" });
	g.addEdge({ "HoS","isCreatedBy","Bllizard" });
	return std::move(g);
}


EdgeSet hasPred(const EdgeSet &es, string pred)
{
	EdgeSet ret{};
	for (Edge e : es) {
		if (e.pred == pred) {
			ret.insert(e);
		}
	}
	return std::move(ret);
}

EdgeSet hasTgt(const EdgeSet &es, string tgt)
{
	EdgeSet ret{};
	for (Edge e : es) {
		if (e.tgt == tgt) {
			ret.insert(e);
		}
	}
	return std::move(ret);
}


EdgeSet hasSrc(const EdgeSet &es, string src)
{
	EdgeSet ret{};
	for (Edge e : es) {
		if (e.src == src) {
			ret.insert(e);
		}
	}
	return std::move(ret);
}

VertexSet getSrcVertexSet(const EdgeSet &es)
{
	VertexSet ret{};
	for (Edge e : es) {
		ret.insert(e.src);
	}
	return std::move(ret);
}

VertexSet getTgtVertexSet(const EdgeSet &es)
{
	VertexSet ret{};
	for (Edge e : es) {
		ret.insert(e.tgt);
	}
	return std::move(ret);
}

