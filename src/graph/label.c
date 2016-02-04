#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./../../headers/label.h"

struct Label {
	int minSubRank;
	int rank;
};

int getSizeOfLabel() {
	return sizeof(struct Label);
}

void initLabel(Label_t* label) {
	*label = malloc(sizeof(struct Label));
	memset(*label, 0, sizeof(struct Label));
}

int getMinSubRank(Label_t label) {
	return label->minSubRank;
}

void setMinSubRank(Label_t label, int minSubRank) {
	label->minSubRank = minSubRank;
}

int getRank(Label_t label) {
	return label->rank;
}

void setRank(Label_t label, int rank) {
	label->rank = rank;
}

int isSubset(Label_t label1, Label_t label2) {
//fprintf(stderr, "mesa sto label\n");
//fprintf(stderr, "(%d, %d), (%d, %d)\n", label1->minSubRank, label1->rank, label2->minSubRank, label2->rank);
//fprintf(stderr, "!!%d!!\n", (label1->minSubRank <= label2->minSubRank && label1->rank >= label2->rank));
	return label1->minSubRank >= label2->minSubRank && label1->rank <= label2->rank;
}
