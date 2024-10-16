#ifndef RAY_H
# define RAY_H

# include <object/objects.h>

typedef struct s_ray
{
	struct s_vec3	direction;
	struct s_vec3	origin;
}					t_ray;

/* pseudo:
 * get_color_traced_at_position(scene, x, y):
 *      ray = calculate_ray_for_pixel(&scene.camera, x, y)
 *      f = INFINITY
 *      object = NULL
 *      color = BLACK
 *      pour obj dans scene.objects:
 *              creer tmp
 *              choisir type pour objet:
 *                      si OBJ_LIGHT:
 *                              passer a la boucle suivante
 *                      si OBJ_PLANE:
 *                              si ray_collision_plane_depth(&ray, obj,
	&tmp) est faux:
 *                                      passer a la boucle suivante
 *                              sinon si tmp < f:
 *                                      f = tmp
 *                                      object = obj
 *                      si OBJ_SPHERE:
 *                              si ray_collision_sphere_depth(&ray, obj,
	&tmp) est faux:
 *                                      passer a la boucle suivante
 *                              sinon si tmp < f:
 *                                      f = tmp
 *                                      object = obj
 *                      si OBJ_CYLINDER:
 *                              si ray_collision_cylinder_depth(&ray, obj,
	&tmp) est faux:
 *                                      passer a la boucle suivante
 *                              sinon si tmp < f:
 *                                      f = tmp
 *                                      object = obj
 *      si object != NULL:
 *              position = intersect_ray_object(ray, object)
 *              pour light dans scene.objects:
 *                      si light.type != OBJ_LIGHT:
 *                              passer a la boucle suivante
 *                      sinon:
 *                              pour obj dans scene.objects:
 *                                      si obj == object:
 *                                              passer a la boucle suivante
 *                                      si is_blocking_light_from(position,
	light, obj) est faux:

	*                                              tmp = calculate_color_from_light(ray,
		light, position)
 *                                              color = blend(color, tmp)
 *      renvoyer color
 */

#endif // RAY_H
