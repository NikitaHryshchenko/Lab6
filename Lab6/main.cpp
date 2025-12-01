#include "generator.hpp"

int main() {
    GeneratorTask task = random_generator();

    for (int i = 0; i < 20; ++i) {
        if (!task.resume()) {
            break;
        }
    }

    return 0;
}
