
#include "orgfx_vector_font.h"
#include "orgfx_3d.h"
#include "orgfx.h"

#include <stdio.h>

orgfx_vector_font orgfx_make_vector_font(Glyph *glyphlist,int size, Glyph **glyphindexlist, int glyphindexlistsize)
{
    orgfx_vector_font font;
    font.size = size;
    font.glyph = glyphlist;
    font.index_list_size = glyphindexlistsize;
    font.index_list = glyphindexlist;
    return font;
}
// takes all glyphs and generate a pointer list with correct index to all glyphs.
int orgfx_init_vector_font(orgfx_vector_font font)
{
    int i,j;
    // for all in the glyphindex.

    for(i=0; i<font.index_list_size; i++)
        font.index_list[i] = 0;

    for(i=0; i<font.size; i++)
    {
        // if character code is outside our glyph scope, return error
        if(font.glyph[i].index >= font.index_list_size)
            return 1;

        // match the glyph index with the ascii code i
        for(j=0; j<font.index_list_size; j++)
            if(j == font.glyph[i].index )
            {
                font.index_list[j] = &(font.glyph[i]);
                break;
            }
    }
    // all went well
    return 0;
}

void orgfx_vf_write(orgfx_vector_font* glyph, const wchar_t *text, int xoffset, int yoffset, int color)
{
    int i,j;
    int width = 35;
    float scale = 0.05;
    yoffset += width*1.5;

    orgfx_enable_tex0(0);
    orgfx_set_colors(color,color,color);
    i = 0;

    while(1)
    {
        wchar_t c = text[i++];
        // Break if we reach the end of the string
        if(c == 0)
            break;

        if(c != ' ')
            orgfx_vf_write_char(glyph,c, xoffset, yoffset, scale);
        else
            xoffset += 20;

        if(glyph->index_list[c])
            xoffset += glyph->index_list[c]->advance_x*scale;
    }
}

void orgfx_vf_write_char(orgfx_vector_font* glyph, wchar_t text, int xoffset, int yoffset, float scale)
{
    if(glyph->index_list[text] == 0)
        return;

    int i;
    orgfx_point3 scaled = {scale,scale,scale};
    orgfx_point3 translate = {xoffset,yoffset,0};
    orgfx_enable_transform(1);
    orgfx_matrix m = orgfx3d_identity();
    m = orgfx3d_scale(m, scaled);
    m = orgfx3d_translate(m, translate);
    orgfx3d_set_matrix(m);

    for(i=0; i<glyph->index_list[text]->triangle_n_writes; i++)
    {
        orgfx_triangle((glyph->index_list[text]->triangle[i].p0.x)*FIXEDW,(glyph->index_list[text]->triangle[i].p0.y)*FIXEDW,
                       (glyph->index_list[text]->triangle[i].p1.x)*FIXEDW,(glyph->index_list[text]->triangle[i].p1.y)*FIXEDW,
                       (glyph->index_list[text]->triangle[i].p2.x)*FIXEDW,(glyph->index_list[text]->triangle[i].p2.y)*FIXEDW, 1);
    }
    for(i=0; i<glyph->index_list[text]->bezier_n_writes; i++)
    {
        orgfx_curve((glyph->index_list[text]->bezier[i].start.x)*FIXEDW, (glyph->index_list[text]->bezier[i].start.y)*FIXEDW,
                    (glyph->index_list[text]->bezier[i].control.x)*FIXEDW, (glyph->index_list[text]->bezier[i].control.y)*FIXEDW,
                    (glyph->index_list[text]->bezier[i].end.x)*FIXEDW, (glyph->index_list[text]->bezier[i].end.y)*FIXEDW,
                    glyph->index_list[text]->bezier[i].fillInside);
    }

    orgfx_enable_transform(0);
}
