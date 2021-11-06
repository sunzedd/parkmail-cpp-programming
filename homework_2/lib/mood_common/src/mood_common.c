#include "mood_common/mood_common.h"

int get_digraph_mood_value(char c) {
    if (c == ')')
        return 1;
    if (c == '(')
        return -1;
    return 0;
}
