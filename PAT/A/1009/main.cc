#include <assert.h>
#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>

struct Complex {
  double re, im;
  Complex() {}
  Complex(double r, double i = 0) : re(r), im(i) {}
  inline Complex operator+(const Complex &right) const { return Complex(re + right.re, im + right.im); }
  inline Complex operator-(const Complex &right) const { return Complex(re - right.re, im - right.im); }
  inline Complex operator*(const Complex &right) const {
    return Complex(re * right.re - im * right.im, im * right.re + re * right.im);
  }
};

std::ostream &operator<<(std::ostream &out, const Complex &c) {
  out << std::setprecision(2) << c.re << "+" << c.im << "i" << std::setprecision(6);
  return out;
}

Complex *unit_root(int n) {
  const double pi = acos(-1);
  Complex *rs = (Complex *)malloc(sizeof(*rs) * n);
  double unit = 2 * pi / n;
  double angle = 0;
  for (int i = 0; i < n; i++) {
    double a = cos(angle);
    rs[i].re = cos(angle);
    rs[i].im = sin(angle);
    angle += unit;
  }
  return rs;
}

Complex FFT_recursive(double *as, int len, int step, int k, Complex *roots) {
  if (len == 2) {
    return as[0] + as[step];
  }
  Complex t1 = FFT_recursive(as, len / 2, step * 2, k, roots);
  Complex t2 = FFT_recursive(as + 1, len / 2, step * 2, k, roots);
  return t1 + roots[k * step] * t2;
}

Complex *FFT(double *as, int as_len) {
  Complex *roots = unit_root(as_len);
  Complex *ys = (Complex *)malloc(sizeof(*ys) * as_len);
  int half_len = as_len / 2;
  for (int i = 0; i < half_len; i++) {
    Complex t1 = FFT_recursive(as, as_len / 2, 2, i, roots);
    Complex t2 = FFT_recursive(as + 1, as_len / 2, 2, i, roots);
    ys[i] = t1 + roots[i] * t2;
    ys[half_len + i] = t1 - roots[i] * t2;
  }
  free(roots);
  return ys;
}

Complex *naive_method(double *as, int as_len) {
  Complex *root = unit_root(as_len);
  Complex *ys = (Complex *)malloc(sizeof(*ys) * as_len);

  free(root);
  return ys;
}

int ceil_power2(int a) {
  if (a <= 1) {
    return 1;
  }
  int count = 0;
  a--;
  while (a) {
    count++;
    a >>= 1;
  }
  return 1 << count;
}

void get_as(int *out_len, double **out_as) {
  int K, n;
  double *as, a;
  assert(scanf("%d", &K) == 1);
  assert(scanf("%d %lf", &n, &a) == 2);
  *out_len = ceil_power2(n + 1);
  as = (double *)malloc(sizeof(*as) * *out_len);
  *out_as = as;
  as[n] = a;
  for (int i = 1; i < K; i++) {
    assert(scanf("%d %lf", &n, &a) == 2);
    as[n] = a;
  }
}

int main() {
  Complex *rs;
  int rs_len = 4;
  unit_root(rs_len, &rs);
  for (int i = 0; i < rs_len; i++) {
    std::cout << rs[i] << std::endl;
  }
  // double *as1, *as2;
  // int as1_len, as2_len;
  // get_as(&as1_len, &as1);
  // get_as(&as2_len, &as2);
  // free(as1);
  // free(as2);
}