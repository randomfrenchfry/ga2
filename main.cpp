#include <iostream>
using namespace std;

//Parent Class
class Player{
private:
    int number;
    int age;
    int minutes;
public:
    Player(int num,int age, int min);
    void setNumber(int num){this->number = num;}
    void setAge(int age){this->age = age;}
    void setMinutes(int min){this->minutes = min;}
    int getNumber(){return number;}
    int getAge(){return age;}
};

Player::Player(int num, int age, int min) {
    this->number = num;
    this->age = age;
    this->minutes = min;
}
//Child Class
class courtPlayer: public Player{
private:
public:
};
//Child Class
class BenchPlayer: public Player{

};

//Linked List
struct Node{
    Player data;
    Node* next;
};
class list{
private:
    Node*head;
    Node*tail;
public:
    list();
    void createPlayer(int,int,int);
};

int main() {

    return 0;
}

list::list() {
    head = NULL;
    tail = NULL;
}

void list::createPlayer(int num,int age, int min){
    Player
    Node*p = new Node;
    p->data.setNumber(num);

    if(head == NULL){
        head = p;
        tail = p;
        p = NULL;
    }
}
