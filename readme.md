# Implementation of graph to represent money transactions between two bank accounts #
## Graph structure ##
A list of vertices where each vertex has a list of edges. <br>
The vertices represent the bank accounts and the edges the transactions.
Bank accounts (vertices) have an id (incremented by 1) and name. <br>
Transactions (edges) have a weight which is the amount of money transferred and a pointer to the receiver's vertex. 
## Input ##
User can give input as a command line argument(not mandatory) with flag -i. <br> 
In this case the graph will be initialized with the accounts and transactions stated in the file. <br>
Some sample input files are in test_data folder. 
```
./mygraph -i test_data/InputFile-Medium.csv
```
Main function always asks for a user command from the following list of possible commands: <br>
* i Ni : Insert new bank account with name Ni to graph.
```
Please enter a command: i Marcus_Duncan
- Inserted |Marcus_Duncan|
```
* n Ni Nj weight : Insert new transaction between bank accounts with names Ni,Nj to graph (bank accounts can already exist or not).
```
Please enter a command: n Leonard_Reeves Shawn_Ford 54
- Inserted |Leonard_Reeves|->54->|Shawn_Ford|
```
* d Ni : Delete bank account with name Ni from graph along with all its transactions (delete all edges pointing to this bank account or linked to this bank account).
```
Please enter a command: d Tom_Casey
- Deleted |Tom_Casey|
```
* l Ni,Nj (weight) : Delete all transactions (edges) between accounts Ni,Nj with the specified weight. If weight is not given then delete all transactions between these two accounts.
```
Please enter a command: l Alvin_Perkins Marcus_Duncan 779
- Del-vertex |Alvin_Perkins|->779->|Marcus_Duncan|
```
* m Ni Nj weight nweight : Modify the weight in transaction between accounts Ni,Nj with specified weight to nweight. If more than one such transaction, modify the first to come across.
```
Please enter a command: m Tom_Casey Myra_Burke 543 400
- Mod-vertex |Tom_Casey|->400->|Myra_Burke|
```
* r Ni :  Print all transactions that account Ni is the receiver.
```
Please enter a command: r Myra_Burke
- Rec-edges
        |Hulda_Zimmerman|->489->|Myra_Burke|
        |Marcus_Duncan|->623->|Myra_Burke|
        |Leonard_Reeves|->867->|Myra_Burke|
        |Tom_Casey|->543->|Myra_Burke|
        |Jim_Johnston|->759->|Myra_Burke|
```
* c Ni : Print all simple circles of account Ni if they exist. 
```
Please enter a command: c Jim_Johnston
- Cir found
        ->|Jim_Johnston|->759->|Myra_Burke|->123->|Jim_Johnston|
        ->|Jim_Johnston|->945->|Leonard_Reeves|->113->|Dean_Fields|->916->|Josie_Burke|->514->|Jack_Hawkins|->368->|Shawn_Ford|->341->|Alvin_Perkins|->779->|Marcus_Duncan|->623->|Myra_Burke|->123->|Jim_Johnston|
        ->|Jim_Johnston|->945->|Leonard_Reeves|->113->|Dean_Fields|->916->|Josie_Burke|->514->|Jack_Hawkins|->368->|Shawn_Ford|->341->|Alvin_Perkins|->755->|Marcus_Duncan|->623->|Myra_Burke|->123->|Jim_Johnston|
        ->|Jim_Johnston|->945->|Leonard_Reeves|->113->|Dean_Fields|->916->|Josie_Burke|->514->|Jack_Hawkins|->368->|Shawn_Ford|->100->|Emilie_Horton|->137->|Tom_Casey|->543->|Myra_Burke|->123->|Jim_Johnston|
        ->|Jim_Johnston|->945->|Leonard_Reeves|->867->|Myra_Burke|->123->|Jim_Johnston|
```
* pe Ni : Print all edges (transactions) of account Ni.
```
Please enter a command: pe Alvin_Perkins 
Marcus_Duncan 779
Marcus_Duncan 755
Ola_Rios 859
```
* pv : Print all vertices (accounts) of graph.
```
Please enter a command: pv
Hulda_Zimmerman
Lina_Bennett
Alvin_Perkins
Todd_Park
Josie_Burke
Dean_Fields
Emilie_Horton
Marcus_Duncan
```
* e : Exit program after freeing allocated memory.
```
Please enter a command: e
- exit program
```

