#Grails-Index

MIT LICENSED

Implemented in C
Needs as an argument a file which contains a graph formatted as :
  nodeId1 nodeId2
        .
        .
        .
  nodeIdX nodeIdY

where relation exists between every couple.
You can set from generalParams.h file the labeling LABEL_LEVEL which is set 5 as a default value.
Notice that higher value of LABEL_LEVEL results as faster queries but more space as well.
You can take a loot of the paper:
  http://www.cs.rpi.edu/~zaki/PaperDir/VLDB10.pdf

Grails is an index used to answer very fast in linear time and space if there is no path between 2 vertices of a directed acyclic graph. If this query traversal can't be answered then dfs with prunning is used which is very effective due to its labeling index. 

If you want to extend Grails to support directed acycle graphs, you can take a look in my thesis where Kosaraju's algorithm is used to vanish all cycles in graph by creating strong connected components of the graph.
