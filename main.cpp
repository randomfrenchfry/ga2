#include <iostream>
using namespace std;

//Parent Class
class Player{
private:
    int number = 1;
    int age;
    int minutes;
public:

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
    int data;
    Node* next;
};
class list{
private:
    Node*head;
    Node*tail;
public:
    list();
};
int main() {
    return 0;
}

list::list() {
    head = NULL;
    tail = NULL;
}
