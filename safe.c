#include <stdio.h>

#define RING_SIZE 16
#define COLUMN_TARGET 40
#define RESOLVE(choice, outer_offset, outers, inner_offset, inners) (choice ? inners[(inner_offset + column) % RING_SIZE] : outers[(outer_offset + column) % RING_SIZE])

/*
 * SafeCracker 40 Puzzle solver
 *
 * Flicks through combinations of rings looking for orientations where all columns sum to 40.
 *
 * - the bottommost ring is labeled a; topmost d
 * - ring a is considered stationary while the other three may turn
 * - cell values -1 are holes and *should* not be considered valid
 *
 */
int main() {

    // no a_offset since it's conceptually stationary.
    int a_outers[RING_SIZE] = { 11, 27, 10, 19, 10, 13, 10, 2,  15, 23, 19, 3,  2,  3,  27, 20 };
    int a_inners[RING_SIZE] = { 9,  7,  3,  12, 24, 10, 9,  22, 9,  5,  10, 5,  1,  24, 2,  10 };

    int b_offset;
    int b_outers[RING_SIZE] = { 10, -1, 15, -1, 6,  -1, 9,  -1, 16, -1, 17, -1, 2,  -1, 2, -1  };
    int b_inners[RING_SIZE] = { 8,  3,  6,  15, 22, 6,  1,  1,  11, 27, 14, 5,  5,  7,  8,  24 };

    int c_offset;
    int c_outers[RING_SIZE] = { 10, -1, 2,  -1, 22, -1, 2,  -1, 17, -1, 15, -1, 14, -1, 5, -1  };
    int c_inners[RING_SIZE] = { 1,  6,  10, 6,  10, 2,  6,  10, 4,  1,  5,  5,  4,  8,  6,  3  };

    int d_offset;
    int d_outers[RING_SIZE] = { 13, -1, 3, -1,  3, -1,  6, -1,  10, -1, 10, -1, 10, -1, 6, -1  };

    int b_to_a;
    int c_to_b;
    int d_to_c;
    int column;
    int sum;

    for (b_offset = 0; b_offset < RING_SIZE; b_offset++) {
        for (c_offset = 0; c_offset < RING_SIZE; c_offset++) {
            for (d_offset = 0; d_offset < RING_SIZE; d_offset++) {

                // pick the parity of the holes
                b_to_a = b_offset % 2 == 1;
                c_to_b = c_offset % 2 == 1;
                d_to_c = d_offset % 2 == 1;

                for (column = 0; column < RING_SIZE; column++) {

                    sum =
                        a_outers[column] +
                        RESOLVE(b_to_a, b_offset, b_outers, 0, a_inners) +
                        RESOLVE(c_to_b, c_offset, c_outers, b_offset, b_inners) +
                        RESOLVE(d_to_c, d_offset, d_outers, c_offset, c_inners);

                    // break if any column doesn't work
                    if (sum != COLUMN_TARGET) {
                        goto backtrack;
                    }

                    // toggle between holes and teeth
                    b_to_a = !b_to_a;
                    c_to_b = !c_to_b;
                    d_to_c = !d_to_c;
                }
                printf("<%d, %d, %d>\n", b_offset, c_offset, d_offset);
backtrack: ;
            }
        }
    }
}

