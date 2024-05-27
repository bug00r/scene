#if 0
/**
	Functions for creating simple until complex meshes.
*/
#endif

#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include <stdlib.h>
#include <stdint.h>
#include "vec.h"
#include "mesh_builder.h"
#include "scene.h"
#include "texture_cache.h"
#include "r_font.h"
#include "font_provider_default.h"


#if 0
	//This screate a simple testscene inclunding some geometric components
#endif
Scene * scene_create_test();
Scene * scene_create_test_cube();
Scene * scene_create_test_all(float distance);
Scene * scene_create_triangle();
Scene * scene_create_test_point_raster();
#if 0
	//This screate a raster from lines
#endif
Scene * scene_create_raster(const float linelen);

#if 0
	//Creates a texture Quad/Cube scenery
#endif
Scene * scene_create_Textureest();

Scene * scene_create_texture_quad(unsigned int texWidth, unsigned int texHeight, float scalex, float scaley);
Scene * scene_create_text_quad(TextureCache *texCache, float txtSize, float glyphDetail, unsigned char const * const text, ColorRGB *txtColor);

#if 0
	//Creates a tree
#endif
Scene * scene_create_tree();

#if 0
	//Creates a polygon
#endif
Scene * scene_create_polys();

#if 0
	//creates waterfall from float array
#endif
Scene * scene_create_waterfall_diagram(TextureCache *texCache, float *array, uint32_t rows, uint32_t cols);

#endif
