#undef NDEBUG
#include <stdio.h>
#include <assert.h>

#include "hashmap.h"

void t1()
{
    hmap h;
    int k, v;

    hmap_init(&h, sizeof(k), sizeof(v), 2);

    k = 1, v = 2;
    hmap_insert(&h, &k, &v);
    k = 2, v = 4;
    hmap_insert(&h, &k, &v);
    k = 3, v = 6;
    hmap_insert(&h, &k, &v);

    for(hmap_iter i = hmap_iter_begin(&h);
        hmap_iter_neq(i, hmap_iter_end(&h));
        i = hmap_iter_next(i))
    {
        k = *(int*)hmap_iter_key(i);
        v = *(int*)hmap_iter_val(i);
        assert(k * 2 == v);
    }

    k = 1;
    assert(*(int*)hmap_get(&h, &k) == 2);
    k = 2;
    assert(*(int*)hmap_get(&h, &k) == 4);
    k = 3;
    assert(*(int*)hmap_get(&h, &k) == 6);

    hmap_destroy(&h);
}

void t2()
{
    lhmap h;
    int k, v;

    lhmap_init(&h, sizeof(k), sizeof(v), 2);

    k = 1, v = 2;
    lhmap_insert(&h, lhmap_iter_end(&h), &k, &v);
    k = 2, v = 4;
    lhmap_insert(&h, lhmap_iter_end(&h), &k, &v);
    k = 3, v = 6;
    lhmap_insert(&h, lhmap_iter_end(&h), &k, &v);

    for(lhmap_iter i = lhmap_iter_begin(&h);
        lhmap_iter_neq(i, lhmap_iter_end(&h));
        i = lhmap_iter_next(i))
    {
        k = *(int*)lhmap_iter_key(i);
        v = *(int*)lhmap_iter_val(i);
        assert(k * 2 == v);
    }

    k = 1;
    assert(*(int*)lhmap_get(&h, &k) == 2);
    k = 2;
    assert(*(int*)lhmap_get(&h, &k) == 4);
    k = 3;
    assert(*(int*)lhmap_get(&h, &k) == 6);

    lhmap_destroy(&h);
}

int main()
{
    t1();
    t2();
}
