// ���������� ����� �� ���������� � �������� �� ������������ vecta.
// ���������� � �����, ����� ���� �� �� ������������ ���� ����������
// sketchps.  �������� �������� ������� �� ����� �������� �������
// ���� test.eps �� PostScript, ����� ������� ��������� (���������):
//
//     tang2c | sketchps 0 >test.eps
// -----------------------------------------------------------------

#include <iostream>
#include "vecta.h"

using namespace std;
using namespace vecta;

template <typename N>
ostream& operator << (ostream& os, vec2d<N> p)  {
  return  os << p.x << ' ' << p.y;
}

// �������� �� ������� ����� ��� ���� ����������� �� ��� ����������.
// ����������� ������� ������������ � ��������� ��� ����������� � ���
// ������ ����� ����� �� ���� ��������, ����� ������:
//     c1, r1 = ������ � ������ �� ������� ���������
//     c2, r2 = ������ � ������ �� ������� ���������
//     s1 = 1 �� �����-���� � ������-����� ��������, ����� -1
//     s2 = 1 �� ������-���� � ������-����� ��������, ����� -1
//     k = ����� ��� ��������� � ������������� �����, 1 ��� 2
vec2d<> tang2c(vec2d<>& c1, double r1, vec2d<>& c2, double r2, int s1, int s2, int k)  {
  vec2d<> u = c2-c1,
          c = k==1 ? c1 : c2;
  double d = norm(u),
         t = r1+s1*r2,
         r = k==1 ? r1 : r2,
         s = 2*(k+s1!=3)-1;
  return c+s*r/d*(t*u+s2*sqrt(d-t*t)*~u);
}

int main()  {
// �������� ����������� �� ����������, �. �� �� �� ������ ������ �����������:
  double r1=5, r2=3;
  vec2d<> c1(1,1), c2(c1+vec2d<>(10,0));
// �������� �� ������ ������� �����:
  vec2d<> pLL1 = tang2c(c1,r1,c2,r2,1,-1,1),
          pLL2 = tang2c(c1,r1,c2,r2,1,-1,2),
          pLR1 = tang2c(c1,r1,c2,r2,-1,-1,1),
          pLR2 = tang2c(c1,r1,c2,r2,-1,-1,2),
          pRL1 = tang2c(c1,r1,c2,r2,-1,1,1),
          pRL2 = tang2c(c1,r1,c2,r2,-1,1,2),
          pRR1 = tang2c(c1,r1,c2,r2,1,1,1),
          pRR2 = tang2c(c1,r1,c2,r2,1,1,2);
// �������� �� ������������:
  cout << "width 1\ncolour gray\ncircles\n" << c1 << ' ' << r1 << endl
                                            << c2 << ' ' << r2 << endl;
// �������� �� �������
  cout << "colour blue\npoints\n" << pLL1 << endl << pLL2 << endl
                                  << pLR1 << endl << pLR2 << endl
                                  << pRL1 << endl << pRL2 << endl
                                  << pRR1 << endl << pRR2 << endl;
// �������� �� ������������� �������:
  cout << "width .3\ncolour purple\nlines\n" << pLL1 << ' ' << pLL2 << endl
                                             << pLR1 << ' ' << pLR2 << endl
                                             << pRL1 << ' ' << pRL2 << endl
                                             << pRR1 << ' ' << pRR2 << endl;
  return 0;
}