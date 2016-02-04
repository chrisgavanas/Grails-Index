#pragma once

typedef struct Label* Label_t;

int getSizeOfLabel();
void initLabel(Label_t*);
int getMinSubRank(Label_t);
void setMinSubRank(Label_t, int);
int getRank(Label_t);
void setRank(Label_t, int);
int isSubset(Label_t, Label_t);

