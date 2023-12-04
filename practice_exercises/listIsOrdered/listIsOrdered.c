
#include "list.h"

bool listAscending(Node n);
bool listDescending(Node n);

bool listIsOrdered(List l) {
	if (listAscending(l->head) || listDescending(l->head)) {
		return true;
	}
	return false;
}

bool listAscending(Node n) {
	if (n == NULL || n->next == NULL) {
		return true;
	} else {
		if (n->value <= n->next->value && listAscending(n->next)) {
			return true;
		}
	}
	return false;
}

bool listDescending(Node n) {
	if (n == NULL || n->next == NULL) {
		return true;
	} else {
		
		if (n->value >= n->next->value && listDescending(n->next)) {
			return true;
		}
	}
	return false;
}