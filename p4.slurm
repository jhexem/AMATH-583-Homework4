#!/bin/bash

#SBATCH --job-name=HW4P4
#SBATCH --mail-type=ALL
#SBATCH --mail-user=jhexem@uw.edu

#SBATCH --account=amath
#SBATCH --partition=gpu-rtx6k
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=10
#SBATCH --mem=5G
#SBATCH --gpus=0
#SBATCH --time=00-00:9:00

#SBATCH --chdir=/gscratch/amath/hexem/codes
#SBATCH --export=all
#SBATCH --output=test-out.txt # where STDOUT goes
#SBATCH --error =test-err.txt  # where STDERR goes

# Modules to use (optional).
module load gcc/11.2.0 ompi/4.1.3

# Your programs to run.
mpirun -np 40 ./xp4 8
mpirun -np 40 ./xp4 16
mpirun -np 40 ./xp4 32
mpirun -np 40 ./xp4 64
mpirun -np 40 ./xp4 128
mpirun -np 40 ./xp4 256
mpirun -np 40 ./xp4 512
mpirun -np 40 ./xp4 1024
mpirun -np 40 ./xp4 2048
mpirun -np 40 ./xp4 4096
mpirun -np 40 ./xp4 8192
mpirun -np 40 ./xp4 16384
mpirun -np 40 ./xp4 32768
mpirun -np 40 ./xp4 65536
mpirun -np 40 ./xp4 131072
mpirun -np 40 ./xp4 262144
mpirun -np 40 ./xp4 524288
mpirun -np 40 ./xp4 1048576
mpirun -np 40 ./xp4 2097152
mpirun -np 40 ./xp4 4194304
mpirun -np 40 ./xp4 8388608
mpirun -np 40 ./xp4 16777216
mpirun -np 40 ./xp4 33554432
mpirun -np 40 ./xp4 67108864
mpirun -np 40 ./xp4 134217728