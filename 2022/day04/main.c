#include <ctype.h>
#include <stdbool.h>
#include <stdio.h> 
#include <string.h>
#include <assert.h>


#define PART 1
#define DEBUG false

#define LINE_LENGTH 32

typedef struct {
    int begin;
    int end;
} Range;

bool range_is_fully_contained(Range *range1, Range *range2) {
    Range *smaller_beginning_range = NULL;
    Range *other_range = NULL;
    // find which range has the smaller beginning number
    if (range1->begin < range2->begin) {
        smaller_beginning_range = range1;
        other_range = range2;
    } else {
        smaller_beginning_range = range2;
        other_range = range1;
    }

    // in the case that either the beginning or ending points 
    // of both ranges are equal, one of the ranges MUST be 
    // fully contained in the other, so return true
    if (smaller_beginning_range->begin == other_range->begin) {
        return true;
    } else if (smaller_beginning_range->end == other_range->end) {
        return true;
    }

    // check the normal case where the beginnings or endings are not equal
    return (bool)(smaller_beginning_range->end >= other_range->end); 
}


bool ranges_overlap_at_all(Range *range1, Range *range2) {
    Range *smaller_beginning_range = NULL;
    Range *other_range = NULL;
    // find which range has the smaller beginning number
    if (range1->begin < range2->begin) {
        smaller_beginning_range = range1;
        other_range = range2;
    } else {
        smaller_beginning_range = range2;
        other_range = range1;
    }

    // in the case that either the beginning or ending points 
    // of both ranges are equal, one of the ranges MUST be 
    // fully contained in the other, so return true
    if (smaller_beginning_range->begin == other_range->begin) {
        return true;
    } else if (smaller_beginning_range->end == other_range->end) {
        return true;
    }

    // check the normal case where the beginnings or endings are not equal
    // and there is just SOME of the first range overlapping the 
    // other range
    return (bool)(smaller_beginning_range->end >= other_range->begin);
}


void convert_str_to_ranges(const char *str, Range *range1, Range *range2) {
    size_t str_len = strnlen(str, LINE_LENGTH);
    Range *current_range = range1;
    int current_number = 0;
    bool looking_for_beginning_number = true;
    for (size_t i = 0; i < str_len; ++i) {
        if (!isdigit(str[i])) {
            // have the full current number, 
            // now need to assign it
            if (looking_for_beginning_number) {
                current_range->begin = current_number;
                looking_for_beginning_number = false;
            } else {
                current_range->end = current_number;
                looking_for_beginning_number = true;
                if (current_range == range1)
                    current_range = range2;
                else 
                    return;
            }

            current_number = 0;
            continue;

        } else if (i == str_len - 1) {
            // take care of the final line as it 
            // doesn't end in \n
            current_number *= 10;
            current_number += str[i] - '0';
            range2->end = current_number;
            return;
        }
        // keep recording the current number
        current_number *= 10;
        current_number += str[i] - '0';
    }
}


void test_range_is_fully_contained(void) {
    Range range1 = {0};
    Range range2 = {0};

    printf("\ntesting range_is_fully_contained...\n");

    printf(" 0 \n");
    range1.begin = 0; range1.end = 4;
    range2.begin = 0; range2.end = 4;
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 1 \n");
    range1.begin = 1; range1.end = 4;
    range2.begin = 0; range2.end = 4;
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 2 \n");
    range1.begin = 4; range1.end = 4;
    range2.begin = 0; range2.end = 4;
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 3 \n");
    range1.begin = 2; range1.end = 4;
    range2.begin = 0; range2.end = 2;
    assert(false == range_is_fully_contained(&range1, &range2));

    printf(" 4 \n");
    range1.begin = 0; range1.end = 4;
    range2.begin = 4; range2.end = 4;
    assert(true == range_is_fully_contained(&range1, &range2));

    printf("done testing\n\n");
}


void test_ranges_overlap_at_all(void) {
    Range range1 = {0};
    Range range2 = {0};

    printf("\ntesting ranges_overlap_at_all...\n");

    printf(" 0 \n");
    range1.begin = 0; range1.end = 4;
    range2.begin = 1; range2.end = 2;
    assert(true == ranges_overlap_at_all(&range1, &range2));

    printf(" 1 \n");
    range1.begin = 0; range1.end = 4;
    range2.begin = 5; range2.end = 6;
    assert(false == ranges_overlap_at_all(&range1, &range2));

    printf(" 2 \n");
    range1.begin = 0; range1.end = 4;
    range2.begin = 4; range2.end = 7;
    assert(true == ranges_overlap_at_all(&range1, &range2));

    printf(" 3 \n");
    range1.begin = 3; range1.end = 4;
    range2.begin = 1; range2.end = 3;
    assert(true == ranges_overlap_at_all(&range1, &range2));

    printf("done testing\n\n");
}


void test_convert_str_to_ranges(void) {
    Range range1 = {0};
    Range range2 = {0};

    printf("\ntesting convert_str_to_ranges...\n");

    printf(" 0 \n");
    convert_str_to_ranges("3-96,3-95\n", &range1, &range2);
    assert(range1.begin == 3 && range1.end == 96);
    assert(range2.begin == 3 && range2.end == 95);
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 1 \n");
    convert_str_to_ranges("25-96,40-95\n", &range1, &range2);
    assert(range1.begin == 25 && range1.end == 96);
    assert(range2.begin == 40 && range2.end == 95);
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 2 \n");
    convert_str_to_ranges("95-95,3-96\n", &range1, &range2);
    assert(range1.begin == 95 && range1.end == 95);
    assert(range2.begin == 3 && range2.end == 96);
    assert(true == range_is_fully_contained(&range1, &range2));

    printf(" 3 \n");
    convert_str_to_ranges("47-65,63-66\n", &range1, &range2);
    assert(range1.begin == 47 && range1.end == 65);
    assert(range2.begin == 63 && range2.end == 66);
    assert(false == range_is_fully_contained(&range1, &range2));

    printf(" 4 \n");
    convert_str_to_ranges("45-53,39-45\n", &range1, &range2);
    assert(range1.begin == 45 && range1.end == 53);
    assert(range2.begin == 39 && range2.end == 45);
    assert(false == range_is_fully_contained(&range1, &range2));

    printf(" 5 \n");
    convert_str_to_ranges("5-84,6-79", &range1, &range2);
    assert(range1.begin == 5 && range1.end == 84);
    assert(range2.begin == 6 && range2.end == 79);
    assert(true == range_is_fully_contained(&range1, &range2));

    printf("done testing\n\n");
}


int main(void) {
    Range range1 = {0};
    Range range2 = {0};
    char buf[LINE_LENGTH];

#if(DEBUG == true)
    test_range_is_fully_contained();
    test_ranges_overlap_at_all();
    test_convert_str_to_ranges();
#endif

    FILE *input = fopen("input.txt", "r");
    size_t num_overlaps = 0;

    while(fgets(buf, LINE_LENGTH, input)) {
        convert_str_to_ranges(buf, &range1, &range2);

#if(PART == 1)
        num_overlaps += (size_t)(true == range_is_fully_contained(&range1, &range2));
#else
        num_overlaps += (size_t)(true == ranges_overlap_at_all(&range1, &range2));
#endif

    }

    fclose(input);

    printf("number of overlaps: %zu\n", num_overlaps);
    
    return 0;
}
