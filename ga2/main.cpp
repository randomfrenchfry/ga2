#include <iostream>
using namespace std;

//Parent Class
class Player{
private:
    int number;
    int age;
    int minutes;
    bool bench; //on bench or not
public:
    Player(int num,int age,int min,bool bench){
        this->number = num;
        this->age = age;
        this->minutes = min;
        this->bench = bench;
    }
    void setNumber(int num){this->number = num;}
    void setAge(int age){this->age = age;}
    void setMinutes(int min){this->minutes = min;}
    void setBool(bool bench){this->bench = bench;}
    int getNumber(){return number;}
    int getAge(){return age;}
    int getMinute(){return minutes;}
    bool getBench(){return bench;}
};

//Linked List
struct Node{
    int num,age,min;
    bool bench;
    Node* next;
};
class list{
private:
    Node*head;
    Node*tail;
public:
    list();
    void createPlayer(int,int,int,bool);
};

int main() {
    //Since the numbers of players are from 1 to 12
    
    return 0;
}

list::list() {
    head = NULL;
    tail = NULL;
}

void list::createPlayer(int num,int age, int min, bool bench){
    //Create a Node with the properties of the Player
    Player player(num,age,min,bench);
    Node*p = new Node;
    p->num = player.getNumber();
    p->age = player.getAge();
    p->min = player.getMinute();
    p->bench = player.getBench();
    
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

