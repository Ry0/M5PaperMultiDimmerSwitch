#ifndef _ID_GENERATOR_H_
#define _ID_GENERATOR_H_

class id_generator
{
public:
    id_generator(int start_id);
    id_generator();
    int get_id();

private:
    int id_;
};
#endif
