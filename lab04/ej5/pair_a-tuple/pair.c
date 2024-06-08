#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pair.h"

pair_t pair_new(int x, int y) {
    pair_t p;
    p.fst = x;
    p.snd = y;
    assert(p.fst == x && p.snd == y);
    return p;
}

int pair_first(pair_t p) {
    return p.fst;
}

int pair_second(pair_t p) {
    return p.snd;
}

pair_t pair_swapped(pair_t p) {
    pair_t s;
    s.fst = p.snd;
    s.snd = p.fst;
    assert(p.fst == s.snd && p.snd == s.fst);
    return s;
}

pair_t pair_destroy(pair_t p) {
    p.fst = 0;
    p.snd = 0;
    return p;
}
