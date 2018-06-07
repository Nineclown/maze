#include "astar.h"

ListNode* searchListNode(List *list, Vertex* node) { //����Ʈ�� �ش� ��尡 �ִ��� �˻��ϴ� �Լ�
	ListNode *it;
	it = list->head;

	do {
		if (it->node == node) {
			return it;
		}
		it = it->next;
	} while (it != NULL);

	return NULL;
}

void deleteListNode(List *list, ListNode *list_node) { //����Ʈ���� �ش� ��带 �����ϴ� �Լ�
	ListNode *it;

	it = list->head;

	while (it != list_node) {
		it = it->next;
	};

	if (it == list->head && list->cnt == 1) {
		list->head = NULL;
	}
	else if (it == list->head && list->cnt > 1) {
		list->head = it->next;
		it->next->prev = NULL;
	}
	else if (it->next == NULL) {
		it->prev->next = NULL;
	}
	else {
		it->prev->next = it->next;
		it->next->prev = it->prev;
	}

	free(it);
	list->cnt--;
}

void addListNode(List *list, Vertex *node, Vertex *parent_node, double g_score) { //����Ʈ�� ��带 �߰��ϴ� �Լ�
	ListNode *tmp, *tmp2;
	ListNode *it;

	tmp = (ListNode*)malloc(sizeof(ListNode));
	tmp->node = node;
	tmp->parent_node = parent_node;
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->g_score = g_score;
	tmp->h_score = (Graph_GetEndV(maze_graph)->x - node->x) + (Graph_GetEndV(maze_graph)->y - node->y);
	tmp->f_score = tmp->g_score + tmp->h_score;

	if (list->head == NULL) {
		list->head = tmp;
		list->cnt++;
	}
	else {
		if (list == open_list) {
			tmp2 = searchListNode(open_list, tmp->node);
			if (tmp2 != NULL) {
				if (tmp2->g_score > tmp->g_score) {
					deleteListNode(open_list, tmp2);

					it = list->head;
					while (it->next != NULL) {
						it = it->next;
					}

					it->next = tmp;
					tmp->prev = it;

					list->cnt++;
				}
			}
			else {
				it = list->head;
				while (it->next != NULL) {
					it = it->next;
				}

				it->next = tmp;
				tmp->prev = it;

				list->cnt++;
			}
		}
		else {
			it = list->head;
			while (it->next != NULL) {
				it = it->next;
			}

			it->next = tmp;
			tmp->prev = it;

			list->cnt++;
		}
	}
}

void addOpenList(ListNode *list_node) { //���� ����Ʈ�� ��带 �߰��ϴ� �Լ�
	//int i;

	Iterator seek = 0, end = 0;
	Edge *edge = 0;

	seek = Array_Begin(maze_graph->edges);
	end = Array_End(maze_graph->edges);

	for (seek = seek; seek != end; ++seek) {
		edge = (Edge *)(*seek);

		if (edge->vt1 == list_node->node) {
			if (searchListNode(closed_list, edge->vt2) == NULL)
				addListNode(open_list, edge->vt2, list_node->node, list_node->g_score + edge->weight);
		}
		else if (edge->vt2 == list_node->node) {
			if (searchListNode(closed_list, edge->vt1) == NULL)
				addListNode(open_list, edge->vt1, list_node->node, list_node->g_score + edge->weight);
		}
	}
}

ListNode* getLastListNode(List *list) { //����Ʈ �� ���� ������ ��带 ã�� �Լ�
	ListNode *it;

	it = list->head;
	while (it->next != NULL) {
		it = it->next;
	}

	return it;
}

ListNode* getLowFScoreListNode(List *list) { //����Ʈ���� F ���� ���� ���� ��带 ã�� �Լ�
	ListNode *it;
	ListNode *tmp;
	double min_f_score;

	it = list->head;
	min_f_score = it->f_score;
	tmp = it;

	while (it->next != NULL) {
		it = it->next;
		if (it->f_score < min_f_score) {
			min_f_score = it->f_score;
			tmp = it;
		}
	}

	if (it->f_score < min_f_score) {
		min_f_score = it->f_score;
		tmp = it;
	}

	return tmp;
}

void addClosedList(ListNode *list_node) { //���� ����Ʈ�� ��带 �߰��ϴ� �Լ�
	addListNode(closed_list, list_node->node, list_node->parent_node, list_node->g_score);
	deleteListNode(open_list, list_node);
}

void printListNode(List *list) { //����Ʈ �� ��带 ����ϴ� �Լ�
	ListNode *it;
	it = list->head;

	if (it == NULL) {
		printf("�������\n");
		return;
	}

	do {
		printf("%d ", it->node->name);
		it = it->next;
	} while (it != NULL);

	printf("\n");
}

void printPath(List *list) {
	ListNode *it;
	int cost;

	it = list->head;

	while (it->next != NULL) {
		it = it->next;
	}

	cost = (int)(it->f_score);

	printf("�� - ");

	do {
		it = searchListNode(list, it->parent_node);
		if (it->node->name != 1)
			printf("%d - ", it->node->name);
	} while (it->parent_node != NULL);

	printf("��");

	printf("\n\n��� : %d\n", cost);
	al_cost[4] = cost;

}

void astart(Vertex *start, Vertex *end) { //A* �˰��� �Լ�
	open_list = (List*)malloc(sizeof(List));
	closed_list = (List*)malloc(sizeof(List));

	open_list->head = NULL;
	closed_list->head = NULL;
	open_list->cnt = 0;
	closed_list->cnt = 0;

	addListNode(closed_list, start, NULL, 0);
	printf("Open List: ");
	printListNode(open_list);
	printf("Closed List: ");
	printListNode(closed_list);
	printf("\n");


	while (getLastListNode(closed_list)->node != end) { //������ ��忡 ������ ������ �ݺ�
		addOpenList(getLastListNode(closed_list));
		printf("Open List: ");
		printListNode(open_list);

		addClosedList(getLowFScoreListNode(open_list));
		printf("Closed List: ");
		printListNode(closed_list);

		printf("\n");
	}

	printPath(closed_list);

}