#include <vector>
#include <stdexcept>
#pragma once

using namespace std;

template <typename T>
class GameSet {
    vector<T> _set;

public:
    GameSet(){
        _set = {};
    }
    /**
     * get GameSet<P> and convert the to GameSet<T>, complies only if
     * P and T inherits from same father (P.getType() == T.getType() && P.size() == T.size())
     * @tparam P - Object
     * @param set - Set of P objects
     */
    template<typename P> GameSet(GameSet<P>& set){
        _set ={};
        for(int i=0;i<set.size();i++){
            P& inSet = set.getAt(i);
            add(inSet.getType(),inSet.size());
        }
    }
    /**
     * Search object with type str
     * @param str
     * @return index in set
     */
    int search(string str){
        for(int i=0;i<_set.size();i++){
            if(_set[i].getType() == str){
                return i;
            }
        }
        return -1;
    }
    /**
     * add to Object T in set amount
     * @param str
     * @param amount
     */
    void add(string str,int amount){
        int result = search(str);
        if (result == -1) {
            _set.push_back(T(str,amount));
        } else {
            this->getAt(result).add(amount);
        }
    }
    /**
     * remove from Obejct T in set amount, if has 0 amount remove from set
     * @param str
     * @param amount
     */
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
    /**
     * get Object T in index i
     * @param i - index
     * @return Refernce to Object T
     */
    T& getAt(int i){
        return _set[i];
    }
    /**
     * @return Size of set
     */
    int size(){
        return _set.size();
    }
    /**
     * clear Set
     */
    void clear(){
        _set.clear();
    }
    /**
     * @return string of set
     */
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
    /**
     * check if set is contains in this
     * @param set
     * @return true or false
     */
    bool contains(GameSet<T>& set){
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
    /**
     * operator -= to remove set from this set
     * @param set
     * @return reference to this set
     */
    GameSet<T>& operator-=(GameSet<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            this->remove(inSet.getType(),inSet.size());
        }
        return *this;
    }
    /***
     * opertor += to add set to this set
     * @param set
     * @return reference to this set
     */
    GameSet<T>& operator+=(GameSet<T>& set){
        for(int i=0;i<set.size();i++){
            T& inSet = set.getAt(i);
            this->add(inSet.getType(),inSet.size());
        }
        return *this;
    }
    /**
     * operator << to print set
     * @param out - osStream
     * @param set - set to print
     * @return osStream
     */
    friend ostream& operator<<(ostream& out, GameSet<T> set){
        out << set.toString();
        return out;
    }
};
