#!/bin/bash

#PBS -N offload
#PBS -q training
#PBS -j oe
#PBS -V
#PBS -l nodes=1:ppn=8:mics=1
#PBS -l walltime=00:01:00

export OFFLOAD_DEVICES=`set_offload_devices`

export MIC_ENV_PREFIX=MIC
export MIC_OMP_NUM_THREADS=236
export MIC_KMP_AFFINIY=compact,granularity=fine

cd $PBS_O_WORKDIR

./runme
