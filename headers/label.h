#pragma once

typedef struct Label *Label;

int getSizeOfLabel();
void allocLabel(Label*);
int getMinSubRank(Label);
void setMinSubRank(Label, int);
int getRank(Label);
void setRank(Label, int);
int isSubset(Label, Label);

