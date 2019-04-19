#pragma once

#include "ittnotify.h"

__itt_domain* domain = __itt_domain_create("MyDomain");
__itt_string_handle* op_task = __itt_string_handle_create("SpMV");