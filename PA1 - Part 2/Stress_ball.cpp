#include "Stress_ball.h"

Stress_ball::Stress_ball() {
    color = static_cast<Stress_ball_colors>(std::rand() % 4);
    size = static_cast<Stress_ball_sizes>(std::rand() % 3);
}

Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) {
    color = c;
    size = s;
}

Stress_ball_colors Stress_ball::get_color() const {
    return color;
}

Stress_ball_sizes Stress_ball::get_size() const {
    return size;
}

bool Stress_ball::operator==(const Stress_ball& sb) {
    return size == sb.get_size() && color == sb.get_color();
}

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb) {
    
    std::string color = "";
    std::string size = "";
    
    if ( sb.get_color() == Stress_ball_colors::red ) color = "red";
    else if ( sb.get_color() == Stress_ball_colors::blue ) color = "blue";
    else if ( sb.get_color() == Stress_ball_colors::yellow ) color = "yellow";
    else if ( sb.get_color() == Stress_ball_colors::green ) color = "green";
    
    if ( sb.get_size() == Stress_ball_sizes::small ) size = "small";
    else if ( sb.get_size() == Stress_ball_sizes::medium ) size = "medium";
    else if ( sb.get_size() == Stress_ball_sizes::large ) size = "large";
    
    o << "(" << color << ", " << size << ")";
    return o;
}
