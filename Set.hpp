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
            this->getAt(result).remove(amount);
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
    Set<T>& operator-=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            int res = this->search(inSet.getType());
            T& inThis = this->getAt(res);
            inThis.remove(inSet.size());
        }
        return *this;
    }
    Set<T>& operator+=(Set<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            int res = this->search(inSet.getType());
            T& inThis = this->getAt(res);
            inThis.add(inSet.size());
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out,Set<T>& set){
        string res ="";
        for(int i=0;i<set.size();i++){
            res += "[";
            res += set.getAt(i).getType();
            res += to_string(set.getAt(i).size());
            res += "],";
        }
        out << res;
        return out;
    }
};
