/**
 * In this file, implement the methods from Jeans.h. The implementation is identical to Stress_ball
 * This file needs to be uploaded to Mimir
 */ 
#include "Jeans.h"

Jeans::Jeans() {
    color = static_cast<Jeans_colors>(std::rand() % 4);
    size = static_cast<Jeans_sizes>(std::rand() % 3);
}

Jeans::Jeans(Jeans_colors c, Jeans_sizes s) {
    color = c;
    size = s;
}

Jeans_colors Jeans::get_color() const {
    return color;
}

Jeans_sizes Jeans::get_size() const {
    return size;
}

bool Jeans::operator==(const Jeans& sb) {
    if ( color == sb.get_color() && size == sb.get_size() ) return true;
    return false;
}


ostream& operator<<(ostream& o, const Jeans& sb) {
    std::string color = "";
    std::string size = "";
    
    if ( sb.get_color() == Jeans_colors::white ) color = "white";
    else if ( sb.get_color() == Jeans_colors::black ) color = "black";
    else if ( sb.get_color() == Jeans_colors::blue ) color = "blue";
    else if ( sb.get_color() == Jeans_colors::grey ) color = "grey";
    
    if ( sb.get_size() == Jeans_sizes::small ) size = "small";
    else if ( sb.get_size() == Jeans_sizes::medium ) size = "medium";
    else if ( sb.get_size() == Jeans_sizes::large ) size = "large";
    else if ( sb.get_size() == Jeans_sizes::xlarge ) size = "xlarge";
    
    o << "(" << color << ", " << size << ")";
    return o;
}
