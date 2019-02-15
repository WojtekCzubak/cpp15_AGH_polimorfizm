#include <iostream>
using namespace std;

struct IA // interface
{
    virtual void f1() = 0; // purely virtual function // zerujemy bo tu nie ma implementacji to czysto wirtualna fcja
    virtual ~IA(); // trzeba dodac ze wirtualny destruktor zeby kompilator sie nie denerwowal
    IA() { cout << "IA::IA()" << endl; }
};

IA::~IA() {} //pusta definicja destruktora wyniesiona na zewnatrz zeby sie kompilator nie szczypal :)

struct A : public IA //zobacz czy potrzeby tu jest public !!! // A rozszerza IA
{
    void f1() override { cout << "A::f1()" << endl; } //override - nadpisywanie implementacji -> patrz rysunek notatki
    void f2() { cout << "A::f2()" << endl; } // not virtual ! //ona nie byla zaznaczona jako wirtualna
    void f3() { cout << "A::f3()" << endl; } // not virtual ! // jw

    A() { cout << "A::A()" << endl; }
    ~A() override; //A nadpisuje destruktor wiec powinien byc zaznaczony jako virtual
};

A::~A() { cout << "~A::A()" << endl; }

struct B : public A // struct rozni sie od klasy tym ze to sa takie pjemniki na dane, nie daje sie funkcji skladowych
{
    void f1() override { cout << "B::f1()" << endl; }
    virtual void f2() { cout << "B::f2()" << endl; } // <- !!!

    B() { cout << "B::B()" << endl; }
    ~B() override;
};

B::~B() { cout << "~B::B()" << endl; }

struct C : public B
{
    void f1() override { cout << "C::f1()" << endl; }
    void f2() override { cout << "C::f2()" << endl; }
    void f3() { cout << "C::f3()" << endl; } // <- hiding not overriding !

    C() { cout << "C::C()" << endl; }
    ~C() override;
};

C::~C() { cout << "~C::C()" << endl; }

struct D { //D nie dziedziczy z nikogo i nikogo nie rozszerza -> bedzie to na rysunku w notatkach
    void f1() { cout << "D::f1()" << endl; }
    void f2() { cout << "D::f2()" << endl; }
    void f3() { cout << "D::f3()" << endl; }

    D() { cout << "D::D()" << endl; }
    ~D() { cout << "~D::D()" << endl; }
};

void demo1()
{
    cout << "demo1()..." << endl;
// tworzymy typy ABC, instancje ich tworzone sa na stosie
    A a; cout << endl;
    B b; cout << endl;
    C c; cout << endl;
    D d; cout << endl;

    cout << "calling f1(), f2(), f3() for object A a ..." << endl;
    a.f1(); a.f2(); a.f3();
    cout << endl;

    cout << "calling f1(), f2(), f3() for object B b ..." << endl;
    b.f1(); b.f2(); b.f3();
    cout << endl;

    cout << "calling f1(), f2(), f3() for object C c ..." << endl;
    c.f1(); c.f2(); c.f3();
    cout << endl;

    cout << "calling f1(), f2(), f3() for object D d ..." << endl;
    d.f1(); d.f2(); d.f3();
    cout << endl;
}

void demo2()
{
    cout << "demo2()..." << endl;

    cout << "constructing A..." << endl;
    A *pAA = new A; cout << endl; // alokujemy pamiec na stercie bo mamy new !!! wynik zapisujemy w zmiennej wskaznikowej *pAA
    cout << "calling methods with the use of 'A * pAA = new A'" << endl;
    pAA->f1(); pAA->f2(); pAA->f3(); //wolamy przy pomocy wskaznika // notacja pAA->f1() to to samo co (*pAA).f1()
    cout << endl;

    cout << "constructing B..." << endl;
    A *pAB = new B; cout << endl; //adres zapisujemy do pokazywania na A
    cout << "calling methods with the use of 'A * pAB = new B'" << endl;
    pAB->f1(); pAB->f2(); pAB->f3();
    cout << endl;

    cout << "constructing C..." << endl;
    A *pAC = new C; cout << endl;
    cout << "calling methods with the use of 'A * pAC = new C'" << endl;
    pAC->f1(); pAC->f2(); pAC->f3();
    cout << endl;

    cout << "constructing B..." << endl;
    B *pBB = new B; cout << endl;
    cout << "calling methods with the use of 'B * pBB = new B'" << endl;
    pBB->f1(); pBB->f2(); pBB->f3();
    cout << endl;

    cout << "constructing C..." << endl;
    B *pBC = new C; cout << endl;
    cout << "calling methods with the use of 'B * pBC = new C'" << endl;
    pBC->f1(); pBC->f2(); pBC->f3();
    cout << endl;

   cout << "calling f1 with the use od pIA"<<endl;
    IA *pIA = new A;
   pIA->f1(); //jak skasujesz to f1 to zobacz jakie fcje sie rozwijaja

   pIA = new B;
   pIA->f1();

   pIA = new C;
   pIA ->f1();


    cout << "deleting objects..." << endl;
    delete pAA; cout << endl;
    delete pAB; cout << endl;
    delete pAC; cout << endl;
    delete pBB; cout << endl;
    delete pBC; cout << endl;
}

int main()
{
    //demo1();
   // cout << endl;
    demo2();
}

