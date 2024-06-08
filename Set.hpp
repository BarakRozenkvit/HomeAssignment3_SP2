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
    bool contains(Set<T>& set){
        for(int i=0;i< set.size();i++){
            T& inSet = set.getAt(i);
            int result = this->search(inSet.getType());
            if(result == -1){return false;}
            T& inThis = this->getAt(result);
            if(inThis.size() < inSet.size()){
                return false;
            }
        }
        return true;
    }

    Set<T>& operator-=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            this->remove(inSet.getType(),inSet.size());
        }
        return *this;
    }
    Set<T>& operator+=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            this->add(inSet.getType(),inSet.size());
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out,Set<T> set){
        out << set.toString();
        return out;
    }
};
