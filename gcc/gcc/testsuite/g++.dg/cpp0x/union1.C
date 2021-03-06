// Negative test for C++0x unrestricted unions
// { dg-options -std=c++0x }
// { dg-prune-output "implicitly deleted because" }

struct A
{
  A();
  A(const A&);
  ~A();
};

union B
{
  A a;				// { dg-error "union member" }
};

B b;				// { dg-error "B::B\\(\\)" }
B b2(b);			// { dg-error "B::B\\(const B&\\)" }

struct C
{
  union
  {
    A a;			// { dg-error "union member" }
  };
};

C c;				// { dg-error "C::C\\(\\)" }
C c2(c);			// { dg-error "C::C\\(const C&\\)" }

// { dg-error "B::~B" "" { target *-*-* } 17 }
// { dg-error "B::~B" "" { target *-*-* } 18 }
// { dg-error "C::~C" "" { target *-*-* } 28 }
// { dg-error "C::~C" "" { target *-*-* } 29 }
