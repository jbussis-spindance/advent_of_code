#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

size_t sum_top_three(size_t *buf) {
    return buf[0] + buf[1] + buf[2];
}

int find_index_to_replace(size_t *buf, size_t value) {
    for (int i = 0; i < 3; ++i) {
        if (value >= buf[i])
            return i;
    }
    return -1;
}

void insert_into_list(size_t *buf, size_t value, int index_to_replace) {
    switch (index_to_replace) {
        case 0:
            buf[2] = buf[1];
            buf[1] = buf[0];
            buf[0] = value;
            break;
        case 1:
            buf[2] = buf[1];
            buf[1] = value;
            break;
        case 2:
            buf[2] = value;
            break;
        default: 
            return;
    }
}

int main(void) {
    char buf[BUFFER_SIZE];
    size_t top_three[3] = {0};
    size_t current_count = 0;
    FILE *input = fopen("input.txt", "r");

    while(fgets(buf, BUFFER_SIZE, input)) {
        if (buf[0] == '\n') {
            int index_to_replace = find_index_to_replace(top_three, current_count);
            if (index_to_replace == -1) {
                current_count = 0;
                continue;
            }
            
            insert_into_list(top_three, current_count, index_to_replace);
            current_count = 0;
        }

        current_count += atoi(buf);
    }

    fclose(input);

    printf("sum of larget 3: %zu\n", sum_top_three(top_three));
    printf("top three: [%zu] [%zu] [%zu]\n", top_three[0], top_three[1], top_three[2]);
    return 0;
}
