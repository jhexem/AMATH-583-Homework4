#!/bin/bash

#SBATCH --job-name=Homework4p3
#SBATCH --account=amath
#SBATCH --partition=gpu-rtx6k
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=20
#SBATCH --mem=5G
#SBATCH --gpus=0
#SBATCH --time=00-00:10:00

#SBATCH --chdir=/gscratch/amath/hexem/codes
#SBATCH --export=all
#SBATCH --output=test-out.txt # where STDOUT goes
#SBATCH --error =test-err.txt  # where STDERR goes

# Modules to use (optional).
module load gcc/11.2.0 ompi/4.1.3

# Your programs to run.
mpirun -np 1 ./xp3 100000000
mpirun -np 2 ./xp3 100000000
mpirun -np 3 ./xp3 100000000
mpirun -np 4 ./xp3 100000000
mpirun -np 5 ./xp3 100000000
mpirun -np 6 ./xp3 100000000
mpirun -np 7 ./xp3 100000000
mpirun -np 8 ./xp3 100000000
mpirun -np 9 ./xp3 100000000
mpirun -np 10 ./xp3 100000000
mpirun -np 11 ./xp3 100000000
mpirun -np 12 ./xp3 100000000
mpirun -np 13 ./xp3 100000000
mpirun -np 14 ./xp3 100000000
mpirun -np 15 ./xp3 100000000
mpirun -np 16 ./xp3 100000000
mpirun -np 17 ./xp3 100000000
mpirun -np 18 ./xp3 100000000
mpirun -np 19 ./xp3 100000000
mpirun -np 20 ./xp3 100000000
mpirun -np 21 ./xp3 100000000
mpirun -np 22 ./xp3 100000000
mpirun -np 23 ./xp3 100000000
mpirun -np 24 ./xp3 100000000
mpirun -np 25 ./xp3 100000000
mpirun -np 26 ./xp3 100000000
mpirun -np 27 ./xp3 100000000
mpirun -np 28 ./xp3 100000000
mpirun -np 29 ./xp3 100000000
mpirun -np 30 ./xp3 100000000
mpirun -np 31 ./xp3 100000000
mpirun -np 32 ./xp3 100000000
mpirun -np 33 ./xp3 100000000
mpirun -np 34 ./xp3 100000000
mpirun -np 35 ./xp3 100000000
mpirun -np 36 ./xp3 100000000
mpirun -np 37 ./xp3 100000000
mpirun -np 38 ./xp3 100000000
mpirun -np 39 ./xp3 100000000
mpirun -np 40 ./xp3 100000000