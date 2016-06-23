CC              =       icc
CFLAGS          =      -openmp -O3 -std=c99 -opt-report=5

tiled: diffusion_tiled.c
	$(CC) $(CFLAGS) diffusion_tiled.c -o diffusion_tiled_xphi

all: tiled

clean: 
	rm -f ./*_xphi



