#include "liczba_bib.h"
#include <cmath>

number::number()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

number::number(int i)
{
    Node* n = new Node(i, nullptr, nullptr);
    tail = n;
    head = n;
    length = 0;
}

number::~number()
{
    while (head && head != tail)
    {
        Node* killer = head;
        head = head -> next;
        killer = nullptr;
    }
    tail = nullptr;
}

number::number (const number& src)
{
    length = 0;
    Node* n = new Node(0, nullptr, nullptr);
    tail = n;
    head = n;
    head -> value = src.head -> value;
    Node* ptr = src.head -> next;
    while (ptr)
    {
        addL (ptr -> value);
        ptr = ptr -> next;
    }
}

number & number::operator= (number n)
{
    while(tail != head)
        this -> deleteL();
    head -> value = n.head -> value;
    Node* ptr = n.head -> next;
    while (ptr)
    {
        this -> addL(ptr -> value);
        ptr = ptr -> next;
    }

    return *this;
}

void number::addL(int i)
{
    if (i >= abs(getBase()))
        throw invalid_argument ("cyfra jest wieksza od postawy");

    Node* n = new Node(i, nullptr, nullptr);
    if (head)
    {
        tail -> next = n;
        length++;
        n -> prev = tail;
        tail = n;
    }
}

void number::addF(int i)
{
    if (i >= abs(getBase()))
        throw invalid_argument ("cyfra jest wieksza od postawy");

    Node* n = new Node(i, nullptr, nullptr);
    if (head)
    {
        n -> prev = head;
        if(head == tail)
        {
            tail = n;
            tail -> next = nullptr;
        }
        else
        {
            n -> next = head -> next;
            head -> next -> prev = n;
        }
        length++;
        head -> next = n;
    }
}

void number::deleteF()
{
    if (tail == head)
        return;
    length--;
    Node* killer = head -> next;
    head -> next = killer -> next;
    killer -> next -> prev = head;
    delete killer;
}

void number::deleteL()
{
    if (tail == head)
        return;
    length--;
    Node* killer = tail;
    tail = killer -> prev;
    tail -> next = nullptr;
    delete killer;
}

void number::print() const
{
    if (head -> value < 0 && head -> next -> value != 0)
        cout << "- ";
    Node* ptr = head -> next;
    while (ptr)
    {
        cout << ptr -> value << " ";
        ptr = ptr -> next;
    }
}

/// pierwszy wczytany element - +/- podstawa
void number::read()
{
    cin.clear();
    cout << "Podaj podstawe: ";
    int base;
    cin >> base;
    cout << "Wczytujemy cyfra po cyfrze\nNacisnij CTRL+Z dla zakonczenia wczytywania\n";
    Node* n = new Node (base, nullptr, nullptr);
    head = n;
    tail = n;
    int i;
    while (cin >> i)
    {
        if (i >= abs(base))
        {
            throw invalid_argument ("cyfra jest wieksza od postawy");
        }
        addL(i);
    }
    cin.ignore();
}

int number::getLength() const
{
    return length;
}

int number::getBase() const
{
    return (abs(head -> value));
}

bool number::getSign() const
{
    if (head -> value < 0)
        return false;
    else
        return true;
}

bool number::operator== (const number& n) const
{
    bool res = false;
    number* num = new number(*this);
    number* num2 = new number(n);
    *num = num -> toDecimal();
    *num2 = num2 -> toDecimal();


    if (num -> length == num2 -> length && num -> getSign() == num2 -> getSign())
    {
        Node* ptr1 = num -> head;
        Node* ptr2 = num2 -> head;
        do
        {
            ptr1 = ptr1 -> next;
            ptr2 = ptr2 -> next;

            if (ptr1 -> value != ptr2 -> value)
                break;

            if (ptr1 == num -> tail) return true;
        } while (ptr1 != num -> tail);
    }
    return res;
}

bool number::operator< (const number& n) const
{
    bool res = false;
    number* num = new number(*this);
    number* num2 = new number(n);
    *num = num -> toDecimal();
    *num2 = num2 -> toDecimal();
    Node* ptr1 = num -> head;
    Node* ptr2 = num2 -> head;

    if (num -> length < num2 -> length)
            res = true;
    if (!(num -> getSign()) && (num2 -> getSign()))
        return true;
    else if ((num -> getSign()) && !(num2 -> getSign()))
        return false;
    else if (num -> length == num2 -> length && num -> getSign() == num2 -> getSign())
        do
        {
            ptr1 = ptr1 -> next;
            ptr2 = ptr2 -> next;

            if (ptr1 -> value < ptr2 -> value)
            {
                res = true;
                break;
            }
            else if (ptr1 -> value > ptr2 -> value)
                break;
        }
        while (ptr1 != num -> tail);

    if (!num -> getSign())
        res = !res;

    return res;
}

bool number::operator> (const number& n) const
{
    bool res = false;
    number* num = new number(*this);
    number* num2 = new number(n);
    *num = num -> toDecimal();
    *num2 = num2 -> toDecimal();
    Node* ptr1 = num -> head;
    Node* ptr2 = num2 -> head;
    if (num -> length > num2 -> length)
        res = true;
    if (num -> getSign() && !(num2 -> getSign()))
        return true;
    else if (!num -> getSign() && num2 -> getSign())
        return false;
    else if (num -> length == num2 -> length)
        do
        {
            ptr1 = ptr1 -> next;
            ptr2 = ptr2 -> next;

            if (ptr1 -> value < ptr2 -> value)
                break;
            else if (ptr1 -> value > ptr2 -> value)
            {
                res = true;
                break;
            }
        }
        while (ptr1 != num -> tail && ptr2 != num2 -> tail);

    if (!num -> getSign())
        res = !res;

    return res;
}


bool number::operator> (int i) const
{
    bool res = false;
    number* num = new number(*this);
    *num = num -> toDecimal();
    Node* ptr1 = num -> head;
    int t = i;
    int ctr = 0;
    for (; t > 0; ctr++)
        t /= 10;
    if (num -> length > ctr)
        res = true;
    else if (num -> length == ctr)
        do
        {
            ptr1 = ptr1 -> next;
            t = i/10;
            i = i%10;
            if (ptr1 -> value < t)
                break;
            else if (ptr1 -> value > t)
            {
                res = true;
                break;
            }
        }
        while (ptr1 != num -> tail);

    if (num -> head -> value < 0)
        res = !res;

    return res;
}

bool number::operator< (int i) const
{
    bool res = false;
    number* num = new number(*this);
    *num = num -> toDecimal();
    Node* ptr1 = num -> head;
    int t = i;
    int ctr = 0;
    for (; t > 0; ctr++)
        t /= 10;

    if (num -> length < ctr)
        res = true;
    else if (num -> length == ctr)
        do
        {
            ptr1 = ptr1 -> next;
            t = i/10;
            i = i%10;
            if (ptr1 -> value < t)
            {
                res = true;
                break;
            }
            else if (ptr1 -> value > t)
                break;
        }
        while (ptr1 != num -> tail);

    if (num -> head -> value < 0)
        res = !res;

    return res;
}

number& number::signReverse()
{
    head -> value = - head -> value;
    return *this;
}

number& number::abss()
{
    number* num = new number(*this);
    num -> head -> value = abs(num -> head -> value);
    return *num;
}

/// tylko w syst. dziesietnym
number& number::operator++ ()
{
    if (getSign())
    {
        if (head == tail)
            addL(1);

        else if (tail -> value < 9)
            tail -> value++;

        else
        {
            Node* ptr = tail;
            while (ptr -> value == 9)
            {
                ptr -> value = 0;
                if (ptr -> prev == head)
                {
                    addF(1);
                    return *this;
                }
                ptr = ptr -> prev;

            }
            ptr -> value++;
        }
    }

    return *this;
}
number& number::operator+ (const number& n) const
{

    number* res = new number(10);
    number* num = new number(*this);
    number* num2 = new number(n);
    *num = num -> toDecimal();
    *num2 = num2 -> toDecimal();
    number* tmp = new number(*num);
    number* tmp2 = new number(*num2);
    tmp2 -> signReverse();
    tmp -> signReverse();

    if (!(num->getSign()) && !(num2->getSign()))
    {
        number* res = new number(*num - *tmp2);
        return *res;
    }

    else if (!(num->getSign()))
    {
        number* res = new number(*num2 - *tmp);
        return *res;
    }

    else if (!(num2->getSign()))
    {
        number* res = new number(*num - *tmp2);
        return *res;
    }

    else
    {
        Node* ptr1 = num -> tail;
        Node* ptr2 = num2 -> tail;
        int i = 0;

        while(ptr1 != num -> head && ptr2 != num2 -> head)
        {

            int l = ptr1 -> value + ptr2 -> value;
            if ((l%10) + i <= 9)
            {
                res -> addF((l%10) + i);
                i = 0;
            }
            else
            {
                res -> addF((l+i)%10);
            }
            if (l > 9)
                i = 1;

            ptr1 = ptr1 -> prev;

            ptr2 = ptr2 -> prev;

        }

        while (ptr1 != num -> head)
        {
            if (ptr1 -> value + i < 10)
            {
                res -> addF(ptr1 -> value + i);
                i = 0;
            }
            else
                res -> addF((ptr1 -> value + i)%10);
            ptr1 = ptr1 -> prev;
        }

        while (ptr2 != num2 -> head)
        {
            if (ptr2 -> value + i < 10)
            {
                res -> addF(ptr2 -> value + i);
                i = 0;
            }
            else
                res -> addF((ptr2 -> value + i)%10);
            ptr2 = ptr2 -> prev;
        }

        if (i == 1)
            res -> addF(1);
    }

    return *res;
}

number& number::operator- (const number& n) const
{

    number* res = new number(10);
    number* num = new number(*this);
    number* num2 = new number(n);
    *num = num -> toDecimal();
    *num2 = num2 -> toDecimal();
    number* tmp = new number(*num);
    number* tmp2 = new number(*num2);
    tmp2 -> signReverse();
    tmp -> signReverse();
    bool b = false;

    if (!(num->getSign()) && (num2->getSign()))
    {
        number* res = new number(*tmp + *num2);
        res -> signReverse();
        return *res;
    }

    else if (!(num->getSign()) && !(num2->getSign()))
    {
        number* res = new number(*tmp2 - *tmp);
        return *res;
    }

    else if (!(num2->getSign()))
    {
        number* res = new number(*num + *tmp2);
        return *res;
    }

    else if (*num < *num2)
    {
        number* res = new number(*num2 - *num);
        res -> signReverse();
        return *res;
    }

    else
    {
        Node* ptr1 = num -> tail;
        Node* ptr2 = num2 -> tail;
        int i = 0;
        int v1, v2;

        while (ptr2 != num2 -> head)
        {
            v1 = ptr1 -> value - i;
            v2 = ptr2 -> value;

            if (v1 < v2)
            {
                v1 += 10;
                i = 1;
            }
            else
                i = 0;
            res -> addF(v1-v2);
            ptr1 = ptr1 -> prev;
            ptr2 = ptr2 -> prev;
        }

        while (ptr1 != num -> head)
        {
            int j = ptr1 -> value - i;
            if (j < 0)
            {
                j += 10;
                j = j%10;
                i = 1;
            }
            else
                i = 0;
            if (ptr1 -> prev == num -> head && j == 0)
                break;
            res -> addF(j);

            ptr1 = ptr1 -> prev;
        }

        if (res -> head -> next -> value == 0)
        {
            while(res -> head -> next -> value == 0 && res -> head -> next ->next != nullptr)
                res -> head -> next = res -> head -> next ->next;
        }

        return *res;
    }
}

number& number::operator* (const number& n) const
{
    number* res = new number(10);
    res -> addF(0);
    number* numb = new number(*this);
    number* numb2 = new number(n);
    *numb = numb -> toDecimal();
    *numb2 = numb2 -> toDecimal();
    Node* ptr1 = numb -> tail;
    Node* ptr2 = numb2 -> tail;
    int p = 0;
    int i = 0;
    int v = 0;
    while (ptr2 != numb2 -> head)
    {
        ptr1 = numb -> tail;
        number* num = new number(10);

        for (int j = p; j > 0; j--)
            num -> addL(0);

        while (ptr1 != numb -> head)
        {
            v = ptr1 -> value * ptr2 -> value + i;
            i = v;
            i /= 10;
            num -> addF(v%10);
            ptr1 = ptr1 -> prev;
        }

        if (i>0)
            num -> addF(i);

        i = 0;

        *res = *res + *num;
        ptr2 = ptr2 -> prev;
        p++;
    }

    if (numb -> getSign() != numb2 -> getSign())
        res -> signReverse();

    return *res;
}

number& number::operator/ (number& n)
{
    number* res = new number(10);
    res -> addF(0);
    number* numb = new number(*this);
    number* numb2 = new number(n);
    *numb = numb -> toDecimal();
    *numb2 = numb2 -> toDecimal();
    number* num = new number(10);
    number* num2 = new number(10);
    int i;
    for (i = 0; !(*num2 > numb -> abss()); i++)
    {
        if (num2 -> abss() > numb -> abss()) break;
        ++(*num);
        *num2 = (*numb2)*(*num);
    }
    for (int j = 1; j < i; j++)
        ++(*res);

    if (numb -> getSign() != numb2 -> getSign())
        res -> signReverse();

    return *res;
}

number& number::toDecimal()
{
    number* res = new number(10);

    int power = 0;
    float i = 0;
    int j = 0;
    Node* ptr = tail;
    int base = this -> getBase();
    while (ptr != head)
    {
        i = ptr -> value * pow(base, power);
        for (int j = 0; j < i; j++)
            ++(*res);
        ptr = ptr -> prev;
        power++;
    }
    if (!this -> getSign()) res -> signReverse();
    return *res;
}
