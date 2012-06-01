#include "orgfx_plus.h"
#include "orgfx_3d.h"
#include "orgfx.h"
#include "orgfx_bitmap_font.h"
#include "orgfx_vector_font.h"
#include <math.h>

#include "cube.obj.h"
#include "humanoid_tri.obj.h"
#include "Bahamut_cc.png.h"
#include "interptest.bmp.h"

#include "franklin_font.h"
#include "test_font.h"

//#include "stdio.h"

int main(void)
{
    int i,j;

    int text[] = {65, 228, 0};

    // Initialize screen, no double buffering
    int screen = orgfxplus_init(640, 480, 16, 1, 0);

    int bahamut_sprite = orgfxplus_init_surface(186, 248, Bahamut_cc);
    int interp_sprite = orgfxplus_init_surface(10, 10, interptest);

    int franklin_surface = orgfxplus_init_surface(512, 512, franklin_img);
    orgfx_tileset franklin_ts = orgfx_make_tileset(franklin_surface, franklin_glyphs, 256);
    orgfx_bitmap_font franklin_font = orgfx_make_bitmap_font(&franklin_ts, 5, 16);

    //	orgfx_mesh mesh = orgfx3d_make_mesh(cube_faces, cube_nfaces, cube_verts, cube_nverts);
    // orgfx_mesh mesh = orgfx3d_make_mesh(humanoid_tri_faces, humanoid_tri_nfaces, humanoid_tri_verts, humanoid_tri_nverts);

    float rad = 0;
    int t = 0;

    orgfxplus_colorkey(0xf81f, 1);

    orgfx_point3 offset = {350, 300, 0};
    orgfx_point3 scale = {10.0, 10.0, 10.0};

    //	orgfxplus_clip(50,50,100,100, 0);
    //	orgfx_enable_cliprect(1);


    // vector fonts
    orgfx_vector_font font = init_test_font();

    while(1)
    {
        /*
        orgfx_point3 rot = {2*rad,rad,3*rad};

        mesh.scale = scale;
        mesh.translation = offset;
        mesh.rotation = rot;
*/
        // Clear screen
        orgfxplus_fill(0,0,640*FIXEDW,480*FIXEDW,0xffff);

        for(i = 0; i < 5000000; ++i);
/*
        orgfx3d_draw_mesh(&mesh, 1, 1);

        orgfxplus_fill(0,0,100*FIXEDW,100*FIXEDW,0x0000);

        orgfx_enable_tex0(1);
        orgfxplus_bind_tex0(bahamut_sprite);
        orgfx_uv(0,0,180,0,90,100);
        orgfx_triangle(0,0,100*FIXEDW,0,50*FIXEDW,100*FIXEDW, 1);
        orgfx_enable_tex0(0);

        orgfx_set_colors(0xf800, 0x07c0, 0x003f);
        orgfx_triangle(0,100*FIXEDW,100*FIXEDW,100*FIXEDW,50*FIXEDW,200*FIXEDW, 1);
        //	        orgfx_enable_tex0(0);
        orgfx_triangle(100*FIXEDW,0,200*FIXEDW,0,150*FIXEDW,100*FIXEDW, 0);

        orgfx_curve(200*FIXEDW,0,300*FIXEDW,0,250*FIXEDW,100*FIXEDW,
                     0, 1);

        orgfx_curve(300*FIXEDW,0,400*FIXEDW,0,350*FIXEDW,100*FIXEDW,
                     0, 0);

        orgfxplus_alpha(0x80, 1);
        orgfxplus_draw_surface(100*FIXEDW, 100*FIXEDW, bahamut_sprite);
        orgfxplus_alpha(0xff, 0);
        //	        orgfx_enable_tex0(0);

        orgfx_put_text(&font, 10*FIXEDW, 200*FIXEDW, "some EXAMPLE text");
*/

        orgfx_put_bitmap_text(&franklin_font, 10*FIXEDW, 200*FIXEDW, L"some ÅXÖMBLÄ text");

        orgfx_vf_write(&font , L"some ÅXÖMBLÄ text", 10, 250, 0x0000);
        // draw interp-test
        orgfx_enable_tex0(1);
        orgfxplus_bind_tex0(interp_sprite);
        orgfx_uv(0,0,10,0,0,10);
        orgfx_triangle(0,0,200*FIXEDW,0,0*FIXEDW,200*FIXEDW, 1);
        orgfx_uv(10,0,10,10,0,10);
        orgfx_triangle(200*FIXEDW,0*FIXEDW,200*FIXEDW,200*FIXEDW,0*FIXEDW,200*FIXEDW, 1);
        orgfx_enable_tex0(0);

        orgfx_set_color(0xf800);
        //orgfx_line(0,0,200*FIXEDW,200*FIXEDW);

        t += 5;
        rad += 0.01;
        if(rad >= M_PI*2) rad -= M_PI*2;

        // Swap buffers
        orgfxplus_flip();
    }
}

