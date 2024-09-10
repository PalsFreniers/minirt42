#include "ui/buttons.h"
#include <stdbool.h>

void	button_set_index(struct s_button *self, int index)
{
	self->has_idx = true;
	self->data_index = index;
}
