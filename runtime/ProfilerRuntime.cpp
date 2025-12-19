#include <cstdio>
#include <cstdint>

extern "C" {

void __profiler_entry(uint64_t func_id) {
    printf("[ OHM ] Entered function with ID: %llu\n", func_id);
}

void __profiler_exit(uint64_t func_id) {
    printf("[ OHM ] Exited function with ID: %llu\n", func_id);
}

}