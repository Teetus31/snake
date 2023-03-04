#include <console.hh>
#include <cstddef>
#include <string>
#include <vector>
#include <list>

typedef console::col::FG fg;
typedef console::col::BG bg;

struct block {
    std::size_t x, y;
};

struct fruit {
    block coord;

    void draw(std::vector<console::Pixel> &pixels, std::size_t X, std::size_t Y) {
        console::grid::at_2D(pixels, coord.x, coord.y, X) = console::Pixel(fg::BRIGHT_RED, bg::BLACK, 'a');
    }
};

fruit apple;

bool dead = false;

struct snake {
    std::list<block> segments;

    std::size_t score = 0;

    void draw(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t) {
        std::size_t cnt = 0;
        for(auto segment = segments.rbegin(); segment != segments.rend(); segment++)
            if(cnt++ == 0)
                console::grid::at_2D(pixels, segment->x, segment->y, X) = console::Pixel(fg::WHITE, bg::BLACK, '0');
            else
                console::grid::at_2D(pixels, segment->x, segment->y, X) = console::Pixel(fg::WHITE, bg::BLACK, 'o');
    }

    void move(std::size_t direction, std::size_t X, std::size_t Y) {
        if (dead == true) {
            return ;
        }

        block first = *segments.rbegin();
        segments.push_back(first);

        if(direction == 0) { // up
            segments.rbegin()->y--;
        } else if(direction == 1) { // down
            segments.rbegin()->y++;
        } else if(direction == 2) { // left
            segments.rbegin()->x--;
        } else if(direction == 3) { // right
            segments.rbegin()->x++;
        }

        if(segments.rbegin()->x < 11 || segments.rbegin()->x > X - 11)
            dead = true;
        if(segments.rbegin()->y == 0 || segments.rbegin()->y > Y - 1)
            dead = true;

        if(segments.rbegin()->x == apple.coord.x && segments.rbegin()->y == apple.coord.y){
            score += 10;
            apple.coord.x = rand() % (X - 1);
            apple.coord.y = rand() % (Y - 2);
        }
        else {
            segments.pop_front();
        }

        for(auto poz = ++segments.rbegin(); poz != segments.rend(); ++poz) {
            if(poz->x == segments.rbegin()->x && poz->y == segments.rbegin()->y) {
                direction = 5;
                dead = true;
            }

        }


    }
};

snake player;

std::size_t direction = 5;

bool notexit = true;

std::size_t initial_value_x, initial_value_y;

void keys(char key) {
    if(dead == false) {

        if(key == 'w'){
            if(direction != 1)
            direction = 0;
        }
        else if(key == 's'){
            if(direction != 0)
            direction = 1;
        }
        else if(key == 'a'){
            if(direction != 3)
            direction = 2;
        }
        else if(key == 'd'){
            if(direction != 2)
            direction = 3;

        }
    }

    if(key == 'q')
        notexit = false;


    if( key == 'r') {
            player.segments.clear();
            player.segments.push_back(block{initial_value_x / 2, initial_value_y / 2});

            player.score = 0;

            apple.coord.x = rand() % (initial_value_x-10);
            apple.coord.y = rand() % (initial_value_y-10);

            dead = false;
    }

}

void death_screen(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {
    std::string_view line1 = "You are dead. Press 'r' key to restart";

    console::grid::set_string(
        pixels,
        line1,
        fg::BRIGHT_RED,
        bg::BLACK,
        console::col::INVERT::NO,
        console::col::BOLD::NO,
        console::col::ITALIC::NO,
        console::col::UNDERLINE::NO,
        console::col::STRIKETHROUGH::NO,
        X / 2 - line1.length() / 2,
        Y / 2,
        X
        );
}

void score(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {

    console::grid::set_string (
        pixels,
        "Score: " + std::to_string(player.score),
        fg::WHITE,
        bg::BLACK,
        console::col::INVERT::NO,
        console::col::BOLD::NO,
        console::col::ITALIC::NO,
        console::col::UNDERLINE::NO,
        console::col::STRIKETHROUGH::NO,
        3,
        0,
        X
    );
}

bool init(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y) {
    console::toggle_title();
    player.segments.push_back(block{X/2, Y/2});

    apple.coord.x = 40;
    apple.coord.y = 25;

    return true;
}

void make_black(console::Pixel & pixel) {
    pixel = console::Pixel(fg::BLACK, bg::BLACK); }

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

float acumulator = 0;
float tickrate = 1.0f / 10.0f;


bool Update(std::vector<console::Pixel> & pixels, std::size_t X, std::size_t Y, float deltatime) {

    initial_value_x = X;
    initial_value_y = Y;
    console::grid::for_each_0(pixels, X, Y, make_black);
    drawBorder(pixels, X, Y);
    player.draw(pixels, X, Y);

    if(dead) {
        direction = 5;
        death_screen(pixels, X, Y);
    }

    acumulator = acumulator + deltatime;

    while(acumulator >= tickrate) {
        player.move(direction, X, Y);


        acumulator = acumulator - tickrate;
    }

    apple.draw(pixels, X, Y);
    score(pixels, X, Y);

    return notexit;
}

int main() {
    if(!console::init())
        return 0;

    console::set_init_callback(init);

    console::set_update_callback(Update);

    console::set_key_callback(keys);

    console::run();

    return console::exit();
}
