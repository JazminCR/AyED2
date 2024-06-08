#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    if (tree == NULL) {
        return true;
    } else {
        bool left_ok = (tree->left == NULL || (elem_less(tree->left->elem, tree->elem) && invrep(tree->left)));
        bool right_ok = (tree->right == NULL || (elem_less(tree->elem, tree->right->elem) && invrep(tree->right)));
        return left_ok && right_ok;
    }
}

abb abb_empty(void) {
    abb tree;
    tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL) {
        tree = malloc(sizeof(struct _s_abb));
        tree-> elem = e;
        tree->right = NULL;
        tree->left = NULL;
    } else {
        if (elem_less(tree->elem, e)) {
            tree->right = abb_add(tree->right, e);
        } else if (elem_less(e, tree->elem)) {
            tree->left = abb_add(tree->left, e);
        } else {
            return tree;
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL) {
        return false;
    } else if (elem_eq(tree->elem, e)) {
        return true;
    } else if (elem_less(e, tree->elem)) {
        return abb_exists(tree->left, e);
    } else {
        return abb_exists(tree->right, e);
    }
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (!abb_is_empty(tree)) {
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (tree == NULL) {
        return NULL;
    } else if (elem_less(e, tree->elem)) {
        tree->left = abb_remove(tree->left, e);
    } else if (elem_less(tree->elem, e)) {
        tree->right = abb_remove(tree->right, e);
    } else {
        if (tree->left == NULL) {
            abb temp = tree->right;
            free(tree);
            tree = temp;
        } else if (tree->right == NULL) {
            abb temp = tree->left;
            free(tree);
            tree = temp;
        } else {
            abb temp = tree->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            tree->elem = temp->elem;
            tree->left = abb_remove(tree->left, temp->elem);
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) {
   abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if(!abb_is_empty(tree)){
        if (abb_is_empty(tree->right)) {
            return tree->elem;
        } else {
            return abb_max(tree->right);   
        }
    }else{
        max_e = INT_MAX;
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if(!abb_is_empty(tree)){
        if (abb_is_empty(tree->left)) {
            return tree->elem;
        } else {
            return abb_min(tree->left);   
        }
    } else {
        min_e = INT_MIN;
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree, abb_ordtype ord) {
    assert(invrep(tree) && (ord==ABB_IN_ORDER  || 
                            ord==ABB_PRE_ORDER ||
                            ord==ABB_POST_ORDER));
  
    if (tree != NULL && ord == ABB_PRE_ORDER) {
        printf("%d ", tree->elem);
        abb_dump(tree->left, ord);
        abb_dump(tree->right, ord);
    }

    if (tree != NULL && ord == ABB_POST_ORDER) {
        abb_dump(tree->left, ord);
        abb_dump(tree->right, ord);
        printf("%d ", tree->elem);
    }

    if (tree != NULL && ord == ABB_IN_ORDER) {
        abb_dump(tree->left, ord);
        printf("%d ", tree->elem);
        abb_dump(tree->right, ord);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_destroy(tree->right);
        abb_destroy(tree->left);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}
