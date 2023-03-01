#include <console.hh>
int main() {
    if(!console::init())
        return 0;

    console::run();
    return console::exit();
}
