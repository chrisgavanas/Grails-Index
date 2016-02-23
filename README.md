#Grails-Index

MIT LICENSED

Implemented in C </br>
Needs as an argument a file which contains a graph formatted as :</br>
  nodeId1 nodeId2</br>

where relation exists between every couple.</br>
You can set from generalParams.h file the labeling LABEL_LEVEL which is set 5 as a default value.</br>
Notice that higher value of LABEL_LEVEL results as faster queries but more space as well.</br>
You can take a loot of the paper:</br>
  http://www.cs.rpi.edu/~zaki/PaperDir/VLDB10.pdf</br>
</br>
Grails is an index used to answer very fast in linear time and space if there is no path between 2 vertices of a directed acyclic graph. If this query traversal can't be answered then dfs with prunning is used which is very effective due to its labeling index. </br></br>

If you want to extend Grails to support directed acycle graphs, you can take a look in my thesis where Kosaraju's algorithm is used to vanish all cycles in graph by creating strong connected components of the graph.</br>
