import unittest
import Matrix
import copy
import math

class TestSequenceFunction(unittest.TestCase):
  def setUp(self):
    pass

  def test_sanitycheck(self):
    self.assertTrue(True);

  def test_creatematrix(self):
    mat = Matrix.Matrix(5, 3, 'a')
    self.assertEqual(mat.m, 5)
    self.assertEqual(mat.n, 3)
    self.assertEqual(len(mat.a), 3)
    self.assertEqual(len(mat.a[0]), 5)
    self.assertEqual(mat.a[0][4], 'a')

  def test_createrandommatrix(self):
    size = 10
    mat = Matrix.RandomMatrix(size)
    self.assertEqual(len(mat.a), size)
    for i in range(size):
      self.assertEqual(len(mat.a[i]), size)

    for i in range(size):
      for j in range(size):
        self.assertNotEqual(mat.a[i][j], None)

  def test_rotatematrix(self):
    s = 6
    original = Matrix.RandomMatrix(s)
    rotated = copy.deepcopy(original)
    rotated.rotate()
    for i in range(math.ceil(s/2)):
      for j in range(math.ceil(s/2)):
        self.assertEqual(rotated.a[i][j], original.a[j][s-1-i])
        self.assertEqual(rotated.a[j][s-1-i], original.a[s-1-i][s-1-j])
        self.assertEqual(rotated.a[s-1-i][s-1-j], original.a[s-1-j][i])
        self.assertEqual(rotated.a[s-1-j][i], original.a[i][j])

    s = 999
    original = Matrix.RandomMatrix(s)
    rotated = copy.deepcopy(original)
    rotated.rotate()
    for i in range(math.ceil(s/2)):
      for j in range(math.ceil(s/2)):
        self.assertEqual(rotated.a[i][j], original.a[j][s-1-i])
        self.assertEqual(rotated.a[j][s-1-i], original.a[s-1-i][s-1-j])
        self.assertEqual(rotated.a[s-1-i][s-1-j], original.a[s-1-j][i])
        self.assertEqual(rotated.a[s-1-j][i], original.a[i][j])

if __name__=='__main__':
  unittest.main()

