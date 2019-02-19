#include "scene.h"
#include <stdio.h>

const size_t scene_size = sizeof(scene_t);

scene_t * 
alloc_scene(const unsigned int meshcount){
	scene_t * newscene = malloc(scene_size);
	newscene->meshes = malloc(meshcount * mesh_ptr_size);
	newscene->cntMesh = meshcount;
	for(int mesh = 0; mesh < newscene->cntMesh; ++mesh){
		newscene->meshes[mesh] = NULL;
	}
	return newscene;
}

void 
free_scene(scene_t *scene){
	for(int mesh = 0; mesh < scene->cntMesh; ++mesh){
		mesh_t * curmesh = scene->meshes[mesh]; 
		if (curmesh != NULL) {
			free_mesh(curmesh);
		}
	}
	free(scene->meshes);
	free(scene);
}

void 
mat_mul_scene(scene_t * scene, const mat3_t * matrix){
	for(int mesh = 0; mesh < scene->cntMesh; ++mesh){
		mat_mul_mesh(scene->meshes[mesh], matrix); 
	}
}

void 
scale_scene(scene_t * scene, const float scalex, const float scaley, const float scalez ){
	for(int mesh = 0; mesh < scene->cntMesh; ++mesh){
		scale_mesh(scene->meshes[mesh], scalex, scaley, scalez); 
	}
}

void 
translate_scene(scene_t * scene, const float tx, const float ty, const float tz ){
	for(int mesh = 0; mesh < scene->cntMesh; ++mesh){
		translate_mesh(scene->meshes[mesh], tx, ty, tz); 
	}
}
