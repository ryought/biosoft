#!/usr/bin/env python
import pprint

def main():
    A = "GGGAAAUCC"
    nussinov(A)

def s(x, y):
    if (x == "A" and y == "U") or (x == "U" and y == "A"):
        return 1
    elif (x == "G" and y == "C") or (x == "C" and y == "G"):
        return 1
    else:
        return 0
    
def nussinov(A):
    S = [[0 for _ in range(len(A))] for _ in range(len(A))]
    # initial
    for i in range(len(A)):
        S[i][i] = 0

    # step length of substring
    for k in range(2, len(A)+1):
        # starting position
        for i in range(0, len(A)-k+1):
            j = i+k-1
            # DP
            S[i][j] = max(
                    S[i+1][j], 
                    S[i][j-1], 
                    S[i+1][j-1] + s(A[i], A[j]), 
                    max([S[i][t]+S[t+1][j] for t in range(i,j)])
                    )
    pprint.pprint(S)


if __name__ == "__main__":
    main()
