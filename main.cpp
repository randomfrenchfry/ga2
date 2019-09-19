//Sony's Sample Code

#include <iostream>
using namespace std;

class Player
{
public:
    int number;
    int age;
    int minutes;
    
    bool isOnCourt;
    
    Player* next;
    Player* prev;
    
    Player() {
        this->number = -1;
        this->age = -1;
        this->minutes = -1;
        
        this->isOnCourt = false;
        
        this->next = NULL;
        this->prev = NULL;
    }
    
    Player(int number, int age, int minutes, bool isOnCourt)
    {
        this->number = number;
        this->age = age;
        this->minutes = minutes;
        
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
        return tail;
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
    
    void set(Player* x)// change bench status?
    {
        x->isOnCourt = !x->isOnCourt;
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
    
    void set(int index, int minutesPlayed)//maybe idk
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
                if (sortBy == "number" && x->number > y->number) {
                    int tmp = x->number;
                    x->number = y->number;
                    y->number = tmp;
                }
                if (sortBy == "minutes" && x->minutes > y->minutes) {
                    int tmp = x->minutes;
                    x->minutes = y->minutes;
                    y->minutes = tmp;
                }
                if (sortBy == "age" && x->age > y->age) {
                    int tmp = x->age;
                    x->age = y->age;
                    y->age = tmp;
                }
            }
    }
};

int main()
{
    Player* lockerRoom = new Player[12];
    
    Bench bench;
    for (int i = 6; i <= 12; i++) {
        Player* p = new Player(i, i + 19 + i, 0, false);
        bench.add(p);
    }
    bench.print();
    
    Court court;
    for (int i = 1; i <= 5; i++) {
        Player* p = new Player((i + 1), i, 0, true);
        court.add(p);
    }
    
    court.sort("age");
    court.print();
    
    
    
    
    
    
    
    return 0;
}
