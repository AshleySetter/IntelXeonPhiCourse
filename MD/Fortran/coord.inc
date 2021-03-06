C $Id: coord.inc,v 1.1 2002/01/08 12:30:07 spb Exp spb $
C This file defines a common block that contains the primary coordinates
C of the particles,
C
C  Nbody	Number of particles
C  Npair	Number of particle pairs
C  pos		Position of the particles
C  vel		velocity of the particles
C  f		Forces acting on each particle
C  visc		viscosity coefficient for each particle
C  mass		mass of each particle
C  delta_x	seperation vector for each particle pair
C  r		seperation for each particle pair
C
      INTEGER Nbody, Npair
      PARAMETER( Nbody=4*1024, Npair=(Nbody*(Nbody-1))/2 )
      INTEGER Xcoord, Ycoord, Zcoord, Ndim
      PARAMETER( Xcoord=1, Ycoord=2, Zcoord=3, Ndim=3 )
      DOUBLE PRECISION pos(Nbody,Ndim), vel(Nbody,Ndim)
      DOUBLE PRECISION f(Nbody,Ndim), visc(Nbody), mass(Nbody)
      DOUBLE PRECISION delta_x(Nbody*Nbody,3)
      DOUBLE PRECISION r(Nbody*Nbody)

      COMMON /coord/ f, pos, visc, mass, vel, delta_x, r

C
C Nominal diameter of the particles.
C
      DOUBLE PRECISION Size
      PARAMETER( Size = 1d0)

C
C Interaction strength for pairwise interactions.
C
      DOUBLE PRECISION G
      PARAMETER( G = 2d0 )
