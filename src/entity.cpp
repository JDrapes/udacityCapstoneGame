#include "entity.h"

int Entity::createAnimCycle(int row, int w, int h, int amount, int speed){
    animCycle temp;
    temp.row = row-1;
    temp.w = w;
    temp.h = h;
    temp.amount = amount;
    temp.speed = speed;
    temp.tick = 0;
    animations.push_back(temp);
    return animations.size()-1; 
}

void Entity::updateAnimation(){
setSource(animations[currentAnimation].w*animations[currentAnimation].tick, animations[currentAnimation].row*animations[currentAnimation].h, animations[currentAnimation].w, animations[currentAnimation].h);
    if(begin>animations[currentAnimation].speed){
        if(!rev)animations[currentAnimation].tick++;
        if(rev)animations[currentAnimation].tick--;
        begin=0;
    }
    begin++;
    if(animations[currentAnimation].tick >= animations[currentAnimation].amount) {animations[currentAnimation].tick=0;}
    if(animations[currentAnimation].tick <= 0 ) {
        if(nAb) {
            currentAnimation=newAnimation;
            nAb=0;
            rev=0;
        } else {
            animations[currentAnimation].tick=0;
        }
    }
}
