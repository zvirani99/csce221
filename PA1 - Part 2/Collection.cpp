#include "Collection.h"
#include "Stress_ball.h"



Collection::Collection() {
    array = nullptr;
    size = 0;
    capacity = 0;
}

Collection::Collection( int c ) {
    size = 0;
    capacity = c;
    array = new Stress_ball[capacity];
}

Collection::Collection( const Collection &c ) {
    size = c.size;
    capacity = c.capacity;
    array = new Stress_ball[capacity];
    for ( int i = 0; i < size; i++ ) {
        array[i] = c.array[i];
    }
}

Collection& Collection::operator=(const Collection& c) {
    if ( this != &c ) {
        if ( array != nullptr ) delete [] array;
        size = c.size;
        capacity = c.capacity;
        array = new Stress_ball[capacity];
        for ( int i = 0; i < size; i++ ) {
            array[i] = c.array[i];
        }
    }
    return *this;
}

Collection::~Collection() {
    make_empty();
}

Collection::Collection(Collection&& c) {
    size = c.size;
    capacity = c.capacity;
    array = c.array;
    c.array = nullptr;
    c.size = 0;
    c.capacity = 0;
}

Collection& Collection::operator=(Collection&& c) {
    size = c.size;
    capacity = c.capacity;
    delete [] array;
    array = c.array;
    c.array = nullptr;
    c.size = 0;
    c.capacity = 0;
    
    return *this;
}

void Collection::insert_item(const Stress_ball& sb) {
    if ( array == nullptr ) {
        array = new Stress_ball[1];
        size = 0;
        capacity = 1;
    }
    if ( size == capacity ) resize();
    array[size] = sb;
    size++;
}

void Collection::resize() {
    Stress_ball *newArray = new Stress_ball[capacity*2];
    for ( int i = 0; i < size; i++ ) {
        newArray[i] = array[i];
    }
    delete [] array;
    array = newArray;
    capacity = capacity * 2;
}

bool Collection::contains(const Stress_ball& sb) const {
    for ( int i = 0; i < size; i++ ) {
        if ( array[i] == sb ) return true;
    }
    return false;
}

Stress_ball Collection::remove_any_item() {
    if ( size == 0 ) throw "Empty Collection";
    
    int idx = rand() % size;
    Stress_ball sb = array[idx];
    for ( int i = idx + 1; i < size; i++ ) {
        array[i-1] = array[i];
    }
    size--;
    return sb;
}

void Collection::remove_this_item(const Stress_ball& sb) {
    if ( size == 0 ) throw "Empty Collection";
    
    for ( int i = 0; i < size; i++ ) {
        if ( array[i] == sb ) {
            for ( int j = i + 1; j < size; j++ ) {
                array[j-1] = array[j];
            }
            size--;
            break;
        }
    }
    
}

void Collection::make_empty() {
    if ( array != nullptr ) {
        delete [] array;
        size = 0;
        capacity = 0;
    }
}

bool Collection::is_empty() const {
    return size == 0;
}

int Collection::total_items() const {
    return size;
}

int Collection::total_items(Stress_ball_sizes s) const {
    int count = 0;
    for ( int i = 0; i < size; i++ ) {
        if ( array[i].get_size() == s ) count++;
    }
    return count;
}

int Collection::total_items(Stress_ball_colors t) const {
    int count = 0;
    for ( int i = 0; i < size; i++ ) {
        if ( array[i].get_color() == t ) count++;
    }
    return count;
}

void Collection::print_items() const {
    for ( int i = 0; i < size; i++ ) {
        std::string size = "";
        std::string color = "";
        switch(array[i].get_size()) {
            case Stress_ball_sizes::small:
                size = "small";
                break;
            case Stress_ball_sizes::medium:
                size = "medium";
                break;
            case Stress_ball_sizes::large:
                size = "large";
                break;
        }
        switch(array[i].get_color()) {
            case Stress_ball_colors::red:
                color = "red";
                break;
            case Stress_ball_colors::blue:
                color = "blue";
                break;
            case Stress_ball_colors::green:
                color = "green";
                break;
            case Stress_ball_colors::yellow:
                color = "yellow";
                break;
        }
        cout << "(" << color << ", " << size << ")" << endl;
    }
}

Stress_ball& Collection::operator[](int i) {
    return array[i];
}

const Stress_ball& Collection::operator[](int i) const {
    return array[i];
}

istream& operator>>(istream& is, Collection& c) {
    while( !is.eof() ) {
        std::string colorString = "";
        std::string sizeString = "";
        Stress_ball_colors color;
        Stress_ball_sizes size;
        is >> colorString >> sizeString;
        if ( colorString == "red" ) color = Stress_ball_colors::red;
        else if ( colorString == "blue" ) color = Stress_ball_colors::blue;
        else if ( colorString == "green" ) color = Stress_ball_colors::green;
        else if ( colorString == "yellow" ) color = Stress_ball_colors::yellow;
        else color = Stress_ball_colors::red;
        
        if ( sizeString == "small" ) size = Stress_ball_sizes::small;
        else if ( sizeString == "medium" ) size = Stress_ball_sizes::medium;
        else if ( sizeString == "large" ) size = Stress_ball_sizes::large;
        else size = Stress_ball_sizes::small;
        
        Stress_ball sb(color, size);
        c.insert_item(sb);
    }
    return is;
}

ostream& operator<<(ostream& os, const Collection& c) {
    for ( int i = 0; i < c.total_items(); i++ ) {
        std::string size = "";
        std::string color = "";
        switch(c[i].get_size()) {
            case Stress_ball_sizes::small:
                size = "small";
                break;
            case Stress_ball_sizes::medium:
                size = "medium";
                break;
            case Stress_ball_sizes::large:
                size = "large";
                break;
        }
        switch(c[i].get_color()) {
            case Stress_ball_colors::red:
                color = "red";
                break;
            case Stress_ball_colors::blue:
                color = "blue";
                break;
            case Stress_ball_colors::green:
                color = "green";
                break;
            case Stress_ball_colors::yellow:
                color = "yellow";
                break;
        }
        os << "(" << color << ", " << size << ")" << endl;
    }
    return os;
}

Collection make_union(const Collection& c1, const Collection& c2) {
    Collection c3(1);
    for ( int i = 0; i < c1.total_items(); i++ ) {
        c3.insert_item(c1[i]);
    }
    for ( int i = 0; i < c2.total_items(); i++ ) {
        c3.insert_item(c2[i]);
    }
    return c3;
}

void swap(Collection& c1, Collection& c2) {
    Collection temp = std::move(c1);
    c1 = std::move(c2);
    c2 = std::move(temp);
    temp.make_empty(); 
}

void sort_by_size(Collection& c, Sort_choice sort) {
    switch(sort) {
        case Sort_choice::bubble_sort:
            for (int i = 0; i < c.total_items()-1; i++) {
                for (int j = 0; j < c.total_items()-i-1; j++) {
                    if (c[j].get_size() > c[j+1].get_size()) {
                        Stress_ball temp = c[j];
                        c[j] = c[j+1];
                        c[j+1] = temp;
                    }
                }
            }
        case Sort_choice::insertion_sort:
            for (int i = 1; i < c.total_items(); i++) {
                Stress_ball key = c[i];
                int j = i - 1;
          
                while (j >= 0 && c[j].get_size() > key.get_size())
                {
                    c[j + 1] = c[j];
                    j = j - 1;
                }
                c[j + 1] = key;
            }
        case Sort_choice::selection_sort:
            for (int i = 0; i < c.total_items()-1; i++)
            {
                int min_idx = i;
                for (int j = i+1; j < c.total_items(); j++)
                if (c[j].get_size() < c[min_idx].get_size())
                    min_idx = j;
          
                Stress_ball temp = c[min_idx];
                c[min_idx] = c[i];
                c[i] = temp;
            }
    }
}

