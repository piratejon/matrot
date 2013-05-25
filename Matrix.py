
import random
import math

class Matrix():
  def __init__(self, m, n = None, fill = None):
    self.m = m
    self.n = n if n is not None else m
    if fill is not None: self.fill(fill)

  def fill(self, fill):
    self.a = [[fill for i in range(self.m)] for j in range(self.n)]

  def rotate(self):
    s = len(self.a)
    w = math.ceil(s/2)
    s = s - 1
    i_max = w if s & 1 else w-1
    for i in range(i_max):
      for j in range(w):
        tmp = self.a[i][j]
        self.a[i][j] = self.a[j][s-i]
        self.a[j][s-i] = self.a[s-i][s-j]
        self.a[s-i][s-j] = self.a[s-j][i]
        self.a[s-j][i] = tmp

  def print(self):
    for i in range(len(self.a)):
      for j in range(len(self.a[i])):
        print('%2d' % (self.a[i][j]),end=',')
      print('')
    print('')

  def fill_sequential(self):
    self.a = [[j*self.m+i for i in range(self.m)] for j in range(self.n)]

class RandomMatrix(Matrix):
  def __init__(self, m, n = None):
    super().__init__(m, n)
    self.fill_random()
  
  def fill_random(self):
    j = 0
    self.a = [[random.randrange(100) for i in range(self.m)] for j in range(self.n)]

