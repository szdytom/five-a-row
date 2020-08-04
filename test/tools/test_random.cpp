#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../../include/tools/random.h"
using namespace std;
using namespace ltzero;
using namespace ltzero::tools;

int main() {
    srand((unsigned)time(nullptr));
    printf("%d\n", randint(5));
    return 0;
}
