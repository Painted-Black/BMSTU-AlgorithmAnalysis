import unittest
import string
import random

from LevenshteinDistance import levenshteinDistance_m, levenshteinDistance_r, damerauLevenshteinDistance_m, \
    damerauLevenshteinDistance_r


def randomString(l):
    letters = string.ascii_lowercase + string.ascii_uppercase
    lettersLen = len(letters)

    s = ''
    for i in range(l):
        s += letters[random.randint(0, lettersLen - 1)]

    return s


class TestDistance(unittest.TestCase):
    def setUp(self):
        self.function = None

    def testEmptySring(self):
        self.assertEqual(self.function('', ''), 0)

    def testSameStrings(self):
        self.assertEqual(self.function("abc", "abc"), 0)
        self.assertEqual(self.function("0", "0"), 0)

    def testDifferensStrings(self):
        self.assertEqual(self.function("a", ""), 1)
        self.assertEqual(self.function("", "1"), 1)
        self.assertEqual(self.function("b", "c"), 1)
        self.assertEqual(self.function("bc", "b"), 1)
        self.assertEqual(self.function("bc", "c"), 1)
        self.assertEqual(self.function("ab", "cd"), 2)


class TestLevenshteinMatrDistance(TestDistance):
    def setUp(self):
        self.function = levenshteinDistance_m

    def testTypo(self):
        self.assertEqual(self.function('скат', 'кот'), 2)
        self.assertEqual(self.function('скат', 'кат'), 1)
        self.assertEqual(self.function("ac", "ca"), 2)
        self.assertEqual(self.function('abc', 'cba'), 2)


class TestLevenshteinRecDistance(TestDistance):
    def setUp(self):
        self.function = levenshteinDistance_r

    def testTypo(self):
        self.assertEqual(self.function('скат', 'кот'), 2)
        self.assertEqual(self.function('скат', 'кат'), 1)
        self.assertEqual(self.function("ac", "ca"), 2)
        self.assertEqual(self.function('abc', 'cba'), 2)


class TestDamerauLevenshteinMatrDistance(TestDistance):
    def setUp(self):
        self.function = damerauLevenshteinDistance_m

    def testTypo(self):
        self.assertEqual(self.function('скат', 'кот'), 2)
        self.assertEqual(self.function('скат', 'кат'), 1)
        self.assertEqual(self.function("ac", "ca"), 1)
        self.assertEqual(self.function("abc", "cba"), 2)


class TestDamerauLevenshteinRecDistance(TestDistance):
    def setUp(self):
        self.function = damerauLevenshteinDistance_r

    def testTypo(self):
        self.assertEqual(self.function('скат', 'кот'), 2)
        self.assertEqual(self.function('скат', 'кат'), 1)
        self.assertEqual(self.function("ac", "ca"), 1)
        self.assertEqual(self.function("abc", "cba"), 2)


class TestPair(unittest.TestCase):
    TESTS_NUMBER = 10

    def setUp(self):
        self.function1 = None
        self.function2 = None

    def testEmptyStrings(self):
        for i in range(TestPair.TESTS_NUMBER):
            s1 = randomString(i)
            s2 = randomString(0)
            self.assertEqual(self.function1(s1, s2), self.function2(s1, s2))
            self.assertEqual(self.function1(s2, s1), self.function2(s2, s1))

    def testSameLenStrings(self):
        for i in range(1, TestPair.TESTS_NUMBER):
            s1 = randomString(i)
            s2 = randomString(i)
            self.assertEqual(self.function1(s1, s2), self.function2(s1, s2))
            self.assertEqual(self.function1(s2, s1), self.function2(s2, s1))

    def testDiffLenStrings(self):
        for i in range(1, TestPair.TESTS_NUMBER):
            l1 = random.randint(1, 10)
            l2 = random.randint(1, 10)
            if l1 == l2:
                if l2 + 1 > 10:
                    l2 -= 1
                else:
                    l2 += 1
            s1 = randomString(l1)
            s2 = randomString(l2)
            self.assertEqual(self.function1(s1, s2), self.function2(s1, s2))
            self.assertEqual(self.function1(s2, s1), self.function2(s2, s1))


class TestLevenshteinDistances(TestPair):
    def setUp(self):
        self.function1 = levenshteinDistance_m
        self.function2 = levenshteinDistance_r


class TestDamerauLevenshteinDistances(TestPair):
    def setUp(self):
        self.function1 = damerauLevenshteinDistance_m
        self.function2 = damerauLevenshteinDistance_r


def runTests():
    suite = unittest.TestLoader().loadTestsFromTestCase(TestLevenshteinMatrDistance)
    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(TestLevenshteinRecDistance))
    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(TestDamerauLevenshteinMatrDistance))
    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(TestDamerauLevenshteinRecDistance))
    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(TestLevenshteinDistances))
    suite.addTests(unittest.TestLoader().loadTestsFromTestCase(TestDamerauLevenshteinDistances))
    unittest.TextTestRunner().run(suite)
