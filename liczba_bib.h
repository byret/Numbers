#ifndef LICZBA_BIB
#define LICZBA_BIB

#include <iostream>
using namespace std;

class number
{
    struct Node
    {
        int value;
        Node* next;
        Node* prev;
        Node (int v, Node* n, Node* p)
        {
            value = v;
            next = n;
            prev = p;
        }
    };
    Node* head;
    Node* tail;
    int length;

public:
    number();
    number(int);
    virtual ~number();
    number (const number&); /// konstruktor kopiujacy
    number& operator= (number); /// operator przypisania
    void addL(int); /// dodawananie cyfry na koniec
    void addF(int); /// dodawanie cyfry na poczatek
    void deleteL(); /// usuwanie cyfry z konca
    void deleteF(); /// usuwanie cyfry z poczatku
    void print() const;
    void read();
    int getLength() const;
    int getBase() const;
    bool getSign() const;
    bool operator== (const number&) const; /// porownywanie number z number
    bool operator< (const number&) const; /// porownywanie number z number
    bool operator> (const number&) const; /// porownywanie number z number
    bool operator< (int) const; /// porownywanie number z int
    bool operator> (int) const; /// porownywanie number z int
    number& signReverse(); /// liczba przeciwna
    number& abss(); /// wartosc bezwzgledna
    number& operator++ (); /// zwieksza wartosc bezwzgledna o 1 (tylko dla liczb w systemie dziesietnym)
    number& operator+ (const number&) const;
    number& operator- (const number&) const;
    number& operator* (const number&) const;
    number& operator/ (number&);
    number& toDecimal(); /// zamiania na system dziesietny
};

#endif // LICZBA_BIB
