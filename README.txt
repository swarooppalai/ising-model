ISING MODEL
2-D Ising Model Simulation in Fortran
H=-J*SUM(sig(i)*sig(j)){over nearest neighbours}

We can solve this exactly. sig(i)=+1, J>0

We need the average magnetisation vs Temperture plot
Start with a 4x4 lattice. Randomly give each site a spin (sir wil give a startin system)
Implement periodic boundary condition, where a spin interacts with 4 spins around it. Calculate the energy of the system. 

1-Start with a high T, T=2
2-For a given T, start with a random config of spin system. 
3-Apply metropolis algorithm, calculate energy (E1)
4-Start a loop in which we change the sign of the spin.
5-Calculate the energy again(E2)
6-If E2<E1 then accept the new config. If E2>E1 then accept the new config witha probability of exp(-(E2-E1)/KT). Generate a random number. If the random number is greater
 than this accept, else reject. 
7-Plot energy with monte carlo steps. We reach a equilibrium
8-After reaching equilibrium, sum up all the spins and then divide it by number of lattice sites to get average magnetization
