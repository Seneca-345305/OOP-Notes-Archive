#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
class Employee {
   double m_salary;
   int m_empno;
   char m_name[31];
public:
   Employee(double sal, int emp, const char* nm) {
      m_salary = sal;
      m_empno = emp;
      strncpy(m_name, nm, 30);
      m_name[30] = '\0';
   }
   double salary()const {
      return m_salary;
   }
   ostream& print(ostream& os)const {
      return os << left << setw(25) << m_name << " Emno: " << setw(7) << m_empno
         << ", Salary: " << setw(10) << fixed << setprecision(2) << right << m_salary;
   }
};
ostream& operator<<(ostream& os, const Employee& E) {
   return E.print(os);
}

template <typename type>
class sPtr {
   type* m_ptr{ nullptr };
   static int m_cnt;
public:
   explicit sPtr(type* ptr) :m_ptr(ptr) {
      m_cnt++;
   }
   sPtr(const sPtr<type>& p) {
      m_ptr = p.m_ptr;
      m_cnt++;
   }
   sPtr<type>& operator=(const sPtr<type>& p) {
      m_ptr = p.m_ptr;
      m_cnt++;
      return *this;
   }
   sPtr(sPtr<type>&& sp) {
      m_ptr = sp.m_ptr;
      sp.m_ptr = nullptr;
   }
   sPtr<type>& operator=(sPtr<type>& sp) {
      delete m_ptr;
      m_ptr = sp.m_ptr;
      sp.m_ptr = nullptr;
      return *this;
   }
   ~sPtr() {
      if (m_cnt == 1)
         delete m_ptr;
      else {
         m_cnt--;
      }
   }
   type& operator*() {
      return *m_ptr;
   }
   type* operator->() {
      return m_ptr;
   }
   bool operator==(void* ptr) {
      return static_cast<void*>(m_ptr) == ptr;
   }
   bool operator!=(void* ptr) {
      return !operator==(ptr);
   }
};
template <typename type>
int sPtr<type>::m_cnt = 0;

void EmpMaker(const char* name, int empNo, double sal) {
   sPtr<Employee> p(new Employee(sal, empNo, name));
   cout << *p << endl;
   sPtr<Employee> q(p);
   cout << "The Salary is: " << q->salary() << endl;
}

int main() {
   sPtr<int> a(new int);
   *a = 12;
   cout << *a << endl;
   sPtr<int> b(a);
   sPtr<int> c(b);
   (*c)++;
   sPtr<int> d = move(a);
   if (a != nullptr)
      cout << *a << endl;
   if (d != nullptr)
      cout << *d << endl;
   cout << *b << *c << endl;
   EmpMaker("Fred Soley", 123, 123456.78);
   return 0;
}
