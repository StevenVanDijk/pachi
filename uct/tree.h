#ifndef ZZGO_UCT_TREE_H
#define ZZGO_UCT_TREE_H

#include <stdbool.h>
#include "move.h"

struct board;

struct tree_node {
	/*
	 *            +------+
	 *            | node |
	 *            +------+
	 *          / <- parent
	 * +------+   v- sibling +------+
	 * | node | ------------ | node |
	 * +------+              +------+
	 *    | <- children          |
	 * +------+   +------+   +------+   +------+
	 * | node | - | node |   | node | - | node |
	 * +------+   +------+   +------+   +------+
	 */
	struct tree_node *parent, *sibling, *children;

	coord_t coord;
	int playouts; // # of playouts coming through this node
	int wins; // # of wins coming through this node
	float value; // wins/playouts
};

struct tree {
	struct tree_node *root;
	struct board *board;
};

struct tree *tree_init(struct board *board);
void tree_done(struct tree *tree);
void tree_dump(struct tree *tree);

void tree_expand_node(struct tree *tree, struct tree_node *node);
void tree_delete_node(struct tree_node *node);
bool tree_leaf_node(struct tree_node *node);
struct tree_node *tree_best_child(struct tree_node *node);

struct tree_node *tree_uct_descend(struct tree_node *node, int parity);
void tree_uct_update(struct tree_node *node, int result);

#endif