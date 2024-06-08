#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pair.h"

pair_t pair_new(int x, int y) {
    pair_t p;
    p.values[0] = x;
    p.values[1] = y;
    assert(p.values[0] == x && p.values[1] == y);
    return p;
}

int pair_first(pair_t p) {
    return p.values[0];
}

int pair_second(pair_t p) {
    return p.values[1];
}

pair_t pair_swapped(pair_t p) {
    pair_t s;
    s.values[0] = p.values[1];
    s.values[1] = p.values[0];
    assert(p.values[0] == s.values[1] && p.values[1] == s.values[0]);
    return s;
}

pair_t pair_destroy(pair_t p) {
    p.values[0] = 0;
    p.values[1] = 0;
    return p;
}
