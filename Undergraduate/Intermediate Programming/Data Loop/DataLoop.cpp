#include "DataLoop.h"

DataLoop::DataLoop(): start(nullptr), count(0) {}

DataLoop::DataLoop(const int & num): start(nullptr), count(0){
    _Node* temp = new _Node{num, nullptr, nullptr};
    start = temp;
    //self-point
    start -> next = start;
    start -> prev = start;
    count = 1;
} 

DataLoop::DataLoop(const DataLoop & rhs): start(nullptr), count(0){
    //empty rhs
    if(rhs.count == 0){
        count = 0;
        start = nullptr;
    }
    //non-empty rhs
    else{
        _Node* temp = rhs.start;
        do{
            (*this)+=(temp -> data);
            temp = temp -> next;
        } while(temp != rhs.start);
    }
}

DataLoop& DataLoop::operator=(const DataLoop & rhs){

    //Self-assignment
    if (this == &rhs){
        return *this;
    }

    //Clearing current dataloop values
    clear();

    //Empty rhs
    if(rhs.count == 0){
        count = 0;
        start = nullptr;
    }
    //Non-empty rhs
    else{
        _Node* temp = rhs.start;
        do{
            (*this)+=(temp -> data);
            temp = temp -> next;
        } while(temp != rhs.start);
    }

    return *this;

}

DataLoop::~DataLoop(){
    clear();
}

bool DataLoop::operator==(const DataLoop & rhs) const{

    //False if counts are not the same
    if(count != rhs.count){
        return false;
    }

    _Node* left = start;
    _Node* right = rhs.start;

    //Checking node by node
    for(int i = 0; i < (int)count; i++){
        if(left -> data != right -> data){
            return false;
        }
        left = left -> next;
        right = right -> next;
    }

    return true;
}

DataLoop & DataLoop::operator+=(const int & num){

    _Node* newn = new _Node{num, nullptr, nullptr};

    //First element of the dataloop
    if(count == 0){
        start = newn;
        start -> next = start;
        start -> prev = start;
    }
    //Adding to the end
    else{
        _Node* last = start -> prev;
        last -> next = newn;
        newn -> prev = last;
        newn -> next = start;
        start -> prev = newn;
    }

    count++;
    return *this;

}

DataLoop DataLoop::operator+(const DataLoop & rhs) const{
    //Copying implicit DL into the output DL
    DataLoop out(*this);

    //No effect if rhs is empty
    if(rhs.count == 0){
        return out;
    }

    //Adding the rhs node by node
    _Node* temp = rhs.start;
    for(int i = 0; i < (int)rhs.count; i++){
        out += temp -> data;
        temp = temp -> next;
    }
    return out;
}

DataLoop & DataLoop::operator^(int offset){

    //no effect
    if(count == 0 || count == 1 || offset == 0){
        return *this;
    }

    _Node* new_start;

    //Positive offset
    if(offset > 0){
        new_start = start;
        for(int i = 0; i < offset; i++){
            new_start = new_start -> next;
        }
    }
    //Negative offset
    else{
        new_start = start;
        for(int i = offset; i < 0; i++){
            new_start = new_start -> prev;
        }
    }

    start = new_start;

    return *this;
}

DataLoop & DataLoop::splice(DataLoop & rhs, size_t pos){
    
    //Accounting for pos being greater than count
    if(pos > count){
        pos = pos % (count);
    }

    //If rhs is an empty data loop
    if(rhs.count == 0){
        return *this;
    }
    //If implicit DL is empty
    if(count == 0){
        *this = rhs;
        return *this;
    }
    
    //Inserted before or after the current loop
    if(pos == 0 || pos == count){
        _Node* last_rhs = rhs.start -> prev;
        _Node* last_cur = start -> prev;

        last_rhs->next = start;
        start -> prev = last_rhs;
        last_cur -> next = rhs.start;
        rhs.start -> prev = last_cur;

        //Adjusting start if inserted before
        if(pos == 0){
            start = rhs.start;
        }

        count += rhs.count;

    }
    //inserted in the middle of the current loop
    else{

        //Finding the lower end (before dl insertion) and upper end (after dl insertion)
        _Node* lower_end = start;
        for(int i = 1; i < (int)pos; i++){
            lower_end = lower_end -> next;
        }
        _Node* upper_end = lower_end -> next;

        _Node* last_rhs = rhs.start -> prev;

        lower_end -> next = rhs.start;
        rhs.start -> prev = lower_end;
        last_rhs -> next = upper_end;
        upper_end -> prev = last_rhs;

        count += rhs.count;

    }

    //Clearing rhs
    rhs.start = nullptr;
    rhs.count = 0;
    return *this;

}

std::ostream & operator<<(std::ostream & os, const DataLoop & dl){

    //DL is empty
    if(dl.count == 0){
        os << ">no values<";
    }
    else{
        DataLoop::_Node* temp = dl.start;
        //Loops through the data loop to print each data point
        do{
            os << "-> " << temp->data << " <-";
            temp = temp -> next;
        } while(temp != dl.start);
    }

    return os;
}

void DataLoop::clear(){

    _Node* cur = start;
    _Node* temp = nullptr;

    //deleting node by node
    for(int i = 0; i < (int)count; i++){
        temp = cur;
        cur = cur -> next;
        delete temp;        
    }

    //resetting instance vars
    start = nullptr;
    count = 0;
}