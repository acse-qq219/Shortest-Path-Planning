# Path planning for energy distribution system
Study notes of UAV path planning for energy distribution system.  

## Problem Background
Consider a two-stage energy distribution system. 
    1. UAV interacts with center senosr node(s)
    2. Center sensor node(s) interact with other nodes

<div align=center><img width="400" height="280" src="figures/2-stage energy distribution system.png"/></div>

For inductive power transfer, Ampere's Law and Faraday's Law need to be applied. The flux linkage looks like  

<div align=center><img width="750" height="250" src="figures/flux linkage.png"/></div>

The induced voltage is expressed by:

<div align=center><img width="96" height="38" src="figures/faraday's Law equation.png"/></div>

## Node Clustering
