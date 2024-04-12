#undef NDEBUG
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "hashmap.h"

typedef unsigned int uint;

const uint q = 2166136261;
const uint p = 16777619;

static void header()
{
    printf("%14s %10s %10s %10s %12s %10s\n",
        "benchmark", "loop", "count", "runtime(s)", "time(ns)", "insert/sec");
    printf("%14s %10s %10s %10s %12s %10s\n",
        "--------------",  "----------", "----------", "----------",
        "------------", "----------");
}

static size_t hash_fn(void *h, void *key)
{
    return *(uint*)key;
}

static int compare_fn(void *h, void *key1, void *key2)
{
    return *(uint*)key1 == *(uint*)key2;
}

static uint bench_hmap(uint loop, uint count, uint print)
{
    uint seq, collisions;
    clock_t wstart, wend, rstart, rend;
    double s1, s2;
    hmap h;

    hmap_init_ex(&h, NULL, sizeof(uint), sizeof(uint), 2,
        (hmap_hash_fn)hash_fn, (hmap_compare_fn)compare_fn);

    wstart = clock();
    for (uint j = 0; j < loop; j++) {
        seq = q;
        for (uint i = 0; i < count; i++) {
            seq = seq * p + i;
            hmap_insert(&h, &seq, &i);
        }
    }
    wend = clock();

    rstart = clock();
    for (uint j = 0; j < loop; j++) {
        seq = q;
        collisions = 0;
        for (uint i = 0; i < count; i++) {
            seq = seq * p + i;
            uint *ip = (uint*)hmap_get(&h, &seq);
            collisions += (*ip != i);
        }
    }
    rend = clock();

    hmap_destroy(&h);

    if (!print) return collisions;

    s1 = (1e9 * (wend - wstart)) / ((double)CLOCKS_PER_SEC);
    s2 = (1e9 * (rend - rstart)) / ((double)CLOCKS_PER_SEC);

    uint sum = count * loop;

    printf("%14s %10u %10u %10.2f %10.2fns %10zu\n",
        "hmap_insert", loop, count, s1/1e9, s1/sum, (size_t)(1e9 * sum/s1));
    printf("%14s %10u %10u %10.2f %10.2fns %10zu\n",
        "hmap_lookup", loop, count, s2/1e9, s2/sum, (size_t)(1e9 * sum/s2));

    return collisions;
}

static uint bench_lhmap(uint loop, uint count, uint print)
{
    uint seq, collisions;
    clock_t wstart, wend, rstart, rend;
    double s1, s2;
    lhmap h;

    lhmap_init_ex(&h, NULL, sizeof(uint), sizeof(uint), 2,
        (lhmap_hash_fn)hash_fn, (lhmap_compare_fn)compare_fn);

    wstart = clock();
    for (uint j = 0; j < loop; j++) {
        seq = q;
        for (uint i = 0; i < count; i++) {
            seq = seq * p + i;
            lhmap_insert(&h, lhmap_iter_end(&h), &seq, &i);
        }
    }
    wend = clock();

    rstart = clock();
    for (uint j = 0; j < loop; j++) {
        seq = q;
        collisions = 0;
        for (uint i = 0; i < count; i++) {
            seq = seq * p + i;
            uint *ip = (uint*)lhmap_get(&h, &seq);
            collisions += (*ip != i);
        }
    }
    rend = clock();

    lhmap_destroy(&h);

    if (!print) return collisions;

    s1 = (1e9 * (wend - wstart)) / ((double)CLOCKS_PER_SEC);
    s2 = (1e9 * (rend - rstart)) / ((double)CLOCKS_PER_SEC);

    uint sum = count * loop;

    printf("%14s %10u %10u %10.2f %10.2fns %10zu\n",
        "lhmap_insert", loop, count, s1/1e9, s1/sum, (size_t)(1e9 * sum/s1));
    printf("%14s %10u %10u %10.2f %10.2fns %10zu\n",
        "lhmap_lookup", loop, count, s2/1e9, s2/sum, (size_t)(1e9 * sum/s2));

    return collisions;
}

void bench(uint loop, uint count)
{
    uint k1 = bench_hmap(loop, count, 0), k2 = bench_hmap(loop, count, 1);
    uint j1 = bench_lhmap(loop, count, 0), j2 = bench_lhmap(loop, count, 1);
    assert(k1 == k2 && j1 == j2 && k1 == j1);
}

int main(int argc, const char **argv)
{
    header();
    bench(100000, 100);
    bench(10000, 1000);
    bench(1000, 10000);
    bench(100, 100000);
    bench(10, 1000000);
}
