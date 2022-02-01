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
scene_t * scene_create_test();
scene_t * scene_create_test_cube();
scene_t * scene_create_test_all(float distance);
scene_t * scene_create_triangle();
scene_t * scene_create_test_point_raster();
#if 0
	//This screate a raster from lines
#endif
scene_t * scene_create_raster(const float linelen);

#if 0
	//Creates a texture Quad/Cube scenery
#endif
scene_t * scene_create_texture_test();

scene_t * scene_create_texture_quad(unsigned int texWidth, unsigned int texHeight, float scalex, float scaley);
scene_t * scene_create_text_quad(texture_cache_t *texCache, float txtSize, float glyphDetail, unsigned char const * const text, cRGB_t *txtColor);

#if 0
	//Creates a tree
#endif
scene_t * scene_create_tree();

#if 0
	//Creates a polygon
#endif
scene_t * scene_create_polys();

#if 0
	//creates waterfall from float array
#endif
scene_t * scene_create_waterfall_diagram(texture_cache_t *texCache, float *array, uint32_t rows, uint32_t cols);

#endif
