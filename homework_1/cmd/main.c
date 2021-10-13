#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tag.h"

void print_tag(const tag_t *tag) {
    if (!tag) {
        printf("tag is NULL\n\n");
        return;
    }

    printf("name:               %s\n", tag->name);
    printf("type:               %d\n", tag->type);
    printf("attributes count:   %d\n", tag->attribute_count);

    for (int i = 0; i < tag->attribute_count; i++) {
        printf("\t%s", tag->attributes[i].name);
        if (tag->attributes[i].value) {
            printf("  =  %s\n", tag->attributes[i].value);
        }
    }
    printf("\n\n");
}

int main(void) {
    const char *const t1 = "<script type=\"module\" src=\"new_tab_page.js\">";
    const char *const t2 = "<video width=\"320\" height=\"240\" controls>";
    const char *const t3 = "asd";

    int err = OK;

    tag_t *tag1 = tag_create_from_html(&err, t1);
    printf("log error: %d\n", err);
    tag_t *tag2 = tag_create_from_html(&err, t2);
    printf("log error: %d\n", err);
    tag_t *tag3 = tag_create_from_html(&err, t3);
    printf("log error: %d\n", err);

    print_tag(tag1);
    print_tag(tag2);
    print_tag(tag3);

    tag_destroy(tag1);
    tag_destroy(tag2);
    tag_destroy(tag3);

    return 0;
}