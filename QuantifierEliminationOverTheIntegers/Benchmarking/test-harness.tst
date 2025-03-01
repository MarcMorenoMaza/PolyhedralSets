with(QuantifierEliminationOverZ):

###########################
## Tests form literature ##
###########################

##########
## T 15 ##
##########
f := &A([x]),&E([y]),&E([z]),&or(&and((x >= 2), (y < 5)), z <= 2);

QEoverZ(f, method = method, mode = mode);


##########
## T 16 ##
##########
f := &E([w]),&E([h]),&E([x]),&E([y]),&E([z]),&or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(f, method = method, mode = mode);


##########
## T 17 ##
##########
# Example 4.8 in https://arxiv.org/pdf/1608.08520
f := &A([a0]),&A([a1]),&E([b0]),&E([b1]),&and(&and(0 <= a0, a0 < t, 0 <= a1, a1<t), &and(0 <= b0, b1 < t), &and(t < 2*a0 + 3*b0 +7*b1, 2*a0 + 3*b0 +7*b1 <= 2*t), &and(2*t < a1 + 2*b1, a1 + 2*b1 <= 3*t));

QEoverZ(f, method = method, mode = mode);


##########
## T 18 ##
##########
# Example 1 from https://link.springer.com/chapter/10.1007/978-3-031-13188-2_12
sq := &E([x1]),&E([x2]);
f := &E([x3]),&E([x4]),&E([x5]),&or(&and(&or(&and(p1>=0, p1<0), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<0), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f, method = method, mode = mode);


##########
## T 19 ##
##########
# Page 10 Example from http://www.numdam.org/item/RO_1988__22_3_243_0.pdf
f := &E([i]),&E([j]),&and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(f, method = method, mode = mode);


##########
## T 20 ##
##########
# ISL Documentation manual page 275
sq := &A([n]),&E([a1]),&E([a2]);
f := &and(7*a1 = -2 + n, 5*a2 = -1 - x + y, y >= 6 + x);

QEoverZ(sq, f, method = method, mode = mode);


##########
## T 32 ##
##########
# Examples from Integer Affine Transformations https://doi.org/10.1145/2207222.2207224
# Example 3.1., page 8:6
f := &E([i]), &E([j]), &E([k]), &and(1 <= i, i <= N, 1 <= j, j <= N , 1 <= k, k <= N, x = 3*i + 6*k, y = 5*i + 2*j + 1);

QEoverZ(f, method = method, mode = mode);


##########
## T 33 ##
##########
# Example 3.3., page 8:8
f := &E([i]), &E([j]), &and( 1 <= i, i <= N, 1 <= j, j <= N, 1 <= x, x <= N, 3*i + 6*j = y, 5*i = -2*x + z - 1);

QEoverZ(f, method = method, mode = mode);


##########
## T 34 ##
##########
# Example 3.10., page 8:12
f := &E([y]), &and(2 <= 3*y - x,  3*y - x <= 5, -1 <= x - 2*y,  x - 2*y <= N - 1);

QEoverZ(f, method = method, mode = mode);


##########
## T 35 ##
##########
# Example 5.1., page 8:21
f := &E([y]), &and( 0 <= 3*y - x,  3*y - x <= 7, 1 <=  x - 2*y, x - 2*y <=  5);

QEoverZ(f, method = method, mode = mode);


##########
## T 36 ##
##########
# Example 5.2., pages 8:23 - 8:24
f := &E([i]), &E([j]), &E([k]), &E([l]), &or(&and(1 <= i, i <= n, i + 1 <= j, j <= n, x = 2*i + 3*j), &and(1 <= k, k <= n, 1 <= l, l <= k - 1, x = k + 2*l));

QEoverZ(f, method = method, mode = mode);


##########
## T 44 ##
##########
# ISL Documentation manual page 276
sq := &A([n]),&A([x]),&A([y]);
f := &and(n>=2,y<=1-n+b,a>=1+x);

QEoverZ(sq, f, method = method, mode = mode);


##########
## T 45 ##
##########
# ISL Documentation manual page 276
sq := &A([x]),&A([y]);
f := &and(a >= 1 + x, b <= 2 - n + x + y - a ,n >= 2);
QEoverZ(sq, f, method = method, mode = mode);


##########
## T 46 ##
##########
# ISL Documentation manual page 276
sq := &A([x]),&A([y]);
f := &and(7* a = -2+n , 6*a >=-x+y, 5*a <= -1-x+y);

QEoverZ(sq, f, method = method, mode = mode);




###############
## Our tests ##
###############

##########
## QE 6 ##
##########
sq := &E([w,h,x,y,z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f, method = method, mode = mode); 


###########
## QE 12 ##
###########
sq := &E([x1]),&E([x2]),&E([x3]),&E([x4]),&E([x5]);
f := &or(&and(&or(&and(p1>=0, p1<=-1), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<=-1), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f, method = method, mode = mode);


###########
## QE 19 ##
###########
sq := &A([w,h,x,y,z]); 
f := &and(x >= 2, y <= 5, z <= 2, w >= M);

QEoverZ(sq, f, method = method, mode = mode);


###########
## QE 20 ##
###########
sq := &A([w,h,x,y,z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f, method = method, mode = mode); 


###########
## QE 21 ##
###########
sq := &A([w,h,x,y,z]);
f := (x=0);

QEoverZ(sq, f, method = method, mode = mode);				
	

###########
## QE 26 ##
###########
sq := &A([x1]),&A([x2]),&A([x3]),&A([x4]),&A([x5]);
f := &or(&and(&or(&and(p1>=0, p1<=-1), x1 + 2*x2 <= 2), &or(&and(p2>=0, p2<=-1), 3*x3 + 4*x4 + 5*x5 = 2)), -x2 - x3 <=3);

QEoverZ(sq, f, method = method, mode = mode);			


###########
## QE 27 ##
###########
sq := &A([i]),&A([j]);
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f, method = method, mode = mode);			


###########
## QE 41 ##
###########
f := &A([i]), &A([j]), &A([k]), &and(1 <= i, i <= N, 1 <= j, j <= N , 1 <= k, k <= N, x = 3*i + 6*k, y = 5*i + 2*j + 1);

QEoverZ(f, method = method, mode = mode);


###########
## QE 42 ##
###########
sq := &A([w,h,x,y,z]); 
f := &or(&and(x >= 2, y <= 5, z <= 2, w >= M), h <= 6);

QEoverZ(sq, f, method = method, mode = mode);


##########
## QE43 ##
##########
sq := &E([i]),&A([j]);
f := &and(0 <= i, i <= m, 0 <= j, j <= n, -2*i - j - k + 2*m + n >= 0, 2*i + j + k - 2*m - n >= 0);

QEoverZ(sq, f, method = method, mode = mode);

