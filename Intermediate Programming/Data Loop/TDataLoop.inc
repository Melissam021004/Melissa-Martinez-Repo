//#include "TDataLoop.h"
template< typename DataType >
TDataLoop<DataType>::TDataLoop(): start(nullptr), count(0) {}

template< typename DataType >
TDataLoop<DataType>::TDataLoop(const DataType & num): start(nullptr), count(0){
    _Node* temp = new _Node{num, nullptr, nullptr};
    start = temp;
    start -> next = start;
    start -> prev = start;
    count = 1;
} 

template< typename DataType >
TDataLoop<DataType>::TDataLoop(const TDataLoop & rhs): start(nullptr), count(0){
    //empty dl
    if(rhs.count == 0){
        count = 0;
        start = nullptr;
    }
    //non-empty rhs DL
    else{
        _Node* temp = rhs.start;
        do{
            (*this)+=(temp -> data);
            temp = temp -> next;
        } while(temp != rhs.start);
    }
}

template< typename DataType >
TDataLoop<DataType>& TDataLoop<DataType>::operator=(const TDataLoop & rhs){

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
    //non-empty rhs
    else{
        _Node* temp = rhs.start;
        do{
            (*this)+=(temp -> data);
            temp = temp -> next;
        } while(temp != rhs.start);
    }

    return *this;

}

template< typename DataType >
TDataLoop<DataType>::~TDataLoop(){
    clear();
}

template< typename DataType >
bool TDataLoop<DataType>::operator==(const TDataLoop & rhs) const{

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

template< typename DataType >
TDataLoop<DataType> & TDataLoop<DataType>::operator+=(const DataType & num){

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

template< typename DataType >
TDataLoop<DataType> TDataLoop<DataType>::operator+(const TDataLoop & rhs) const{
    TDataLoop out(*this);

    //empty rhs
    if(rhs.count == 0){
        return out;
    }

    //non-empty rhs, adding node by node
    _Node* temp = rhs.start;
    for(int i = 0; i < (int)rhs.count; i++){
        out += temp -> data;
        temp = temp -> next;
    }
    return out;
}

template< typename DataType >
TDataLoop<DataType> & TDataLoop<DataType>::operator^(int offset){

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

template< typename DataType >
TDataLoop<DataType> & TDataLoop<DataType>::splice(TDataLoop & rhs, size_t pos){
    
    //Accounting for pos being greater than count
    if(pos > count){
        pos = pos % (count);
    }

    //If rhs is an empty data loop
    if(rhs.count == 0){
        return *this;
    }
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

        //Getting the last node of the inserted dl
        _Node* last_rhs = rhs.start -> prev;

        lower_end -> next = rhs.start;
        rhs.start -> prev = lower_end;
        last_rhs -> next = upper_end;
        upper_end -> prev = last_rhs;

        count += rhs.count;

    }

    rhs.start = nullptr;
    rhs.count = 0;
    return *this;

}

template< typename U >
std::ostream & operator<<(std::ostream & os, const TDataLoop<U> & dl){
    if(dl.count == 0){
        os << ">no values<";
    }
    else{
        typename TDataLoop<U>::_Node* temp = dl.start;
        do{
            os << "-> " << temp->data << " <-";
            temp = temp -> next;
        } while(temp != dl.start);
    }

    return os;
}

template< typename DataType >
void TDataLoop<DataType>::clear(){

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