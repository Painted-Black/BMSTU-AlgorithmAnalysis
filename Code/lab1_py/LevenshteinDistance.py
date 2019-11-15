def printMatrix(matrix):
    l1 = len(matrix)
    l2 = len(matrix[0])

    for i in range(l1):
        s = ''
        for j in range(l2):
            s += str(matrix[i][j])
            s += '\t'
        s += '\n'
        print(s)


def levenshteinDistance_m(s1, s2, printMatr=False):
    l1 = len(s1) + 1
    l2 = len(s2) + 1

    matrix = []
    for i in range(l1):
        matrix.append([])
        for j in range(l2):
            matrix[i].append(0)

    for i in range(1, l2):
        matrix[0][i] = i

    for i in range(1, l1):
        matrix[i][0] = i

    for i in range(1, l1):
        for j in range(1, l2):
            r1 = matrix[i-1][j] + 1  # клетка сверху
            r2 = matrix[i][j-1] + 1  # клетка слева
            fine = 1
            if s1[i-1] == s2[j-1]:
                fine = 0
            r3 = matrix[i-1][j-1] + fine
            matrix[i][j] = min(r1, r2, r3)

    if printMatr:
        print("Матрица:")
        printMatrix(matrix)

    return matrix[l1-1][l2-1]


def levenshteinDistance_r(s1, s2):
    if len(s1) == 0 and len(s2) == 0:
        return 0
    if len(s1) == 0:
        return len(s2)
    if len(s2) == 0:
        return len(s1)

    r1 = levenshteinDistance_r(s1[:-1], s2) + 1
    r2 = levenshteinDistance_r(s1, s2[:-1]) + 1
    r3 = levenshteinDistance_r(s1[:-1], s2[:-1])
    if s1[len(s1) - 1] != s2[len(s2) - 1]:
        r3 += 1
    distance = min(r1, r2, r3)

    return distance


def damerauLevenshteinDistance_m(s1, s2, printMatr=False):
    l1 = len(s1) + 1
    l2 = len(s2) + 1

    matrix = []
    for i in range(l1):
        matrix.append([])
        for j in range(l2):
            matrix[i].append(0)

    for i in range(1, l2):
        matrix[0][i] = i

    for i in range(1, l1):
        matrix[i][0] = i

    for i in range(1, l1):
        for j in range(1, l2):
            r1 = matrix[i-1][j] + 1  # клетка сверху
            r2 = matrix[i][j-1] + 1  # клетка слева
            fine = 1
            if s1[i-1] == s2[j-1]:
                fine = 0
            r3 = matrix[i-1][j-1] + fine

            distance = min(r1, r2, r3)

            if i >= 2 and j >= 2:
                if s1[i-1] == s2[j-2] and s2[j-1] == s1[i-2]:
                    distance = min(distance, matrix[i-2][j-2] + 1)

            matrix[i][j] = distance

    if printMatr:
        print("Матрица:")
        printMatrix(matrix)

    return matrix[l1-1][l2-1]


def damerauLevenshteinDistance_r(s1, s2):
    if len(s1) == 0 and len(s2) == 0:
        return 0
    if len(s1) == 0:
        return len(s2)
    if len(s2) == 0:
        return len(s1)

    r1 = levenshteinDistance_r(s1[:-1], s2) + 1
    r2 = levenshteinDistance_r(s1, s2[:-1]) + 1
    r3 = levenshteinDistance_r(s1[:-1], s2[:-1])
    if s1[len(s1) - 1] != s2[len(s2) - 1]:
        r3 += 1
    distance = min(r1, r2, r3)

    if len(s1) >= 2 and len(s2) >= 2 and s1[len(s1) - 1] == s2[len(s2) - 2] and s1[len(s1) - 2] == s2[len(s2) - 1]:
        distance = min(distance, damerauLevenshteinDistance_r(s1[:-2], s2[:-2]) + 1)

    return distance
