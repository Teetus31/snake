#include <console.hh>
#include <cstddef>
#include <vector>
#include <list>

typedef console::col::FG fg;
typedef console::col::BG bg;

struct block {
    std::size_t x, y;
};

struct fruit {
    block coord;
};

struct snake {
    std::list<block> segments;

    void draw(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t) {
        std::size_t cnt = 0;
        for(auto & segment : segments)
            if(cnt++ == 0)
                console::grid::at_2D(pixels, segment.x, segment.y, X) = console::Pixel(fg::WHITE, bg::BLACK, '0');
            else
                console::grid::at_2D(pixels, segment.x, segment.y, X) = console::Pixel(fg::WHITE, bg::BLACK, 'o');
    }

    void move(std::size_t direction) {
        if(direction == 0) { // up

        } else if(direction == 1) { // down

        } else if(direction == 2) { // left

        } else if(direction == 3) { // right

        }

    }
};

snake player;

std::size_t direction = 5;

void keys(char key) {
    if(key == 'w')
        direction = 0;

    else if(key == 's')
        direction = 1;

    else if(key == 'a')
        direction = 2;

    else if(key == 'd')
        direction = 3;

}

bool init(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {
    console::toggle_title();
    player.segments.push_back(block{X/2, Y/2});
    return true;
}

void make_black(console::Pixel & pixel) {
    pixel = console::Pixel(fg::BLACK, bg::BLACK);
}

void drawBorder(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {
    for(std::size_t x = 11; x < X - 10; x++)
        console::grid::at_2D(pixels, x, 0, X) = console::Pixel(fg::WHITE, bg::BLACK,'-');

    for(std::size_t y = 1; y < Y - 1; y++) {
        console::grid::at_2D(pixels, 10, y, X) = console::Pixel(fg::WHITE, bg::BLACK, '|');
        console::grid::at_2D(pixels, X - 10, y ,X) = console::Pixel(fg::WHITE, bg::BLACK,'|');
    }

    for(std::size_t x = X - 11; x >= 11; x--)
        console::grid::at_2D(pixels, x, Y-1, X)  = console::Pixel(fg::WHITE, bg::BLACK, '-') ;

    console::grid::at_2D(pixels, 10, 0, X) = console::Pixel(fg::WHITE, bg::BLACK, '#');
    console::grid::at_2D(pixels, X - 10, Y - 1, X) = console::Pixel(fg::WHITE, bg::BLACK, '#');
    console::grid::at_2D(pixels, 10, Y - 1, X) = console::Pixel(fg::WHITE, bg::BLACK, '#');
    console::grid::at_2D(pixels, X - 10, 0, X) = console::Pixel(fg::WHITE, bg::BLACK, '#');
}

bool Update(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y, float deltatime) {

    console::grid::for_each_0(pixels, X, Y, make_black);
    drawBorder(pixels, X, Y);
    player.draw(pixels, X, Y);
    player.move(direction);

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
