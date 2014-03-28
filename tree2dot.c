#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE_ID_LEN 3
#define MAX_NODE_NAME_LEN 63

typedef struct _node {
	char id[MAX_NODE_ID_LEN+1];
	char label[MAX_NODE_NAME_LEN+1];
	struct _node *prev;
} node;

void skip_whitespace();
void inc_next_id();
int contains(const char*, int);

node *init_node(node*);
void output_node(node*);
node *pop_node(node*);
void read_label(char*, const char*);

static char next_id[MAX_NODE_ID_LEN+1];

int main() {
	node *tree = NULL;
	int go = 1;
	int n;
	
	/* init things */
	for (n = 0; n < MAX_NODE_ID_LEN; n++) {
		next_id[n] = 'a';
	}
	next_id[MAX_NODE_ID_LEN] = 0;
	
	puts("// generated with tree2dot");
	puts("graph tree {");
	puts("node [shape=plaintext];");
	
	skip_whitespace();
	
	/* start reading and outputting tree */
	while (go) {
		int c = getchar();
		
		if (c == EOF) {	/* no more input */
			go = 0;
		} else if (c == '(') {	/* new branch/node */
			tree = init_node(tree);
			skip_whitespace();
		} else if (c == ')') {	/* end of node */
			tree = pop_node(tree);
			skip_whitespace();
		} else if (c == '"') {	/* node value string */
			if (tree->label[0] == 0) {
				read_label(tree->label, "\"");
			} else {
				node *temp_node = init_node(tree);
				read_label(temp_node->label, "\"");
				pop_node(temp_node);
			}
			getchar();
			skip_whitespace();
		} else if (c == '\'') {	/* node value string */
			if (tree->label[0] == 0) {
				read_label(tree->label, "'");
			} else {
				node *temp_node = init_node(tree);
				read_label(temp_node->label, "'");
				pop_node(temp_node);
			}
			getchar();
			skip_whitespace();
		} else {	/* node value string */
			ungetc(c, stdin);
			if (tree->label[0] == 0) {
				read_label(tree->label, "() \t\n");
			} else {
				node *temp_node = init_node(tree);
				read_label(temp_node->label, "() \t\n");
				pop_node(temp_node);
			}
			skip_whitespace();
		}
	}
	
	/* finish up tree */
	puts("}");
	
	return 0;
}

void skip_whitespace() {
	char c;
	while ((c = getchar()) != EOF &&
			(c == ' ' || c == '\t' || c == '\n'));
	ungetc(c, stdin);
}

void inc_next_id() {
	int n;
	for (n = MAX_NODE_ID_LEN - 1; n > 0; n--) {
		next_id[n]++;
		if (next_id[n] > 'z') {
			next_id[n] = 'a';
		} else {
			return;
		}
	}
}

int contains(const char *str, int c) {
	if (*str == 0) {
		return 0;
	} else if (*str == c) {
		return 1;
	} else {
		return contains(str+1, c);
	}
}

node *init_node(node *parent) {
	node *ret = malloc(sizeof(node));
	strcpy(ret->id, next_id);
	ret->label[0] = 0;
	inc_next_id();
	ret->prev = parent;
	
	return ret;
}

void output_node(node *elem) {
	printf("%s\t[label=\"%s\"];\n", elem->id, elem->label);
	if (elem->prev != NULL) {
		printf("%s -- %s;\n", elem->prev->id, elem->id);
	}
}

node *pop_node(node *tree) {
	node *old_node = tree;
	output_node(old_node);
	tree = tree->prev;
	free(old_node);
	return tree;
}

void read_label(char *str, const char *skip) {
	int n = 0;
	int c;
	
	while ((c = getchar()) != EOF && !contains(skip, c)) {
		if (c == '\\') {
			c = getchar();
		}
		if (n < MAX_NODE_NAME_LEN) {
			str[n] = c;
			n++;
		}
	}
	
	ungetc(c, stdin);
	str[n] = 0;
}
