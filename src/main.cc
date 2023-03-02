#include <console.hh>
#include <vector>

bool init(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {
    console::toggle_title();


    return true;
}

void make_black(console::Pixel & pixel) {
    pixel = console::Pixel(console::col::FG::BLACK, console::col::BG::BLACK);
}

bool Update(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y, float deltatime) {

    console::grid::for_each_0(pixels, X, Y, make_black);
    for(std::size_t x = 1; x < X; x++){
        console::grid::at_2D(pixels, x, 0, X) = console::Pixel(console::col::FG::WHITE, console::col::BG::BLACK,'-');
    }
    return true;

}

int main() {
    if(!console::init())
        return 0;
    console::set_init_callback(init);


    console::set_update_callback(Update);

    console::run();
    return console::exit();
}
