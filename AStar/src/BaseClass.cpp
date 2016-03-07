#include "BaseClass.h"

#include <math.h>


int Node::calcuG(Node* node) {
	if (node->m_x == m_x || node->m_y == m_y) {
		m_g = node->m_g + 10;
	} else {
		m_g = node->m_g + 14;
	}
	return m_g;
}

int Node::calcuH(Node* node) {
	m_h = (abs(node->m_x - m_x) + abs(node->m_y - m_y)) * 10;
	return m_h;
}

Map::Map(int width, int height, const int* nodes)
	:m_width(width),
	 m_height(height) {

	m_nodes.reserve(width * height);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int walk = nodes[x + y * width];
			m_nodes.push_back(Node(x, y, walk == 0));
		}
	}
}

Node* Map::getNode(int x, int y) {
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
		return NULL;
	}
	return &m_nodes[x + y * m_height];
}

Node* Map::getNode(const Node& node) {
	return getNode(node.m_x, node.m_y);
}

void Map::getNeighbours(Node* node, vector<Node*>& neighbours) {
	static int n[8][2] = {{-1, -1}, {0, -1}, {1, -1},
						 {-1, 0}, 			{1, 0},
						 {-1, 1},  {0, 1},  {1, 1}
						};

	neighbours.clear();
	for (int i = 0; i < 8; ++i) {
		Node* neigh = getNode(node->m_x + n[i][0], node->m_y + n[i][1]);
		if (neigh != NULL && neigh->canWalk()) {
			neighbours.push_back(neigh);
		}
	}
}

bool Map::runAStar(const Node& from, const Node& to, list<Node*>& path) {
	path.clear();
	OpenTable openList;
	Node* fromNode = getNode(from);
	Node* targetNode = getNode(to);
	openList.insert(fromNode);

	Node* curNode = fromNode;
	vector<Node*> neighbours;

	int num = 0;
	while (!openList.empty()) {
		curNode = openList.pop_first();
		curNode->setOpen(false);
		curNode->setClose(true);

		if (curNode == targetNode) {
			break;
		}
		getNeighbours(curNode, neighbours);
		for (Node* node:neighbours) {
			Node copyNode = *node;
			if (copyNode.isClose()) {
				continue;
			} else if (!copyNode.isOpen()) {
				node->setParent(curNode);
				node->setOpen(true);
				openList.insert(node);
			} else {
				copyNode.calcuG(curNode);
				copyNode.calcuH(targetNode);
				//经过这个点F值比之前更小
				int oldF = node->getF();
				if (copyNode.getF() < oldF) {
					copyNode.setParent(curNode);
					(*node) = copyNode;
					openList.update(node, oldF);
				}
			}
			num++;
		}
		neighbours.clear();
	}

	//printf("loop num %d\n", num);

	bool found = false;
	if (curNode == targetNode) {
		while (curNode != fromNode) {
			path.push_front(curNode);
			curNode = curNode->getParent();
		}
		path.push_front(fromNode);
		found = true;
	}

	clearState();
	return found;
}

void Map::clearState() {
	for (Node& node : m_nodes) {
		node.reset();
	}
}
