/**
 * There is no Collection.cpp for this assignment.
 * Move all the functions from Collection.cpp to this file except Operator>> 
 * Covert the Collection class to a templated form. (Stress_ball should be replaced with typename "Obj".
 *   Stress_ball_colors and Stress_ball_sizes should be replaced with typename "F2").
 * This file has to be uploaded to mimir.
 */

#ifndef Collection_H
#define Collection_H
#include <string>
#include <iostream>
using namespace std;

enum class Sort_choice{bubble_sort, insertion_sort, selection_sort};

class Empty_Collection{};

template <class Obj, class F1, class F2>
class Collection {
    Obj* array;
    int size;
    int capacity;
    void resize() {
        Obj* newArray = new Obj[capacity*2];
        for ( int i = 0; i < size; i++ ) {
            newArray[i] = array[i];
        }
        delete [] array;
        array = newArray;
        capacity = capacity * 2;
    };
public:
    Collection() {
        array = nullptr;
        size = 0;
        capacity = 0;
    };
    Collection(int c) {
        size = 0;
        capacity = c;
        array = new Obj[capacity];
    };
    Collection(const Collection& c) {
        size = c.size;
        capacity = c.capacity;
        array = new Obj[capacity];
        for ( int i = 0; i < size; i++ ) {
            array[i] = c.array[i];
        }
    };
    Collection& operator=(const Collection& c) {
        if ( this != &c ) {
            if ( array != nullptr ) delete [] array;
            size = c.size;
            capacity = c.capacity;
            array = new Obj[capacity];
            for ( int i = 0; i < size; i++ ) {
                array[i] = c.array[i];
            }
        }
        return *this;
    };
    ~Collection() {
        make_empty();
    };
    Collection(Collection&& c) {
        size = c.size;
        capacity = c.capacity;
        array = c.array;
        c.array = nullptr;
        c.size = 0;
        c.capacity = 0;
    };
    Collection& operator=(Collection&& c) {
        size = c.size;
        capacity = c.capacity;
        delete [] array;
        array = c.array;
        c.array = nullptr;
        c.size = 0;
        c.capacity = 0;
        
        return *this;
    };
    void insert_item(const Obj& sb) {
        if ( array == nullptr ) {
            array = new Obj[1];
            size = 0;
            capacity = 1;
        }
        if ( size == capacity ) resize();
        array[size] = sb;
        size++;
    };
    bool contains(const Obj& sb) const {
        for ( int i = 0; i < size; i++ ) {
            if ( array[i] == sb ) return true;
        }
        return false;
    };
    Obj remove_any_item() {
        if ( size == 0 ) throw "Empty Collection";
        
        int idx = rand() % size;
        Obj sb = array[idx];
        for ( int i = idx + 1; i < size; i++ ) {
            array[i-1] = array[i];
        }
        size--;
        return sb;
    };
    void remove_this_item(const Obj& sb) {
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
    };
    void make_empty() {
        if ( array != nullptr ) {
            delete [] array;
            size = 0;
            capacity = 0;
        }
    };
    bool is_empty() const {
        return size == 0;
    };
    int total_items() const {
        return size;
    };
    int total_items(F2 s) const {
        int count = 0;
        for ( int i = 0; i < size; i++ ) {
            if ( array[i].get_size() == s ) count++;
        }
        return count;
    };
    int total_items(F1 c) const {
        int count = 0;
        for ( int i = 0; i < size; i++ ) {
            if ( array[i].get_color() == c ) count++;
        }
        return count;
    };
    void print_items() const {
        for ( int i = 0; i < size; i++ ) {
            cout << array[i] << endl;
        }
    };
    Obj& operator[](int i) {
        return array[i];
    };
    const Obj& operator[](int i) const {
        return array[i];
    };
};

template <class Obj, class F1, class F2>
ostream& operator<<(ostream& os, const Collection<Obj, F1, F2>& c) {
    for ( int i = 0; i < c.total_items(); i++ ) {
        os << c[i] << endl;
    }
    return os;
}

template <class Obj, class F1, class F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2) {
    Collection<Obj, F1, F2> c3(1);
    for ( int i = 0; i < c1.total_items(); i++ ) {
        c3.insert_item(c1[i]);
    }
    for ( int i = 0; i < c2.total_items(); i++ ) {
        c3.insert_item(c2[i]);
    }
    return c3;
}

template <class Obj, class F1, class F2>
void swap(Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2) {
    Collection<Obj, F1, F2> temp = std::move(c1);
    c1 = std::move(c2);
    c2 = std::move(temp);
    temp.make_empty();
}

template <class Obj, class F1, class F2>
void sort_by_size(Collection<Obj, F1, F2>& c, Sort_choice sort) {
    switch(sort) {
        case Sort_choice::bubble_sort:
            for (int i = 0; i < c.total_items()-1; i++) {
                for (int j = 0; j < c.total_items()-i-1; j++) {
                    if (c[j].get_size() > c[j+1].get_size()) {
                        Obj temp = c[j];
                        c[j] = c[j+1];
                        c[j+1] = temp;
                    }
                }
            }
        case Sort_choice::insertion_sort:
            for (int i = 1; i < c.total_items(); i++) {
                Obj key = c[i];
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
          
                Obj temp = c[min_idx];
                c[min_idx] = c[i];
                c[i] = temp;
            }
    }
}

#endif
