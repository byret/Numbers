#include "liczba_bib.h"

int main()
{
    number n(10);
    n.read();
    number n2(10);
    n2.read();
    cout << "\nPierwsza liczba: ";
    n.print();
    cout << ".  Podstawa " << n.getBase() << ". ";
    if (n.getSign()) cout << "Dodatnia. ";
    else cout << "Ujemna. ";
    if (n.getBase() != 10)
    {
        cout << "W systemie dziesietnym: ";
        n.toDecimal().print();
    }

    cout << "\nDruga liczba: ";
    n2.print();
    cout << ".  Podstawa " << n2.getBase() << ". ";
    if (n2.getSign()) cout << "Dodatnia. ";
    else cout << "Ujemna. ";
    if (n2.getBase() != 10)
    {
        cout << "W systemie dziesietnym: ";
        n2.toDecimal().print();
    }

    if (n == n2)
        cout << "\nSa sobie rowne.";
    else if (n > n2)
        cout << "\nPierwsza liczba jest wieksza od drugiej.";
    else if (n < n2)
        cout << "\nPierwsza liczba jest mniejsza od drugiej.";

    number n3 = n + n2;
    cout << "\nSuma: ";
    n3.print();

    n3 = n - n2;
    cout << "\nRoznica: ";
    n3.print();

    n3 = n * n2;
    cout << "\nIloczyn: ";
    n3.print();

    n3 = n / n2;
    cout << "\nIloraz: ";
    n3.print();

    cout << endl << endl;
    system("pause");
    return 0;
}
