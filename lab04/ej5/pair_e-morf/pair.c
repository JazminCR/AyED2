#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pair.h"

struct s_pair_t {
    elem fst;
    elem snd;
};

pair_t pair_new(elem x, elem y) {
    pair_t p = malloc(sizeof(pair_t));
    p->fst = x;
    p->snd = y;
    assert(p->fst == x && p->snd == y);
    return p;
}

elem pair_first(pair_t p) {
    elem x = p->fst;
    return x;
}

elem pair_second(pair_t p) {
    elem y = p->snd;
    return y;
}

pair_t pair_swapped(pair_t p) {
    pair_t s;
    s = malloc(sizeof(pair_t));
    s->fst = p->snd;
    s->snd = p->fst;
    assert(p->fst == s->snd && p->snd == s->fst);
    return s;
}

pair_t pair_destroy(pair_t p) {
    free(p);
    p = NULL;
    return p;
}
