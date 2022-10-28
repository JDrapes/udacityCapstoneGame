#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "object.h"

//Extends object
class Entity : public Object {
public:
Entity() {rev=0;}
    void setHealth(int h){health=h;}
    void setMaxHealth(int h){maxHealth=h;}
    int getHealth() const {return health;}
    int getMaxHealth() const {return maxHealth;}
    int createAnimCycle(int row, int w, int h, int amount, int speed);
    void setCurrentAnimation(int c) {begin= 0; currentAnimation = c;}
    int getCurrrentAnimation() const {return currentAnimation;}
    void updateAnimation();
    void reverse(bool r) {rev=r;}
    void reverse(bool r, int nA) {rev=r; nAb=1; nA=newAnimation;}
private:
    int health, maxHealth;
    struct animCycle{
        int row;
        int w;
        int h;
        int amount;
        int speed; 
        int tick;
    };
    vector<animCycle> animations;
    int currentAnimation;
    int begin;
    bool rev, nAb;
    int newAnimation;
};


#endif //ENTITY_H