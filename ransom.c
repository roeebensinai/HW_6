#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

// define nodes and lists
struct node {
	char *word;
	struct node *next;
};

struct list {
    struct node *head;
    struct node *tail;
};

struct node* create_words_node (char *word){
    struct node *node = malloc(sizeof(struct node));
    if (node==NULL) { 
        return(NULL);
    }
    node->word = word;
    node->next = NULL;
    return node;
}

// add new node to the end of the list
void insert_node_to_list(struct list **list,char *word){
    struct node *node = create_words_node (word);
    if (!(*list)->head){
        (*list)->head = node;
    }
    else{
        (*list)->tail->next = node;
    }
    (*list)->tail = node;
    return;
}

// create new list with word as the key
void create_list(struct list **list,char **text,int count_words) {
    for(int i=0;i<count_words;i++) {
        insert_node_to_list(list,*(text+i));
    }
    return;
}

// delete used linked list
void free_linked_list(struct node *node){
    struct node *cursor;
    struct node *cursor_copy;
    cursor=node;
    while (cursor) {
        cursor_copy= cursor;
        cursor = cursor->next;
        free(cursor_copy);
    }
    return;
}

// delete node
void remove_node(struct list *list, char *key) {
    struct node* tmp = list->head , *prev; 
    if (tmp->word==key && tmp != NULL){
        list->head=tmp->next;
        free(tmp);
        return;
    }
    while (tmp->word!=key && tmp != NULL){ 
        prev=tmp;
        tmp=tmp->next;

    }
    if (tmp==NULL) 
    {
        return;
    }
    prev->next=tmp->next;
    free(tmp);
}

// compare words between magazine and note
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {
    // print "No" if number of words in note is bigger than in magazine
    if (magazine_count < note_count) {
        printf("No");
        return;
    } else {

        struct list *note_list;
        struct list *magazine_list;

        note_list = (struct list*)malloc(sizeof(struct list));
        magazine_list = (struct list*)malloc(sizeof(struct list));

        create_list(&magazine_list,magazine,magazine_count);
        create_list(&note_list,note,note_count);

        while (note_list->head) {
            struct node *note_temp = note_list->head;
            struct node *magazine_temp = magazine_list->head;
            // compare each word in note to magazine's words
            while((strcmp(note_temp->word,magazine_temp->word)) && (magazine_temp->next)) {
                magazine_temp=magazine_temp->next;
            }
            // if we found a match
            if ((strcmp(magazine_temp->word,note_temp->word)) == 0) {
                remove_node(magazine_list,magazine_temp->word);
                note_list->head= note_list->head->next;
                free(note_temp);
            }
            else{
                printf("No");
                // free the memory
                free_linked_list(note_list->head);
                free_linked_list(magazine_list->head);
                free(magazine_list);
                free(note_list);
                return;
            }
        }
        free_linked_list(note_list->head);
        free(note_list);
        free(magazine_list);
        printf("Yes"); // in any other case we get a match
        return;
	}
}


int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
