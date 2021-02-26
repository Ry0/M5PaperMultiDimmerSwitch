#include "id_generator.h"

id_generator::id_generator(int start_id)
{
    id_ = start_id;
}

id_generator::id_generator()
{
    id_ = 0;
}

int id_generator::get_id()
{
    int id = id_;
    id_ += 1;
    return id;
}
