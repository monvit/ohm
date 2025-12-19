#include <iostream>
#include <vector>
#include <string>

void heavy_computation() {
    int result = 0;
    for (int i = 0; i < 1000; ++i) {
        result += i;
    }
}

void quick_task() {
    std::cout << "  -> Quick task completed." << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "--- Example Program ---" << std::endl;

    if (argc > 1) {
        std::cout << "Provided command-line arguments:" << std::endl;
        for (int i = 1; i < argc; ++i) {
            std::cout << "  Arg " << i << ": " << argv[i] << std::endl;
        }
    } else {
        std::cout << "No additional command-line arguments provided." << std::endl;
    }

    std::vector<std::string> taskList = {"Quick Task", "Heavy Computation"};
 
    int counter = 1;
    for (const auto& task : taskList) {
        std::cout << counter++ << ". " << task << std::endl;
    }

    quick_task();
    
    std::cout << "Processing data..." << std::endl;
    for (int i = 0; i < 3; i++) {
        heavy_computation();
    }

    return 0;
}
