#include "Record.h"

using std::string;

string Record::get_title() const {
    return title;
}

string Record::get_author() const {
    return author;
}

string Record::get_ISBN() const {
    return ISBN;
}

string Record::get_year() const {
    return year;
}

string Record::get_edition() const {
    return edition;
}

void Record::set_title( std::string newTitle ) {
    title = newTitle;
}

void Record::set_author( std::string newAuthor ) {
    author = newAuthor;
}

void Record::set_ISBN( std::string newISBN ) {
    ISBN = newISBN;
}

void Record::set_year( std::string newYear ) {
    year = newYear;
}

void Record::set_edition( std::string newEdition ) {
    edition = newEdition;
}

std::istream& operator>>(std::istream& is, Record& rec) {
    std::string curLine;
    
    getline( is, curLine );
    if ( curLine == "" ) getline(is, curLine);
    rec.set_title( curLine );
    
    getline(is, curLine);
    rec.set_author( curLine );
    
    getline(is, curLine);
    rec.set_ISBN( curLine );
    
    getline(is, curLine);
    rec.set_year( curLine );
    
    getline(is, curLine);
    rec.set_edition( curLine );
    
    return is;
}

std::ostream& operator<<(std::ostream& os, Record& rec) {
    os << rec.get_title() << std::endl;
    os << rec.get_author() << std::endl;
    os << rec.get_ISBN() << std::endl;
    os << rec.get_year() << std::endl;
    os << rec.get_edition() << std::endl;
    return os;
}

bool operator==(const Record& r1, const Record& r2) {
    if ( r1.get_title() == r2.get_title() )
        if ( r1.get_author() == r2.get_author() )
            if ( r1.get_ISBN() == r2.get_ISBN() )
                return true;
    return false;
}
