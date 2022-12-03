#include <stdio.h>
#include <string.h>
#include <assert.h>

// define which part to run 
// 1 or 2
#define PART 2

#define BUFFER_LEN          128
#define PRIORITY_LIST_LEN   52

static char _first_priority_list[PRIORITY_LIST_LEN];
static char _second_priority_list[PRIORITY_LIST_LEN];
static char _third_priority_list[PRIORITY_LIST_LEN];

void trim_newline(char *str) {
    size_t length = strnlen(str, BUFFER_LEN);
    if (str[length-1] == '\n')
        str[length-1] = 0;
}

void record_value(char *list, char value) {
    int index = 0;
    // map the index to the correct order in the priority list
    if (value >= 'a' && value <= 'z') {
        index = value - 'a';
    } else if (value >= 'A' && value <= 'Z') {
        index = value - 'A' + 26;
    }
    list[index]++;
}

void record_full_rucksack(const char *str, char *list) {
    size_t str_len = strnlen(str, BUFFER_LEN);
    for (size_t i = 0; i < str_len; ++i) {
        record_value(list, str[i]);
    }
}

size_t get_duplicate_priority(const char *str) {
    size_t str_len = strnlen(str, BUFFER_LEN);
    size_t half_len = str_len / 2;

    // do the first half
    for (size_t i = 0; i < half_len; ++i) {
        record_value(_first_priority_list, str[i]);
    }

    // do the second half
    for (size_t i = half_len; i < str_len; ++i) {
        record_value(_second_priority_list, str[i]);
    }

    // check which values are duplicates
    for (size_t i = 0; i < PRIORITY_LIST_LEN; ++i) {
        // find the overlap
        if (_first_priority_list[i] > 0 &&
            _second_priority_list[i] > 0) {
            // the chars are oredered correctly in the 
            // list, but need to add 1 to offset starting at 0
            return i + 1;
        }
    }
    
    return 0;
}

size_t get_badge_priority(void) {
    for (size_t i = 0; i < PRIORITY_LIST_LEN; ++i) {
        // find overlap of all three 
        if (_first_priority_list[i] > 0 &&
            _second_priority_list[i] > 0 &&
            _third_priority_list[i] > 0) {
            // the chars are oredered correctly in the 
            // lists, but need to add 1 to offset starting at 0
            return i + 1;
        }
    }
    return 0;
}

void clear_prority_lists(void) {
    memset(_first_priority_list, 0, PRIORITY_LIST_LEN);
    memset(_second_priority_list, 0, PRIORITY_LIST_LEN);
    memset(_third_priority_list, 0,  PRIORITY_LIST_LEN);
}

int main(void) {
    FILE *input = fopen("input.txt", "r");
    char buf[BUFFER_LEN];
    size_t sum = 0;

#if(PART == 1)
    while(fgets(buf, sizeof(buf), input)) {
        trim_newline(buf);
        sum += get_duplicate_priority(buf);
        clear_prority_lists();
    }
#else
    while(fgets(buf, sizeof(buf), input)) {
        // record the first
        trim_newline(buf);
        record_full_rucksack(buf, _first_priority_list);
        // record the second
        fgets(buf, sizeof(buf), input);
        trim_newline(buf);
        record_full_rucksack(buf, _second_priority_list);
        // record the third
        fgets(buf, sizeof(buf), input);
        trim_newline(buf);
        record_full_rucksack(buf, _third_priority_list);
        // find the overlap
        sum += get_badge_priority();
        clear_prority_lists();
    }
#endif

    printf("sum: %zu\n", sum);

    fclose(input);
    return 0;
}
