//Sunny's Sample Code

#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

class Player
{
public:
    int number;
    int age;
    int minutes;
    double timeatstart;
    
    bool isOnCourt;
    
    Player* next;
    Player* prev;
    
    Player() {
        this->number = -1;
        this->age = -1;
        this->minutes = -1;
        this->timeatstart = -1;
        
        this->isOnCourt = false;
        
        this->next = NULL;
        this->prev = NULL;
    }
    
    Player(int number, int age, int minutes, bool isOnCourt)
    {
        this->number = number;
        this->age = age;
        this->minutes = minutes;
        this->timeatstart = 0;
        
        this->isOnCourt = isOnCourt;
        
        this->next = NULL;
        this->prev = NULL;
    }
};

class Bench
{
public:
    Player* head;
    Player* tail;
    int size;
    
    Bench()
    {
        this->head = NULL;
        this->tail = NULL;
        this->size =0;
    }
    
    void addFirst(Player *x) //done I think
    {
        if (head == NULL)
        {
            head = x;
            tail = x;
            
            return;
        }
        x->next = head;
        head = x;
        ++size;
        
        
    }
    
    // call addLast
    void add(Player* x)
    {
        if (head == NULL)
        {
            head = x;
            tail = x;
            
            return;
        }
        
        x->prev = tail;
        tail->next = x;
        tail = x;
        ++size;
    }
    
    Player* getFirst()//why?
    {
        
        return head;
        
    }
    
    Player* getLast()//why?
    {
        return tail->next; // wrong
    }
    
    Player* get(int index)
    {
        if (head == NULL)
            return NULL;
        if (index < 0 || index >= size)
            return NULL;
        
        Player* tmp = head;
        int counter = 0;
        while (tmp != NULL) {
            if (counter == index)
                return tmp;
            
            tmp = tmp->next;
            ++counter;
        }
        
        return NULL;
    }
    
    void set(Player* x)// change bench status
    {
        x->isOnCourt = !x->isOnCourt;
    }

    Player* unbench(){
        //return head
        //make 2nd player new head
        Player* tmp = head;
        head = head->next;
        set(tmp);
        return tmp;
    }
    
    void print()
    {
        cout << "This is the bench: ";
        
        Player* tmp = head;
        
        while (tmp != NULL) {
            cout << tmp->number;
            if (tmp->next != NULL)
                cout << " --> ";
            tmp = tmp->next;
        }
        
        cout << endl;
    }
};

class Court
{
public:
    Player* head;
    Player* tail;
    int size;
    
    Court()
    {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }
    
    void add(Player* x)
    {
        ++size;
        
        if (head == NULL)
        {
            head = x;
            tail = x;
            
            return;
        }
        
        x->prev = tail;
        tail->next = x;
        tail = x;
        tail->next = head;
    }
    
    void set(int index, int minutesPlayed)
    {
        Player* tmp = head;
        int counter = 0;
        while (tmp != NULL) {
            if (counter == index)
                tmp->minutes = minutesPlayed;
            
            tmp = tmp->next;
            ++counter;
        }
    }
    
    Player* get(int index)
    {
        if (head == NULL)
            return NULL;
        if (index < 0 || index >= size)
            return NULL;
        
        Player* tmp = head;
        int counter = 0;
        while (tmp != NULL) {
            if (counter == index)
                return tmp;
            
            tmp = tmp->next;
            ++counter;
        }
        
        return NULL;
    }
    
    void print()
    {
        cout << "This is the court: ";
        
        Player* tmp = head;
        
        while (tmp != NULL) {
            cout << tmp->number;
            if (tmp->next != head)
                cout << " --> ";
            else
                break;
            tmp = tmp->next;
        }
        
        cout << endl;
    }
    
    void sort(string sortBy)
    {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1; j++) {
                Player* x = get(j);
                Player* y = get(j + 1);
                
                //  4-> 7-> 1
                // &1->&2->&3
                if (sortBy == "number" && x->number > y->number) { // how did you mess this up? 
                    Player* tmp = x; 
                    x = y; 
                    y = tmp; 
                }
                if (sortBy == "minutes" && x->minutes > y->minutes) {
                    Player* tmp = x; 
                    x = y; 
                    y = tmp; 
                }
                if (sortBy == "age" && x->age > y->age) {
                    Player* tmp = x; 
                    x = y; 
                    y = tmp; 
                }
            }
    }
};

void startGame(Bench bench, Court court)//working on this
{
    int quart =1;
    double min =0.0;
    
    while(quart<5)
    {
        while(min<12.0)
        {
            double old = court.head->age*.1; // num of mins oldest player is allowed to play
            for(double i =0.0;i<0.9;i+=.1)
            {
                if(old <= (quart*12 + min+i) - court.head->timeatstart)
                //        time since start   - time player entered court
                {
                    //add minutes to minutes played
                    court.head->minutes += i;
                    //bench player (needs work) to end of bench
                    bench.add(court.head);
                    bench.set(court.head);
                    //add player to court from top of bench
                    Player* tmp = bench.unbench();
                    //set timestamp
                    tmp->timeatstart = quart*12 + min+i;
                    court.add(tmp);
                    //sort court by age
                    court.sort("age");
                    cout<<min+i<<endl;
                }
            }
            min++;
            //add 1 min to all players on court
            Player* cur = court.head;
            for(int i=0;i<court.size;i++){
                cur->minutes += 1;
                cur = cur->next;
            }
        }
        //displaying the output all together (needs work)
        cout<<"Report "<<quart<<endl;
        court.print();
        
        quart++;
    }
}

int main(int argc, char *argv[])
{
    ArgumentManager am(argc,argv);
    string inputfilename = am.get("input");
    string outputfilename = am.get("input");

    Player* lockerRoom = new Player[12];
    
    Bench bench;

    ifstream inf;
    inf.open(inputfilename);

    for (int i = 0; i <= 6; i++) {
        int number;
        int age;
        inf >> number;
        inf >> age;
        Player* p = new Player(number, age, 0, false);
        bench.add(p);
    }
    bench.print();
    
    Court court;
    for (int i = 1; i <= 5; i++) {
        int number;
        int age;
        inf >> number;
        inf >> age;
        Player* p = new Player(number, age, 0, false);
        court.add(p);
    }
    
    court.sort("age");
    court.print();
    
    startGame(bench, court);
   
    
    
    
    
    
    return 0;
}

