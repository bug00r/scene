#include <stdio.h>
#include <assert.h>
#include "scene.h"
#include "scene_builder.h"

int 
main() 
{
	#ifdef debug
		printf("Start test scene lib\n");	
		printf("End test scene lib\n");
	#endif		

	float waterfall_data[240] = { 
		0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.010309f,0.041237f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.000000f,0.989691f,0.773196f,0.000000f,0.000000f,0.350515f,0.030928f,0.515464f,0.000000f,0.979381f,0.876289f,0.000000f,0.000000f,0.412371f,0.020619f,0.659794f,0.000000f,0.989583f,0.906250f,0.000000f,0.000000f,0.354167f,0.197917f,0.697917f,0.000000f,0.989691f,0.948454f,0.000000f,0.010309f,0.783505f,0.360825f,0.773196f,0.000000f,0.979381f,0.958763f,0.000000f,0.010309f,0.721649f,0.268041f,0.804124f,0.000000f,0.989691f,0.969072f,0.000000f,0.000000f,0.742268f,0.412371f,0.762887f,0.000000f,1.000000f,0.938144f,0.000000f,0.092784f,0.989691f,0.608247f,0.927835f,0.000000f,0.989362f,1.000000f,0.000000f,0.095745f,0.914894f,0.531915f,0.904255f,0.000000f,1.000000f,0.989796f,0.000000f,0.040816f,0.938776f,0.693878f,0.948980f,0.000000f,1.000000f,1.000000f,0.000000f,0.247423f,0.989691f,0.762887f,0.969072f,0.000000f,1.000000f,1.000000f,0.000000f,0.312500f,0.989583f,0.750000f,0.968750f,0.000000f,1.000000f,1.000000f,0.000000f,0.239583f,1.000000f,0.843750f,0.958333f,0.000000f,1.000000f,1.000000f,0.000000f,0.479167f,1.000000f,0.885417f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.391753f,1.000000f,0.793814f,0.989691f,0.000000f,1.000000f,1.000000f,0.000000f,0.593750f,1.000000f,0.927083f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.625000f,1.000000f,0.989583f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.731959f,0.979381f,0.989691f,1.000000f,0.000000f,1.000000f,1.000000f,0.010417f,0.802083f,0.989583f,1.000000f,0.989583f,0.000000f,1.000000f,1.000000f,0.000000f,0.865979f,1.000000f,1.000000f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.750000f,1.000000f,0.979167f,1.000000f,0.000000f,1.000000f,1.000000f,0.000000f,0.865979f,1.000000f,1.000000f,1.000000f
	};

	scene_t * waterfall_diag = scene_create_waterfall_diagram(&waterfall_data[0], 30, 8); 

	free_scene(waterfall_diag);

	return 0;
}