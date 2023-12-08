#include "Enemy.hpp"

#include "Knight.hpp"

Enemy::Enemy(float p_x , float p_y ,SDL_Texture* p_tex,int h,int p):Entity(p_x,p_y,p_tex){
    health = h;
    pwr = p;
}

void Enemy::attackKnight(Knight& knight) {
    int random = rand() % 10;
    
    if (random >= 0 && random <= 3){
        knight.decreasehealth(2*pwr); //Fireball
        std::cout<<"Fireball"<<std::endl;
        // need to implement animation
    }
    else if (random > 3 && random <= 6){
        knight.decreasehealth(3*pwr); //Lightning Strike
        //need to implement animation
        std::cout<<"Lightning"<<std::endl;
    }
    else if (random > 6){
        std::cout<<"healed"<<std::endl;
        health += 7;
    }
    
}

void  Enemy::decreasehealth(int dmg){
    health -= dmg;
}

int Enemy::gethealth(){
    return health;
}