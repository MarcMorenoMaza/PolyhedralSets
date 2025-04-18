with(QuantifierEliminationOverZ):

# Add <method name> with integerpointdecomposition or numberofintegerpoints
# Add <mode name> with onequantifieratatime or byblockofquantifiers

###########################
## Tests form literature ##
###########################

#########
## T 1 ##
#########
# Example 1.11 https://arxiv.org/pdf/1608.08520     Page 4

sq := &A([t]), &E([x]);
f := &and(2*x + 2*y + 3 = 5*t, x <= t, t <= y); 

QEoverZ(sq, f);     


#########
## T 2 ##
#########
# Example 2.1 https://arxiv.org/pdf/1608.08520      Page 7

sq := &E([y]);
f := &and(x + y <= z, y >= 3, x <= z - 3);

QEoverZ(sq, f);     


#########
## T 3 ##
#########
# Example 2.3 https://arxiv.org/pdf/1608.08520      Page 8

sq := &E([y]);
f := &and(x + 1 <= 2*y, 2*y <= z, 2*y <= 3*z - x);

QEoverZ(sq, f);


#########
## T 4 ##
#########
# https://arxiv.org/pdf/1608.08520        Page 19

sq := &E([y]);
f := &and(x >= 0, y >= 0, x + y <= 2);

QEoverZ(sq, f);


#########
## T 5 ##
#########
# https://arxiv.org/pdf/1608.08520        Page 19

sq := &E([y]);
f := &and(x >= 0, w >= 0, y >= 0, x + y + w = 2);

QEoverZ(sq, f);


#########
## T 6 ##
#########
# Example 3.11., https://doi.org/10.1145/2207222.2207224      Page 8:12

sq := &E([y]);
f := &and(x - N - 2 <= 2*y, 4*y <= x + 5);

QEoverZ(sq, f);


#########
## T 7 ##
#########
# Example An_Implementation_of_the_Barvinok–Woods_Integer_Projection_Algorithm.pdf    Page 16

sq := &E([i]), &E([j]);
f := &and(l = 6*i + 9*j -7, 1 <=j, j <= p, 1 <= i, i <= 8);

QEoverZ(sq, f);


#########
## T 8 ##
#########
# Equation 6.7 https://www.mpi-inf.mpg.de/fileadmin/inf/rg1/Documents/2023-07-14-lnqe.pdf Page 56

sq := &A([x1]), &A([x2]), &E([y]);
f := &implies(x1 + 1 < x2, &and(x1 < y, y < x2));  ## Maple demo (Thomas Sturm)

QEoverZ(sq, f);     


#########
## T 9 ##
#########
# Equation 7.59 https://www.mpi-inf.mpg.de/fileadmin/inf/rg1/Documents/2023-07-14-lnqe.pdf    Page 70

sq := &E([x1]), &E([x2]);
f := &and(c <= 3*x1 + 4*x2, 3*x1 + 2*x2 <= 500*v, -x1 <= 0, x1 <= 100*v, -x2 <= 0, x2 <= 200*v);

QEoverZ(sq, f);  


##########
## T 15 ##
##########
sq := &A([x]),&E([y]),&E([z]);
f := &or(&and((x >= 2), (y < 5)), z <= 2);

QEoverZ(sq, f);


##########
## T 16 ##
##########
sq := &E([w]),&E([h]),&E([x]),&E([y]),&E([z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f);


##########
## T 17 ##
##########
# Example 4.8 in https://arxiv.org/pdf/1608.08520

sq := &A([a0]),&A([a1]),&E([b0]),&E([b1]);
f := &and(&and(0 <= a0, a0 < t, 0 <= a1, a1<t), &and(0 <= b0, b1 < t), &and(t < 2*a0 + 3*b0 +7*b1, 2*a0 + 3*b0 +7*b1 <= 2*t), &and(2*t < a1 + 2*b1, a1 + 2*b1 <= 3*t));

QEoverZ(sq, f); 


##########
## T 18 ##
##########
# Example 1 from https://link.springer.com/chapter/10.1007/978-3-031-13188-2_12

sq := &A([p1,p2]),  &E([x1]),&E([x2]),&E([x3]),&E([x4]),&E([x5]);
f := &or(&and(&or(&and(p1>=0, p1<0), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<0), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f); ## Maple demo
                 ## CAV 2022 paper 
                 ## Shaowei Cai1, Bohan Li, and Xindi Zhang


##########
## T 19 ##
##########
# Page 10 Example from http://www.numdam.org/item/RO_1988__22_3_243_0.pdf

sq := &E([i]),&E([j]); 
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f);


##########
## T 20 ##
##########
# ISL Documentation manual page 275

sq := &A([n]),&E([a1]),&E([a2]);
f := &and(7*a1 = -2 + n, 5*a2 = -1 - x + y, y >= 6 + x);

QEoverZ(sq, f);			


##########
## T 32 ##
##########
# Examples from Integer Affine Transformations https://doi.org/10.1145/2207222.2207224
# Example 3.1., page 8:6

sq := &E([i]), &E([j]), &E([k]); 
f := &and(1 <= i, i <= N, 1 <= j, j <= N , 1 <= k, k <= N, x = 3*i + 6*k, y = 5*i + 2*j + 1);

QEoverZ(sq, f);  


##########
## T 33 ##
##########
# Example 3.3., page 8:8

sq := &E([i]), &E([j]); 
f := &and( 1 <= i, i <= N, 1 <= j, j <= N, 1 <= x, x <= N, 3*i + 6*j = y, 5*i = -2*x + z - 1);

QEoverZ(sq, f);


##########
## T 34 ##
##########
# Example 3.10., page 8:12

sq := &E([y]);
f := &and(2 <= 3*y - x,  3*y - x <= 5, -1 <= x - 2*y,  x - 2*y <= N - 1);

QEoverZ(sq, f);


##########
## T 35 ##
##########
# Example 5.1., page 8:21

sq := &E([y]); 
f := &and( 0 <= 3*y - x,  3*y - x <= 7, 1 <=  x - 2*y, x - 2*y <=  5);

QEoverZ(sq, f);


##########
## T 36 ##
##########
# Example 5.2., pages 8:23 - 8:24

sq := &E([i]), &E([j]), &E([k]), &E([l]); 
f := &or(&and(1 <= i, i <= n, i + 1 <= j, j <= n, x = 2*i + 3*j), &and(1 <= k, k <= n, 1 <= l, l <= k - 1, x = k + 2*l));

QEoverZ(sq, f);  


##########
## T 44 ##
##########
# ISL Documentation manual page 276

sq := &A([n]),&A([x]),&A([y]);
f := &and(n>=2,y<=1-n+b,a>=1+x);

QEoverZ(sq, f);


##########
## T 45 ##
##########
# ISL Documentation manual page 276

sq := &A([x]),&A([y]);
f := &and(a >= 1 + x, b <= 2 - n + x + y - a ,n >= 2);

QEoverZ(sq, f);


##########
## T 46 ##
##########
# ISL Documentation manual page 276

sq := &A([x]),&A([y]);
f := &and(7* a = -2+n , 6*a >=-x+y, 5*a <= -1-x+y);

QEoverZ(sq, f);


#########
## T47 ##
#########
# https://www.impact-workshop.org/impact2015/papers/impact2015-verdoolaege.pdf
# Example 5.1

sq := &E([a]);
f := &or(&and(x-1 <= 3*a, 3*a <= x), x-2 = 3*a);

QEoverZ(sq, f);

#########
## T48 ##
#########
# Example 5.2

sq := &E([j]);
f := &or(&and(i = 4*j, 0 <= i, i <= 100), &and(4*j + 1 <= i, i <= 4*j + 2,  0 <= i, i <= 100));

QEoverZ(sq, f);


#########
## T49 ##
#########
# Example 5.3

sq := &E([a]);
f := &or(&and(0 <= x, x <= 100), &and(5 <= x, x <= 40, x = 5*a));

QEoverZ(sq, f);


###############
## Our tests ##
###############

##########
## QE 5 ##
##########
# MODIFIED Example Integer Affine Transformations https://doi.org/10.1145/2207222.2207224 Page 8.22

sq := &E([i]), &E([j]), &E([k]), &E([l]);
f := &and(0<=i, i <=m, 0<=j, j<=m, 0<=k, k<=m, 0<=l, l<=m, &or(&not(i=k), &not(j=l)), &not(i+j = k+l));

QEoverZ(sq, f); 


##########
## QE 6 ##
##########
sq := &E([w,h,x,y,z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f); 


###########
## QE 12 ##
###########
sq := &E([x1]),&E([x2]),&E([x3]),&E([x4]),&E([x5]);
f := &or(&and(&or(&and(p1>=0, p1<=-1), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<=-1), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f);


###########
## QE 13 ##
###########
sq := &E([i]),&E([j]);
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f);


###########
## QE 19 ##
###########
sq := &A([w,h,x,y,z]); 
f := &and(x >= 2, y <= 5, z <= 2, w >= M);

QEoverZ(sq, f);


###########
## QE 20 ##
###########
sq := &A([w,h,x,y,z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f); 


###########
## QE 21 ##
###########
sq := &A([w,h,x,y,z]);
f := (x=0);

QEoverZ(sq, f);				
	

###########
## QE 26 ##
###########
sq := &A([x1]),&A([x2]),&A([x3]),&A([x4]),&A([x5]);
f := &or(&and(&or(&and(p1>=0, p1<=-1), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<=-1), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f);			


###########
## QE 27 ##
###########
sq := &A([i]),&A([j]);
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f);			


###########
## QE 28 ##
###########
sq := &A([i]),&A([j]);
f := [i - j >= - m, i + j <= n,  p <= j];

QEoverZ(sq, f);		


###########
## QE 41 ##
###########
sq := &A([i]), &A([j]), &A([k]); 
f := &and(1 <= i, i <= N, 1 <= j, j <= N , 1 <= k, k <= N, x = 3*i + 6*k, y = 5*i + 2*j + 1);

QEoverZ(sq, f);


###########
## QE 43 ##
###########
sq := &E([i]),&A([j]);
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f);