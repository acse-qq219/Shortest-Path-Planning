# Path planning for energy distribution system
Study notes of UAV path planning for energy distribution system.

## Wireless power transfer background
Consider a two-stage energy distribution system [1]. 
    1. UAV interacts with center senosr node(s)
    2. Center sensor node(s) interact with other nodes

<div align=center><img width="400" height="280" src="figures/2-stage energy distribution system.png"/></div>

For inductive power delivery, Ampere's Law and Faraday's Law need to be applied. The flux linkage looks like [2]:  

<div align=center><img width="750" height="250" src="figures/flux linkage.png"/></div>

The induced voltage is expressed by:

<div align=center><img width="96" height="38" src="figures/faraday's Law equation.png"/></div>

For acoustic power distribution, there's piezoelectric driver and transducer in each sensor node. Therefore the energy of the storage capacitor **E<sub>SC</sub>** at any time **t** can be expressed as:

<div align=center><img width="405" height="19" src="figures/capacitor energy equation.png"/></div>

where **E<sub>m</sub>** is the energy consumption from storage capacitor within an unit timestamp, **T** is the acoustic power transmitted to other nodes within an unit timestamp, **R** is the acoustic power transmitted from other nodes, **I** is indevtice power transmitted from the UAV. 

## Single weighted node clustering and multi-clusters
Therefore, to find the optimal center node, iterative loop is required. This search is bounded by acoustic limits. The choosing criteria should be:

<div align=center><img width="156" height="51" src="figures/choosing criteria.png"/></div>

where d(P, P<sub>i</sub>) is the distance between node i position and current node position, w<sub>i</sub> is the weighing parameter of node i (the energy of storage capacitor). This is because the altitude of UAV will affect the number of charging nodes.

Then for larger planes, multiple clusters will be formed like following figure [3]:

<div align=center><img width="639" height="229" src="figures/multi-clusters.png"/></div>

The algorithm is aimed at finding the minimum path.

## Dijkstra's algorithm
The method is to find the shortest path between two nodes in weighting system G = {V, E}. Basically, the main concept is marking each node with (length or * as unknown) and separating G into two sets V<sub>1</sub> (node length which is already known) and V<sub>2</sub> (node length which is unknown). Consider the following example - assuming we have 6 nodes and from node **a** to destination node **f**:

1. starting node a = 0, b = 3, c = 2, V<sub>1</sub> = {a}, V<sub>2</sub> = {b, c, d, e, f}

<div align=center><img width="380" height="200" src="figures/Dij_0.png"/></div>

2. starting node c, b = 2+5 = 7 > 3 (keep 3 then), e = 2+4 = 6, V<sub>1</sub> = {a, c}, V<sub>2</sub> = {b, d, e, f}

<div align=center><img width="380" height="200" src="figures/Dij_1.png"/></div>

3. starting node b, d = 3+6 = 9 , e = 3+3 = 6, V<sub>1</sub> = {a, c, b}, V<sub>2</sub> = {d, e, f}

<div align=center><img width="380" height="200" src="figures/Dij_2.png"/></div>

4. starting node e, d = 6+5 = 11 > 9 (keep 9 then), f = 6+7 = 13, V<sub>1</sub> = {a, c, b, e}, V<sub>2</sub> = {d, f}

<div align=center><img width="380" height="200" src="figures/Dij_3.png"/></div>

5. starting node d, f = 9+6 = 15 > 13 (keep 13 then), e = 9+5 = 14 > 13 (keep 13 then), V<sub>1</sub> = {a, c, b, e, d}, V<sub>2</sub> = {f}

<div align=center><img width="380" height="200" src="figures/Dij_4.png"/></div>

Then we can get shortest path (a, c, e, f) or (a, b, e, f) and total length is 13.

## Implementation 
This algorithm will be realized through C++. See [Dij_algorithm](Dij_algorithm.cpp) for more information.

# Reference 
[1] D. E. Boyle, S. W. Wright, M. E. Kiziroglou, A. Y. S. Pandiyan, and E. M.
Yeatman, "Inductive Power Delivery with Acoustic Distribution to Wireless
Sensors," in Wireless Power Week, London, UK, 2019.

[2] Abdolkhani, A (2016) Fundamentals of inductively coupled wireless power transfer systems. In Coca, E (ed.), Wireless Power Transfer – Fundamentals and Technologies. Rjieka, Croatia: InTech.

[3] D. E. Boyle, S. W. Wright, M. E. Kiziroglou, A. Y. S. Pandiyan, and E. M.
Yeatman, "Optimal energy distribution using clustering algorithm"