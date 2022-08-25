CC			= /opt/funkey-sdk/usr/bin/arm-linux-gcc
SDL_GFX_LIB	= ~/Documents/Projects/FunKey/SDL_gfx/build/SDL_gfx_fk.a
CFLAGS     += -march=armv7-a+neon-vfpv4 -mtune=cortex-a7 -mfpu=neon-vfpv4 -DFUNKEY=1