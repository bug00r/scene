#if 0
/**
	Functions for creating simple until complex meshes.
*/
#endif

#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H

#include <stdlib.h>
#include "vec.h"
#include "mesh_builder.h"
#include "scene.h"

#if 0
	//This screate a simple testscene inclunding some geometric components
#endif
scene_t * scene_create_test();
scene_t * scene_create_test_cube();
scene_t * scene_create_test_all();
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

#if 0
	//Creates a tree
#endif
scene_t * scene_create_tree();

#endif
