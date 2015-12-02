#include <stdlib.h>
#include <string.h>
#include "./../../headers/label.h"

struct Label {
	int minSubRank;
	int rank;
};

int getSizeOfLabel() {
	return sizeof(struct Label);
}

void allocLabel(Label* label) {
	*label = malloc(sizeof(struct Label));
	memset(*label, 0, sizeof(struct Label));
}

int getMinSubRank(Label label) {
	return label->minSubRank;
}

void setMinSubRank(Label label, int minSubRank) {
	label->minSubRank = minSubRank;
}

int getRank(Label label) {
	return label->rank;
}

void setRank(Label label, int rank) {
	label->rank = rank;
}

int isSubset(Label label1, Label label2) {
	return label1->minSubRank >= label2->minSubRank && label1->rank >= label2->rank;
}
