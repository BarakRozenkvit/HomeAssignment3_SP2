#include <vector>
#pragma once

using namespace std;

template <typename T>
class Set {
    vector<T> _set;

public:
    Set(){
        _set = {};
    }
    int search(string str){
        for(int i=0;i<_set.size();i++){
            if(_set[i].getType() == str){
                return i;
            }
        }
        return -1;
    }
    void add(string str,int amount){
        int result = search(str);
        if (result == -1) {
            _set.push_back(T(str,amount));
        } else {
            this->getAt(result).add(amount);
        }
    }
    void remove(string str,int amount){
        int result = search(str);
        if(result > -1){
            T& res = this->getAt(result);
            if(res.size() == amount){
                vector<T> cpy = {};
                for(int i=0;i<this->size();i++){
                    if(i!=result){
                        cpy.push_back(this->getAt(i));
                    }
                }
                _set = cpy;
            }
            else {
                this->getAt(result).remove(amount);
            }
        }
    }
    T& getAt(int i){
        return _set[i];
    }
    int size(){
        return _set.size();
    }
    void clear(){
        _set.clear();
    }
    int total(){
        int res = 0;
        for(int i=0;i<size();i++){
            res += getAt(i).size();
        }
        return res;
    }
    string toString(){
        string res ="";
        for(int i=0;i< this->size();i++){
            res += "[";
            res += this->getAt(i).getType();
            res += ": ";
            res += to_string(this->getAt(i).size());
            res += "],";
        }
        return res;
    }

    Set<T>& operator-=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            int res = this->search(inSet.getType());
            if(res == -1){
                return *this;
            }
            T& inThis = this->getAt(res);
            inThis.remove(inSet.size());
        }
        return *this;
    }
    Set<T>& operator+=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            int res = this->search(inSet.getType());
            if(res == -1){
                this->add(inSet.getType(),inSet.size());
            }
            else {
                T &inThis = this->getAt(res);
                inThis.add(inSet.size());
            }
        }
        return *this;
    }
    Set<T>& operator==(Set<T>& set){}

    bool operator>(Set<T>& set){
        if(this->size() < set.size()){
            return false;
        }
        for(int i=0;i<this->size();i++){
            T& inThis = this->getAt(i);
            int res = set.search(inThis.getType());
            if(res == -1){ continue;}
            T& inSet = set.getAt(res);
            if(inThis.size() < inSet.size()){
                return false;
            }

        }
        return true;
    }

    friend ostream& operator<<(ostream& out,Set<T> set){
        out << set.toString();
        return out;
    }
};
