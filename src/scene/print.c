#include <stdio.h>
#include <scene/scene.h>

void	print_scene(struct s_scene scene)
{
	printf("struct scene => {\n");
	printf("\tambient light => {\n");
	printf("\t\tbritness => %f;\n", scene.ambient.ratio);
	printf("\t\tcolor => 0x%x {%d, %d, %d};\n", scene.ambient.color.rgb,
		scene.ambient.color.r, scene.ambient.color.g, scene.ambient.color.b);
	printf("\t}\n");
	printf("\tcamera => {\n");
	printf("\t\tfov => %f;\n", scene.camera.fov);
	printf("\t\tposition => {%f, %f, %f};\n", scene.camera.position.x,
		scene.camera.position.y, scene.camera.position.z);
	printf("\t\torientation => {%f, %f, %f};\n", scene.camera.orientation.x,
		scene.camera.orientation.y, scene.camera.orientation.z);
	printf("\t}\n");
	printf("}\n");
}
