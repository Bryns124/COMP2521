#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// Worst case time complexity of this solution: O(...)
List zipList(List l1, int x, List l2, int y) {
    // TODO
    if (l1->first == NULL || l2->first == NULL) {
        return NULL;
    }
    List zippedList = ListNew();
    Node curr1 = l1->first;
    Node curr2 = l2->first;
    if (x == 0) {
        while (curr2 != NULL) {
            Node new = newNode(curr2->value);
            if (zippedList->first == NULL) {
                zippedList->first = new;
                zippedList->last = new;
                curr2 = curr2->next;
            }
            zippedList->last->next = new;
            zippedList->last = new;
            curr2 = curr2->next;
        }
        return zippedList;
    }
    if (y == 0) {
        while (curr1 != NULL) {
            Node new = newNode(curr1->value);
            if (zippedList->first == NULL) {
                zippedList->first = new;
                zippedList->last = new;
                curr1 = curr1->next;
            }
            zippedList->last->next = new;
            zippedList->last = new;
            curr1 = curr1->next;
        }
        return zippedList;
    }
    for (int i = 0; i <= x; i++) {
        if (curr1 == NULL && curr2 == NULL) {
            break;
        }
        if (zippedList->first == NULL) {
            Node new = newNode(curr1->value);
            zippedList->first = new;
            zippedList->last = new;
            curr1 = curr1->next;
            continue;
        }
        if (i == x) {
            for (int j = 1;  j <= y; j++) {
                if (curr1 != NULL && curr2 == NULL && i == x) {
                    i = 0;
                    break;
                }
                if (curr2 == NULL) {
                    break;
                }
                if (j == y) {
                    Node new = newNode(curr2->value);
                    zippedList->last->next = new;
                    zippedList->last = new;
                    curr2 = curr2->next;
                    i = 0;
                    j = 1;
                    break;
                }
                Node new = newNode(curr2->value);
                zippedList->last->next = new;
                zippedList->last = new;
                curr2 = curr2->next;
            }
        }
        if (curr1 != NULL) {
            Node new = newNode(curr1->value);
            zippedList->last->next = new;
            zippedList->last = new;
            curr1 = curr1->next;
        }
    }

    return zippedList;
}