#include "Library.h"
#include <fstream>

std::vector<Record> Library::search(std::string title) {
    std::vector<Record> matchingBooks = vector<Record>();
    
    int firstLetter = std::toupper( title.at(0) ) - 65;
    DLList<Record> &dlist = book_db.at( firstLetter );
    DLListNode<Record> *node = dlist.first_node();
    
    while ( node != ( dlist.after_last_node() ) ){
        if ( node->obj.get_title() == title )
            matchingBooks.push_back(node->obj);
        node = node->next;
    }
    
    return matchingBooks;
}

int Library::import_database(std::string filename) {
    int importCount = 0;
    Record rec;
    
    std::ifstream file( filename );
    
    while ( file >> rec ) {
        //int firstLetter = std::toupper( rec.get_title().at(0) ) - 65;
        
        if ( add_record( rec ) ) importCount++;
        
        //book_db.at( firstLetter ).insert_last( rec );
        
    }
    return importCount;
}

int Library::export_database(std::string filename) {
    int exportCount = 0;
    
    std::ofstream file( filename );
    
    for ( DLList<Record> &dlist : book_db ) {
        DLListNode<Record> *node = dlist.first_node();
        while ( node != ( dlist.after_last_node() ) ){
            file << node->obj;
            file << endl;
            node = node->next;
            exportCount++;
        }
    }
    return exportCount;
}

void Library::print_database() {
    for ( DLList<Record> &dlist : book_db ) {
        if ( dlist.is_empty() ) {
            continue;
        }
        DLListNode<Record> *node = dlist.first_node();
        while ( node != ( dlist.after_last_node() ) ){
            cout << node->obj << endl;
            node = node->next;
        }
    }
}

bool Library::add_record(Record book) {
    int firstLetter = std::toupper( book.get_title().at(0) ) - 65;
    
    DLList<Record> &dlist = book_db.at( firstLetter );
    
    if ( dlist.is_empty() ) {
        dlist.insert_first( book );
        return true;
    }
    
    DLListNode<Record> *node = dlist.first_node();
    
    while ( node != dlist.after_last_node() ) {
        if ( book.get_title().compare( node->obj.get_title() ) > 0 ) { // Book is after current book
            node = node->next;
        }
        else if ( book.get_title().compare( node->obj.get_title() ) < 0 ) { // Book is before current book
            dlist.insert_before( *node, book );
            return true;
        }
        else if ( book.get_title().compare( node->obj.get_title() ) == 0 ) { // Book title is the same
            if ( book == node->obj ) return false;
            
            if ( book.get_author().compare( node->obj.get_author() ) < 0 ) {
                dlist.insert_before( *node, book );
                return true;
            } else if ( book.get_author().compare( node->obj.get_author() ) > 0 ) {
                dlist.insert_after( *node, book );
                return true;
            } else if ( book.get_author().compare( node->obj.get_author() ) == 0 ) {
                if ( book.get_ISBN().compare( node->obj.get_ISBN() ) < 0 ) {
                    dlist.insert_before( *node, book );
                    return true;
                } else if ( book.get_ISBN().compare( node->obj.get_ISBN() ) > 0 ) {
                    dlist.insert_after( *node, book );
                    return true;
                }
            }
        }
    }
    
    if ( node == dlist.after_last_node() ) {
        dlist.insert_last( book );
        return true;
    }
    return false;
}

void Library::remove_record(Record book) {
    int firstLetter = std::toupper( book.get_title().at(0) ) - 65;

    DLList<Record> &dlist = book_db.at( firstLetter );
    
    DLListNode<Record> *node = dlist.first_node();
    
    while ( node != dlist.after_last_node() ) {
        if ( book == node->obj ) {
            node = node->next;
            dlist.remove_before( *node );
            return;
        } else {
            node = node->next;
        }
    }
}

char Library::prompt_yes_no() {
    char choice;
    cout << "Yes or No? ";
    cin >> choice;
    cin.ignore();
    choice = std::toupper(choice);
    if ( choice != 'Y' and choice != 'N') prompt_yes_no();
    return choice;
}

int Library::prompt_menu(std::vector<std::string> vec) {
    int choice = 0;
    for ( std::string option : vec ) {
        std::cout << ++choice << ". " << option << std::endl;
    }
    cout << "Select an option: ";
    cin >> choice;
    cin.ignore();
    return choice-1;
}

Record Library::prompt_record() {
    Record newRecord;
    newRecord.set_title(prompt_title());
    newRecord.set_author(prompt_string("Enter the book author: "));
    newRecord.set_ISBN(prompt_string("Enter the book ISBN: "));
    newRecord.set_year(prompt_string("Enter the book's publishing year: "));
    newRecord.set_edition(prompt_string("Enter the book's edition: "));
    return newRecord;
}

std::string Library::prompt_title() {
    std::string title;
    
    std::cout << "Enter a book title: " << std::endl;
    getline( cin, title );
    
    return title;
}

std::string Library::prompt_string(std::string prompt) {
    std::string input;
    std::cout << prompt << std::endl;
    getline( cin, input );
    return input;
}
