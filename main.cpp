#include <iostream>
using namespace std;

//Parent Class
class Player{
private:
    int number;
    int age;
    int minutes;
public:
    Player(int num,int age, int min){
        this->number = num;
        this->age = age;
        this->minutes = min;
    }
    void setNumber(int num){this->number = num;}
    void setAge(int age){this->age = age;}
    void setMinutes(int min){this->minutes = min;}
    int getNumber(){return number;}
    int getAge(){return age;}
    int getMinute(){return minutes;}
};
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
    int num,age,min;
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
    //Create a Node with the properties of the Player
    Player player(num,age,min);
    Node*p = new Node();
    p->num = player.getNumber();
    p->age = player.getAge();
    p->min = player.getMinute();

    if(head == NULL){ //If the player is the first Node
        head = p;
        tail = p;
        p = NULL;
    }
    else{            //If the list is not empty
        tail->next = p;
        tail = p;
    }
}


