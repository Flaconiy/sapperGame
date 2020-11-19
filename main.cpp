#include "miner.h"
#include <iostream>

using namespace std;

int main()
try {
        Sapper sss{Graph_lib::Point(100,100)};
        return Graph_lib::gui_main();
    }

catch (exception& e) {
    cerr<<e.what()<<endl;
}

catch (...) {
    cerr<<"Ooops, smth went wrong. Call to developer! ";
}

