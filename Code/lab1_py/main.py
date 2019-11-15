from LevenshteinDistance import levenshteinDistance_m, levenshteinDistance_r, damerauLevenshteinDistance_m, \
    damerauLevenshteinDistance_r
from tests import runTests


import string
import random
import time
import locale


def randomString(l):
    letters = string.ascii_lowercase + string.ascii_uppercase
    lettersLen = len(letters)

    s = ''
    for i in range(l):
        s += letters[random.randint(0, lettersLen - 1)]

    return s


def getDiatanceMatrix(function, printFlag):
    s1 = input("Строка 1: ")
    s2 = input("Строка 2: ")
    d = function(s1, s2, printFlag)
    print("Расстояние Левенштейна (матрично): ", d)


def getDistanceRec(function):
    s1 = input("Строка 1: ")
    s2 = input("Строка 2: ")
    d = function(s1, s2)
    print("Расстояние Левенштейна (матрично): ", d)


def distances():
    s1 = input("Строка 1: ")
    s2 = input("Строка 2: ")

    printFlag = getPrintFlag()

    d1 = levenshteinDistance_m(s1, s2, printFlag)
    d2 = levenshteinDistance_r(s1, s2)
    d3 = damerauLevenshteinDistance_m(s1, s2, printFlag)
    d4 = damerauLevenshteinDistance_r(s1, s2)

    print("Расстояние Левенштейна (матрично): ", d1)
    print("Расстояние Левенштейна (рекурсивно): ", d2)
    print("Расстояние Дамерау-Левенштейна (матрично): ", d3)
    print("Расстояние Дамерау-Левенштейна (рекурсивно): ", d4)


def timeTestFunc(func, testsPerWlen=1, maxLen=10, minLen=1, step=1):
    TESTS_PER_WORDLEN = testsPerWlen
    MAX_TEST_WORDLEN = maxLen
    MIN_TEST_WORDLEN = minLen
    STEP = step
    times = {}
    for i in range(MIN_TEST_WORDLEN, MAX_TEST_WORDLEN+1, STEP):
        s1 = randomString(i)
        s2 = randomString(i)
        total_time = 0
        for j in range(TESTS_PER_WORDLEN):
            t1 = time.time()
            d = func(s1, s2)
            t2 = time.time()
            total_time += (t2 - t1)
        total_time /= TESTS_PER_WORDLEN
        times[i] = total_time

    return times


def timeTest():
    levMatrTimes = timeTestFunc(levenshteinDistance_m)
    levRecTimes = timeTestFunc(levenshteinDistance_r, testsPerWlen=1)
    damLevMartTimes = timeTestFunc(damerauLevenshteinDistance_m)
    damLevRecTimes = timeTestFunc(damerauLevenshteinDistance_r, testsPerWlen=1)

    print('{:^30}'.format('Word len'),
          '{:^30}'.format('Lev(M)'), '{:^30}'.format('Lev(R)'),
          '{:^30}'.format('DamLev(M)'), '{:^30}'.format('DamLev(R)'))

    l = len(levMatrTimes)
    keys1 = levMatrTimes.keys()

    for i in keys1:
        print('{:^30}'.format(i),
              '{:^30}'.format(locale.format("%2f", levMatrTimes.get(i))),
              '{:^30}'.format(locale.format("%2f", levRecTimes.get(i))),
              '{:^30}'.format(locale.format("%2f", damLevMartTimes.get(i))),
              '{:^30}'.format(locale.format("%2f", damLevRecTimes.get(i))))


def getPrintFlag():
    print("Печатать матрицу? (y/n)")
    answer = input(" > ")
    if answer == 'y':
        return True
    return False


def menu():
    run = True
    while run:
        print("1 - расстояние Левенштейна матрично")
        print("2 - расстояние Левенштейна рекурсивно")
        print("3 - расстояние Дамерау-Левенштейна матрично")
        print("4 - расстояние Дамерау-Левенштейна рекурсивно")
        print("5 - все сразу (1-4)")
        print("6 - временной анализ")
        print("7 - тесты")

        action = input(" > ")

        if action == '1':
            printFlag = getPrintFlag()
            getDiatanceMatrix(levenshteinDistance_m, printFlag)
        elif action == '2':
            getDistanceRec(levenshteinDistance_r)
        elif action == '3':
            printFlag = getPrintFlag()
            getDiatanceMatrix(damerauLevenshteinDistance_m, printFlag)
        elif action == '4':
            getDistanceRec(damerauLevenshteinDistance_r)
        elif action == '5':
            distances()
        elif action == '6':
            timeTest()
        elif action == '7':
            runTests()
        else:
            run = False


menu()
