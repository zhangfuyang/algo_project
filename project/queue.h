#pragma once
#ifndef _QUEUE_H_
#include "struct.h"
#define _QUEUE_H_

#define LIST_HEAD(name, type)		\
	struct name				\
	{						\
	struct type *lh_first;	\
	}						

#define LIST_ENTRY(type)			\
	struct{						\
		struct type *le_next; \
		struct type **le_prev;\
	}

#define LIST_EMPTY(head)	((head)->lh_first == NULL)

#define LIST_FIRST(head)	((head)->lh_first)

#define LIST_NEXT(elm, field)	((elm)->field.le_next)

#define LIST_INIT(head) do {			\
		LIST_FIRST(head) = NULL; \
	} while(0) 

#define LIST_FOREACH(var, head, field) 	\
	for((var) = LIST_FIRST((head)); (var); (var) = LIST_NEXT((var), field))

#define LIST_INSERT_HEAD(head, elm, field)	do{	\
	if ((LIST_NEXT((elm), field) = LIST_FIRST((head))) != NULL)	\
		LIST_FIRST((head))->field.le_prev = &LIST_NEXT((elm), field);\
	LIST_FIRST((head)) = (elm);					\
	(elm)->field.le_prev = &LIST_FIRST((head));	\
	} while (0)

#define LIST_REMOVE(elm, field) do{			\
	if ((LIST_NEXT((elm), field)  != NULL)	\
		LIST_NEXT((elm),field)->field.le_prev = (elm)->field.le_prev;\
	*(elm)->field.le_prev = LIST_NEXT((elm),field);	\
	} while (0)

#define LIST_SIZE(var, head, field, k) do{		\
		k = 0;							\
		LIST_FOREACH((var, head, field))		\
			k++;			\
	} while (0)


#endif /*_QUEUE_H_*/