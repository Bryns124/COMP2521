
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List insertNewNode(Node curr, List zipped);

// Worst case time complexity of this solution: O(n^3)
List zipList(List l1, int x, List l2, int y) {
    if (l1->first == NULL || l2->first == NULL) {
        return NULL;
    }
    List listZipped = ListNew();
    if (x == 0) {
        while (l2->first != NULL) {
            List listZipped = insertNewNode(l2->first, listZipped);
        }
        return listZipped;
    }
    else if (y == 0) {
        while (l1->first != NULL) {
            List listZipped = insertNewNode(l1->first, listZipped);
        }
        return listZipped;
    }
    for (int i = 0; i <= x; i++) {
        if (l1->first == NULL && l2->first == NULL) {
            break;
        }
        if (listZipped->first == NULL) {
            Node new = newNode(l1->first->value);
            listZipped->first = new;
            listZipped->last = new;
            l1->first = l1->first->next;
        }
        if (i == x) {
            for (int j = 1;  j <= y; j++) {
                if (l1->first != NULL && l2->first == NULL && i == x) {
                    i = 0;
                    break;
                }
                else if (j == y) {
                    Node new = newNode(l2->first->value);
                    listZipped->last->next = new;
                    listZipped->last = new;
                    l2->first = l2->first->next;
                    i = 0;
                    j = 1;
                    break;
                }
                Node new = newNode(l2->first->value);
                listZipped->last->next = new;
                listZipped->last = new;
                l2->first = l2->first->next;
            }
        }
    }

    return listZipped;
}

List insertNewNode(Node curr, List zipped) {
    Node new = newNode(curr->value);
        if (zipped->first == NULL) {
            zipped->first = new;
            zipped->last = new;
            curr = curr->next;
        }
        zipped->last->next = new;
        zipped->last = new;
        curr = curr->next;
    return zipped;
}