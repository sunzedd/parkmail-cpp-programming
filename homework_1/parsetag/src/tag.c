#include "tag.h"


void attribute_destroy_internals(attribute* attrib) {
    if (attrib->name) {
        free(attrib->name);
        attrib->name = NULL;
    }
    if (attrib->value) {
        free(attrib->value);
        attrib->value = NULL;
    }
}

attribute attribute_construct_from_html(int* err, const char* const html_str) {
    attribute result = { 0 };

    int token_count = 0;
    char** tokenized_html = split_string(err, &token_count, html_str, "=");

    if (token_count == 1) {
        result.name = strdup(tokenized_html[0]);
        if (!result.name) {
            *err = ERR_MEM_ALLOC;
        }
        result.value = NULL;
    }
    else if (token_count == 2) {
        result.name = strdup(tokenized_html[0]);
        if (!result.name) {
            *err = ERR_MEM_ALLOC;
        }

        size_t value_str_size = strlen(tokenized_html[1]) - 2; 
        result.value = (char*)malloc(value_str_size);
        if (!result.value) {
            *err = ERR_MEM_ALLOC;
        }
        else {
            memcpy(result.value, tokenized_html[1] + 1, value_str_size);
        }
    }
    else {
        *err = ERR_INVALID_HTML_SYNTAX;
    }

    destroy_string_array(tokenized_html, token_count);

    if (*err != OK) {
        attribute_destroy_internals(&result);
    }

    return result;
}


int tag_validate_html_str(const char* const tag_str) {
    if (!tag_str) {
        return ERR_INVALID_ARGS;
    }

    if (tag_str[0] != '<' || tag_str[strlen(tag_str) - 1] != '>') {
        return ERR_INVALID_HTML_SYNTAX;
    }

    return OK;
}


static int tag_read_attributes(tag* tag, const char** const html_str_array, int str_count) {
    if (!tag || !html_str_array) {
        return ERR_INVALID_ARGS;
    }

    if (str_count) {

    }

    attribute* attrib_array = (attribute*)malloc(sizeof(attribute) * str_count);
    if (!attrib_array) {
        return ERR_MEM_ALLOC;
    }

    int err = OK;
    for (int i = 0; i < str_count && err == OK; i++) {
        attrib_array[i] = attribute_construct_from_html(&err, html_str_array[i]);
    }

    if (err == OK) {
        tag->attributes = attrib_array;
        tag->attribute_count = str_count;
    }
    else {
        for (int i = 0; i < str_count; i++) {
            attribute_destroy_internals(&attrib_array[i]);
        }
        free(attrib_array);
    }

    return err;
}

static int tag_read_name_and_type(tag* tag, const char* const html_str) {
    if (!tag || !html_str) {
        return ERR_INVALID_ARGS;
    }

    int err = OK;
    short tag_type = TAG_TYPE_OPENING;

    if (html_str[0] == '/') {
        tag_type = TAG_TYPE_CLOSING;
        tag->name = (char*)malloc(sizeof(char) * (strlen(html_str) - 1));
        if (!tag->name) {
            err = ERR_MEM_ALLOC;
            return err;
        }
        strcpy(tag->name, html_str + 1);
    }
    else {
        tag->name = strdup(html_str);
        if (!tag->name) {
            err = ERR_MEM_ALLOC;
            return err;
        }
    }

    tag->type = tag_type;
    return err;
}

void tag_destroy(tag* tag) {
    if (!tag) {
        return;
    }

    if (tag->name) {
        free(tag->name);
    }
    if (tag->attributes) {
        for (int i = 0; i < tag->attribute_count; i++) {
            attribute_destroy_internals(&tag->attributes[i]);
        }
    }

    free(tag);
    tag = NULL;
}

static tag* tag_create(int* err) {
    tag* tag = (struct tag*)malloc(sizeof(struct tag));
    if (!tag) {
        *err = ERR_MEM_ALLOC;
        return NULL;
    }

    tag->name = NULL;
    tag->attribute_count = 0;
    tag->type = 0;
    tag->attributes = NULL;

    return tag;
}

tag* tag_create_from_html(int* err, const char* const tag_str) {
    *err = tag_validate_html_str(tag_str);
    if (*err != OK) {
        return NULL;
    }

    int tokenized_html_str_count = 0;
    char** tokenized_html = split_string(err, &tokenized_html_str_count, tag_str, " <>");
    if (!tokenized_html) {
        return NULL;
    }

    tag* tag = tag_create(err);
    if (!tag) {
        destroy_string_array(tokenized_html, tokenized_html_str_count);
        return NULL;
    }

    *err = tag_read_name_and_type(tag, tokenized_html[0]);
    if (*err == OK) {
        if ((tokenized_html_str_count - 1) > 0) {
            *err = tag_read_attributes(tag, (const char** const)&tokenized_html[1], tokenized_html_str_count - 1);
        }
    } 
    else {
        tag_destroy(tag);
    }

    destroy_string_array(tokenized_html, tokenized_html_str_count);

    return tag;
}
