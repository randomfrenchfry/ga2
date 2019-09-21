

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
    
    void set(Player* x)
    {
        x->isOnCourt = !x->isOnCourt;
    }
    
    Player* unbench(){
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
        head->prev = x;
        tail = x;
        tail->next = head;
    }
    
    void swapouthead(){
        head = head->next;
        head->prev = tail;
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
        
        while (tmp != tail) {
            cout << tmp->number << "-" << tmp->minutes << " --> ";
            
            tmp = tmp->next;
        }
        cout << tmp->number << "-" << tmp->minutes << endl;
    }
    
    void sort(string sortBy)
    {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - 1; j++) {
                Player* x = get(j);
                Player* y = get(j + 1);
                
               
                if (sortBy == "number" && x->number > y->number) {
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



void startGame(Bench bench, Court court, Player* lockerRoom)//working on this
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
                if(old <= ((quart-1)*12 + min+i) - court.head->timeatstart)
                    //        time since start   - time player entered court
                {
                    //cout << "changing player: " << court.head->number << "played: " << court.head->minutes << " st time:" << (quart-1)*12 + min+i << endl;
                    //add minutes to minutes played
                    court.head->minutes += i;
                    //bench player (needs work) to end of bench
                    bench.add(court.head);
                    bench.set(court.head);
                    court.swapouthead();
                    //add player to court from top of bench
                    Player* tmp = bench.unbench();
                    //set timestamp
                    tmp->timeatstart = quart*12 + min+i;
                    court.add(tmp);
                    //sort court by age
                    court.sort("age");
                    //cout<<min+i<<endl;
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
        quart++;
        min = 0.0;
        
    }
    
    
    // The minutes are fucked (48mins only in one Game)
    Player* cu;
    cu = bench.head;
    int c =0;
    while(c<bench.size)
    {
        for(int i =0;i<12;i++)
        {
            if(cu->number == lockerRoom[i].number)
            {
                lockerRoom[i].minutes = cu->minutes;
            }
        }
        cu = cu->next;
        c++;
    }
   
   
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Command:  \"input=<file>;output=<file>;\"" <<  endl;
        return -1;
    }
    ArgumentManager am(argc,argv);
    string inputfilename = am.get("input");
    string outputfilename = am.get("output");
    
    Player* lockerRoom = new Player[12];
    
    Bench bench;
    
    ifstream inf;
    inf.open(inputfilename);
    
    for (int i = 0; i < 6; i++) {
        int number;
        int age;
        inf >> number;
        inf >> age;
        Player* p = new Player(number, age, 0, false);
        bench.add(p);
        lockerRoom[i] = *p;
        
    }
    
    Court court;
    for (int i = 6; i < 12; i++) {
        int number;
        int age;
        inf >> number;
        inf >> age;
        Player* p = new Player(number, age, 0, false);
        court.add(p);
        lockerRoom[i] = *p;
    }
    
    court.sort("age");
    
    startGame(bench, court,lockerRoom);
    
    ofstream outf;
    outf.open(outputfilename);
    
    
    outf << "Report 1: "<<endl;
    outf << "Number - Minutes Played" << endl;
    for(int i =0;i<(bench.size+court.size);i++)
    {
        outf << lockerRoom[i].number << " - " << lockerRoom[i].minutes << endl;
    }
    
    outf << endl;
    
    outf << "Report 2: "<<endl;
    outf << "Age - Number - Minutes Played" << endl;
    for(int i =0;i<(bench.size+court.size);i++)
    {
        outf << lockerRoom[i].age << " - " << lockerRoom[i].number << " - " << lockerRoom[i].minutes << endl;
    }
    
    
    
   
   
    
    return 0;
}
