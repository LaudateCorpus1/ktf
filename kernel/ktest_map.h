/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 *    Author: Knut Omang <knut.omang@oracle.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * ktest_map.h: simple objects with name lookup to be inlined into a
 *    larger object
 */

#ifndef _KTEST_MAP_H
#define _KTEST_MAP_H
#include <linux/version.h>
#include <linux/rbtree.h>

#define KTEST_MAX_NAME 20

struct ktest_map {
	struct rb_root root; /* The rb tree holding the map */
	size_t size;	     /* Current size (number of elements) of the map */
};

struct ktest_map_elem {
	struct rb_node node;	      /* Linkage for the map */
	char name[KTEST_MAX_NAME+1];  /* Name of the element - must be unique within the same map */
};


#define DEFINE_KTEST_MAP(_mapname) \
	struct ktest_map _mapname = { \
		.root = RB_ROOT, \
		.size = 0, \
	}

void ktest_map_init(struct ktest_map *map);

/* returns 0 upon success or -errno upon error */
int ktest_map_elem_init(struct ktest_map_elem *elem, const char *name);

/* Insert a new element in map - return 0 iff 'elem' was inserted or -1 if
 * the key already existed - duplicates are not insterted.
 */
int ktest_map_insert(struct ktest_map *map, struct ktest_map_elem *elem);

/* Find and return the element 'name' */
struct ktest_map_elem *ktest_map_find(struct ktest_map *map, const char *name);

/* Find the first map elem in 'map' */
struct ktest_map_elem *ktest_map_find_first(struct ktest_map *map);

/* Find the next element in the map after 'elem' if any */
struct ktest_map_elem *ktest_map_find_next(struct ktest_map_elem *elem);

/* Remove the element 'name' from the map and return a pointer to it */
struct ktest_map_elem *ktest_map_remove(struct ktest_map *map, const char *name);

static inline size_t ktest_map_size(struct ktest_map *map) {
	return map->size;
}

#endif
