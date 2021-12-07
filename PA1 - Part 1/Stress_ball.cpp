#include <iostream>

enum Stress_ball_colors {
    red, blue, yellow, green
};

enum Stress_ball_sizes {
    small, medium, large
};

class Stress_ball {
    public:
        Stress_ball();
        Stress_ball(Stress_ball_colors c, Stress_ball_sizes s);
        Stress_ball_colors get_color() const;
        Stress_ball_sizes get_size() const;
        bool operator==(const Stress_ball& sb);
    private:
        Stress_ball_colors color;
        Stress_ball_sizes size;
};

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
    
    if ( sb.get_color() == red ) color = "red";
    else if ( sb.get_color() == blue ) color = "blue";
    else if ( sb.get_color() == yellow ) color = "yellow";
    else if ( sb.get_color() == green ) color = "green";
    
    if ( sb.get_size() == small ) size = "small";
    else if ( sb.get_size() == medium ) size = "medium";
    else if ( sb.get_size() == large ) size = "large";
    
    o << "(" << color << ", " << size << ")";
    return o;
}

int main() {
    Stress_ball sbOne(red, large);
    Stress_ball sbTwo;
    std::cout << sbOne << std::endl;
    std::cout << sbTwo << std::endl;
    
    std::cout << std::boolalpha << (sbOne == sbTwo) << std::endl;
    return 1;
}
