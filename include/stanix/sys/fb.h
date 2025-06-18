#ifndef _SYS_FB_H
#define _SYS_FB_H

struct fb {
    long width;
    long height;
    long pitch;
    long bpp;
    long red_mask_size;
    long red_mask_shift;
    long green_mask_size;
    long green_mask_shift;
    long blue_mask_size;
    long blue_mask_shift;
};

#define IOCTL_GET_FB_INFO 0

#endif