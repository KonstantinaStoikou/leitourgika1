# Implementation of graph to represent money transactions between two bank accounts #
## Graph structure ##
A list of vertices where each vertex has a list of edges. <br>
The vertices represent the bank accounts and the edges the transactions.
Bank accounts (vertices) have an id (incremented by 1) and name. <br>
Transactions (edges) have a weight which is the amount of money transferred and a pointer to the recipient's vertex. 
## Input ##
User can give input as a command line argument (not mandatory). <br>
In this case the graph will be initialized with the accounts and transactions stated in the file. <br>
Some sample input files are in test_data folder. 
```
$ ./mygraph test_data/InputFile-Medium.csv
```

