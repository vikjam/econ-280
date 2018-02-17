#------------#
# Exercise 1 #
#------------#

# Exercise 1a
A = [ 6 9  2;  1 8  2; -3  1 -6];
B = [-4 7 -7; -1 6 -5;  2 -5 -1];

# Exercise 1b
AB    = A * B;
A4    = A^4;
AinvB = A' * B^(-1);
B3    = B.^3;
A_B   = A ./ B;

# Exercise 1c
X = A^(-1) * B;

# Exercise 1d
C              = 2 .* A;
AplusB         = A .+ B;
C[AplusB .< 5] = 0;

# Exercise 1e
E11   = [-4 7 -7; -1 6 -5];
E12   = [ 9 2; 8 2; 1 -6];
E1ans = E11 * E12;

E21   = [1 9 2; 1 8 2; 1 1 -6];
E22   = [7; 6; -5];
E2ans = E21 * E22;

E31   = [-3 1 -6];
E32   = [6 9 2; 2 -5 -1; 1 8 2];
E3ans = E31 * E32;

