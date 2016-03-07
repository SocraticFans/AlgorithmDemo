#ifndef _BASE_CLASS_H_
#define _BASE_CLASS_H_

#include <stdlib.h>
#include <stdint.h>

#include <vector>
#include <list>
#include <map>

using namespace std;

class Map;
class Node {
public:
	friend class Map;
	Node(int x, int y, bool walk = false): m_x(x), m_y(y), m_g(0), m_h(0),
										   m_walkable(walk), m_isInOpen(false), m_isInClose(false),
										   m_parent(NULL) {}

	void reset() {
		m_g = 0;
		m_h = 0;
		m_isInOpen = false;
		m_isInClose = false;
		m_parent = NULL;
	}

	bool operator == (const Node& rhs) {
		if (rhs.m_x == m_x && rhs.m_y == m_y) {
			return true;
		}
		return false;
	}
	
	bool canWalk() {return m_walkable;}

	bool isOpen() const {return m_isInOpen;}
	void setOpen(bool open) {m_isInOpen = open;}

	bool isClose() {return m_isInClose;}
	void setClose(bool close) {m_isInClose = close;}

	Node* getParent() {return m_parent;}
	void setParent(Node* parent) {m_parent = parent;}


	int getG() {return m_g;}
	int calcuG(Node* node);

	int getH() {return m_h;}
	int calcuH(Node* node);

	int getF() const {return m_g + m_h;}

	void show() {
		printf("(%d, %d)", m_x, m_y);
	}

		
private:
	int m_x;
	int m_y;
	int m_g;
	int m_h;
	bool m_walkable;
	bool m_isInOpen;
	bool m_isInClose;
	Node* m_parent;
};

class OpenTable {
public:
	typedef multimap<int, Node*> Table_T;
	bool empty() {return m_nodes.empty();}

	Node* pop_first() {
		Table_T::iterator it = m_nodes.begin();
		Node* node = it->second;
		m_nodes.erase(it);
		return node;
	}

	void insert(Node* node) {
		m_nodes.insert(make_pair(node->getF(), node));
	}

	void update(Node* node, int oldF) {
		pair<Table_T::iterator,  Table_T::iterator> ret = m_nodes.equal_range(oldF);
		for (Table_T::iterator it = ret.first; it != ret.second; ++it) {
			if (*it->second == *node) {
				m_nodes.erase(it);
				break;
			}
		}
		insert(node);
	}

	Table_T m_nodes;
};

class Map {
public:
	Map(int width, int height, const int* nodes);

	bool runAStar(const Node& from, const Node& to, list<Node*>& path);
	void clearState();

	Node* getNode(int x, int y);
	Node* getNode(const Node& node);
	void getNeighbours(Node* node, vector<Node*>& neighbours);

private:
	Map(const Map&);
	const Map& operator= (const Map& rhs);

private:
	int m_width;
	int m_height;
	vector<Node> m_nodes;
};

#endif
