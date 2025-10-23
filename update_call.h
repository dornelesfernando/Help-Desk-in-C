#ifndef UPDATE_CALL_H
#define UPDATE_CALL_H

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "logs.h"
#include "services.h"
#include "structs.h"

void update_call(Call *call_data, int login_control, char **logs);

#endif // UPDATE_CALL_H
