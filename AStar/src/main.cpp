#include <stdio.h>

#include "BaseClass.h"

#include <time.h>
#include <sys/time.h>

static int mapData[][6] = { {0, 0, 0, 1, 0, 0},
							{0, 0, 0, 1, 0, 0},
							{0, 0, 0, 1, 0, 0},
							{0, 0, 0, 0, 0, 0},
							{0, 0, 0, 1, 0, 0},
							{0, 0, 0, 1, 0, 0},
						};
const uint32_t MICROSEC_PER_SEC = 1000000;
int64_t getNowUs() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t)tv.tv_sec * MICROSEC_PER_SEC + (uint64_t)tv.tv_usec;
}

int main(void) {
	printf("Hello AStar!\n");

	Map m(6, 6, (int*)mapData);
	list<Node*> path;
	int64_t s = getNowUs();
	for (int i = 0; i < 10000; ++i) {
		m.runAStar(Node(0, 0), Node(5, 0), path);
	}
	int64_t e = getNowUs();
	printf("time %ld\n", e - s);

	printf("path length %lu\n", path.size());
	for (Node* n:path) {
		n->show();
	}
	printf("\n");

	return 0;
}
