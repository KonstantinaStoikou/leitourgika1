# Implementation of graph to represent money transactions between two bank accounts #
## Graph structure ##
A list of vertices where each vertex has a list of edges. <br>
The vertices represent the bank accounts and the edges the transactions.
Bank accounts (vertices) have an id (incremented by 1) and name. <br>
Transactions (edges) have a weight which is the amount of money transferred and a pointer to the receiver's vertex. 
## Input ##
User can give input as a command line argument (not mandatory). <br>
In this case the graph will be initialized with the accounts and transactions stated in the file. <br>
Some sample input files are in test_data folder. 
```
$ ./mygraph test_data/InputFile-Medium.csv
```
Main function always asks for a user command from the following list of possible commands: <br>
* Insert new bank account with name Ni to graph.
```
$ i Ni
```
* Insert new transaction between bank accounts with names Ni,Nj to graph (bank accounts can already exist or not).
```
$ n Ni Nj weight
```
* Delete bank account with name Ni from graph along with all its transactions (delete all edges pointing to this bank account or linked to this bank account).
```
$ d Ni
```
* Delete all transactions (edges) between accounts Ni,Nj with the specified weight. If weight is not given then delete all transactions between these two accounts.
```
$ l Ni,Nj (weight)
```
* Modify the weight in transaction between accounts Ni,Nj with specified weight to nweight. If more than one such transaction, modify the first to come across.
```
$ m Ni Nj weight nweight
```
* Print all transactions that account Ni is the receiver.
```
$ r Ni
```
* Print all simple circles of account Ni if they exist. 
```
$ c Ni
```
* Print all edges (transactions) of account Ni.
```
$ pe Ni
```
* Print all vertices (accounts) of graph.
```
$ pv
```
* Exit program after freeing allocated memory.
```
$ e
```

