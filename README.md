# Min-Cost-Covering
## Min-Cost Covering by Dynamic Programming
### For each primary input, cost to cover is 0.
### For each (non-leaf) node 𝑣 in the subject trees
#### Recursive assumption
##### We know a best cost cover for each of its (transitive) predecessors.
#### Recursive formula for cost to cover 𝑣
##### For each matched pattern graph, compute sum of the cost of this pattern and the total best costs 
##### Take the minimum as best cost for node
### Total cost is the sum of the best costs for all primary outputs of the subject trees.
## Example
### Subject tree
![p1](./img/p1.png)
### Pattern trees
![p2](./img/p2.png)
### Input
#### A Verilog-like circuit file
#### Logic gates’ cost (Pattern Trees)
### Output
#### By using the pattern trees and dynamic programming algorithm, output the minimum cost on terminal.
