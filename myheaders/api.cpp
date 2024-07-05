#ifndef API
#define API
enum stage_names 
{
    TEST,
    RANDOM,
};

namespace stage_api {
    void(*set)(stage_names);
}

#endif
