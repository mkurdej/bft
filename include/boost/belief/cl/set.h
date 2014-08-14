inline uint set_intersection(uint set1, uint set2)
{
    return set1 & set2;
}

inline uint set_union(uint set1, uint set2)
{
    return set1 | set2;
}

inline uint set_minus(uint set1, uint set2)
{
    return set1 & (set1 ^ set2);
}

inline uint set_xor(uint set1, uint set2)
{
    return set1 ^ set2;
}

inline bool is_emptyset(uint set1)
{
    return 0 == set1;
}

inline bool is_subset_of(uint set1, uint set2)
{
    return set_intersection(set1, set2) == set1;
}

inline bool is_superset_of(uint set1, uint set2)
{
    return is_subset_of(set2, set1);
}

// Use cl::popcount instead
inline uint count_bits(uint n)
{
    uint c; // c accumulates the total bits set in n
    for (c = 0; n; ++c) {
        n &= n - 1; // clear the least significant bit set
    }
    return c;
}
