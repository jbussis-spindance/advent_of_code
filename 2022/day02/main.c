#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PART 2

#define LINE_LEN        8

#define ROCK_POINTS     1
#define PAPER_POINTS    2
#define SCISSORS_POINTS 3
#define WIN_POINTS      6
#define DRAW_POINTS     3
#define LOSE_POINTS     0

#define OPP_ROCK        'A'
#define OPP_PAPER       'B'
#define OPP_SCISSORS    'C'
#define ROCK            'X'
#define PAPER           'Y'
#define SCISSORS        'Z'
#define NEED_WIN        'Z'
#define NEED_DRAW       'Y'
#define NEED_LOSE       'X'

#define WIN_AGAINST_ROCK_POINTS         WIN_POINTS + PAPER_POINTS 
#define WIN_AGAINST_PAPER_POINTS        WIN_POINTS + SCISSORS_POINTS
#define WIN_AGAINST_SCISSORS_POINTS     WIN_POINTS + ROCK_POINTS

#define DRAW_AGAINST_ROCK_POINTS        DRAW_POINTS + ROCK_POINTS
#define DRAW_AGAINST_PAPER_POINTS       DRAW_POINTS + PAPER_POINTS
#define DRAW_AGAINST_SCISSORS_POINTS    DRAW_POINTS + SCISSORS_POINTS

#define LOSE_AGAINST_ROCK_POINTS        LOSE_POINTS + SCISSORS_POINTS
#define LOSE_AGAINST_PAPER_POINTS       LOSE_POINTS + ROCK_POINTS
#define LOSE_AGAINST_SCISSORS_POINTS    LOSE_POINTS + PAPER_POINTS


size_t get_round_score(const char *round) {
    assert(round[2] == ROCK || round[2] == PAPER || round[2] == SCISSORS);
    switch (round[0]) {
        case OPP_ROCK:
            return  (size_t)(round[2] == ROCK) * (ROCK_POINTS + DRAW_POINTS) +
                    (size_t)(round[2] == PAPER) * (PAPER_POINTS + WIN_POINTS) +
                    (size_t)(round[2] == SCISSORS) * (SCISSORS_POINTS + LOSE_POINTS);
            break;
        case OPP_PAPER:
            return  (size_t)(round[2] == ROCK) * (ROCK_POINTS + LOSE_POINTS) +
                    (size_t)(round[2] == PAPER) * (PAPER_POINTS + DRAW_POINTS) +
                    (size_t)(round[2] == SCISSORS) * (SCISSORS_POINTS + WIN_POINTS);
            break;
        case OPP_SCISSORS:
            return  (size_t)(round[2] == ROCK) * (ROCK_POINTS + WIN_POINTS) +
                    (size_t)(round[2] == PAPER) * (PAPER_POINTS + LOSE_POINTS) +
                    (size_t)(round[2] == SCISSORS) * (SCISSORS_POINTS + DRAW_POINTS);
            break;
        default:
            assert(0 && "ERROR: Incorrect input!");
            return 0;
    }
}

size_t get_round_score_part_2(const char *round) {
    assert(round[2] == NEED_WIN || round[2] == NEED_DRAW || round[2] == NEED_LOSE);
    switch (round[0]) {
        case OPP_ROCK:
            return  (size_t)(round[2] == NEED_WIN) * (WIN_AGAINST_ROCK_POINTS) + 
                    (size_t)(round[2] == NEED_DRAW) * (DRAW_AGAINST_ROCK_POINTS) + 
                    (size_t)(round[2] == NEED_LOSE) * (LOSE_AGAINST_ROCK_POINTS);
            break;
        case OPP_PAPER:
            return  (size_t)(round[2] == NEED_WIN) * (WIN_AGAINST_PAPER_POINTS) + 
                    (size_t)(round[2] == NEED_DRAW) * (DRAW_AGAINST_PAPER_POINTS) + 
                    (size_t)(round[2] == NEED_LOSE) * (LOSE_AGAINST_PAPER_POINTS);    
            break;
        case OPP_SCISSORS:
            return  (size_t)(round[2] == NEED_WIN) * (WIN_AGAINST_SCISSORS_POINTS) + 
                    (size_t)(round[2] == NEED_DRAW) * (DRAW_AGAINST_SCISSORS_POINTS) + 
                    (size_t)(round[2] == NEED_LOSE) * (LOSE_AGAINST_SCISSORS_POINTS);
            break;
        default:
            assert(0 && "ERROR: Incorrect input!");
            return 0;
    }
}


int main(void) {
    FILE *input = fopen("input.txt", "r");
    char line[LINE_LEN];
    size_t total_points = 0;

    while (fgets(line, LINE_LEN, input)) {
#if(PART == 1)
        total_points += get_round_score(line);
#else 
        total_points += get_round_score_part_2(line);
#endif
    }

    printf("total score: %zu\n", total_points);

    fclose(input);
    return 0;
}
