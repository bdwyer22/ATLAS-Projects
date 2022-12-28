double getZ0ResParam_NewScenario_MoU_OutOut(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.4) {
      z0Res += 277.34*pow(abstrketa, 0);
      z0Res += -1505.76*pow(abstrketa, 1);
      z0Res += 9407.34*pow(abstrketa, 2);
      z0Res += -23140.18*pow(abstrketa, 3);
      z0Res += 28607.75*pow(abstrketa, 4);
      z0Res += -17768.32*pow(abstrketa, 5);
      z0Res += 5267.60*pow(abstrketa, 6);
      z0Res += -579.25*pow(abstrketa, 7);
    }
    if (abstrketa>=2.4 && abstrketa<4.0) {
      z0Res += -62699.60*pow(abstrketa, 0);
      z0Res += 2439643.78*pow(abstrketa, 1);
      z0Res += -3943468.06*pow(abstrketa, 2);
      z0Res += 2577673.66*pow(abstrketa, 3);
      z0Res += -839499.36*pow(abstrketa, 4);
      z0Res += 135777.57*pow(abstrketa, 5);
      z0Res += -8713.71*pow(abstrketa, 6);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.95)/0.15,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.9) {
      z0Res += 125.38*pow(abstrketa, 0);
      z0Res += -74.21*pow(abstrketa, 1);
      z0Res += 1628.39*pow(abstrketa, 2);
      z0Res += -5678.10*pow(abstrketa, 3);
      z0Res += 8787.82*pow(abstrketa, 4);
      z0Res += -6247.33*pow(abstrketa, 5);
      z0Res += 2058.91*pow(abstrketa, 6);
      z0Res += -253.19*pow(abstrketa, 7);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.34)/0.15,2));
    }
    if (abstrketa>=2.9 && abstrketa<4.0) {
      z0Res += 493066.76*pow(abstrketa, 0);
      z0Res += -408682.97*pow(abstrketa, 1);
      z0Res += 112521.84*pow(abstrketa, 2);
      z0Res += -10229.18*pow(abstrketa, 3);
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.9) {
      z0Res += 83.42*pow(abstrketa, 0);
      z0Res += -322.74*pow(abstrketa, 1);
      z0Res += 2352.48*pow(abstrketa, 2);
      z0Res += -6264.72*pow(abstrketa, 3);
      z0Res += 7973.40*pow(abstrketa, 4);
      z0Res += -4940.32*pow(abstrketa, 5);
      z0Res += 1453.99*pow(abstrketa, 6);
      z0Res += -162.13*pow(abstrketa, 7);
      z0Res += 967.91*exp(-0.5*pow((abstrketa-2.37)/0.19,2));
    }
    if (abstrketa>=2.9 && abstrketa<4.0) {
      z0Res += 284947.78*pow(abstrketa, 0);
      z0Res += -236934.09*pow(abstrketa, 1);
      z0Res += 65447.31*pow(abstrketa, 2);
      z0Res += -5971.62*pow(abstrketa, 3);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.3) {
      z0Res += 54.13*pow(abstrketa, 0);
      z0Res += -302.51*pow(abstrketa, 1);
      z0Res += 1865.43*pow(abstrketa, 2);
      z0Res += -4693.09*pow(abstrketa, 3);
      z0Res += 5713.90*pow(abstrketa, 4);
      z0Res += -3392.43*pow(abstrketa, 5);
      z0Res += 931.56*pow(abstrketa, 6);
      z0Res += -89.90*pow(abstrketa, 7);
    }
    if (abstrketa>=2.3 && abstrketa<4.0) {
      z0Res += -199767.71*pow(abstrketa, 0);
      z0Res += 275463.25*pow(abstrketa, 1);
      z0Res += -138974.61*pow(abstrketa, 2);
      z0Res += 30515.26*pow(abstrketa, 3);
      z0Res += -2462.72*pow(abstrketa, 4);
      z0Res += 700.97*exp(-0.5*pow((abstrketa-2.96)/0.20,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.3) {
      z0Res += 33.60*pow(abstrketa, 0);
      z0Res += -132.74*pow(abstrketa, 1);
      z0Res += 649.77*pow(abstrketa, 2);
      z0Res += -1451.31*pow(abstrketa, 3);
      z0Res += 1597.14*pow(abstrketa, 4);
      z0Res += -794.80*pow(abstrketa, 5);
      z0Res += 145.38*pow(abstrketa, 6);
    }
    if (abstrketa>=2.3 && abstrketa<4.0) {
      z0Res += -21968.24*pow(abstrketa, 0);
      z0Res += 19794.23*pow(abstrketa, 1);
      z0Res += -1909.81*pow(abstrketa, 2);
      z0Res += -1788.70*pow(abstrketa, 3);
      z0Res += 15.52*pow(abstrketa, 4);
      z0Res += 197.28*pow(abstrketa, 5);
      z0Res += -28.70*pow(abstrketa, 6);
      z0Res += 303.25*exp(-0.5*pow((abstrketa-2.96)/0.18,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.3) {
      z0Res += 23.36*pow(abstrketa, 0);
      z0Res += -102.95*pow(abstrketa, 1);
      z0Res += 366.49*pow(abstrketa, 2);
      z0Res += -681.78*pow(abstrketa, 3);
      z0Res += 684.25*pow(abstrketa, 4);
      z0Res += -329.48*pow(abstrketa, 5);
      z0Res += 59.94*pow(abstrketa, 6);
    }
    if (abstrketa>=2.3 && abstrketa<4.0) {
      z0Res += -4265.55*pow(abstrketa, 0);
      z0Res += 3323.28*pow(abstrketa, 1);
      z0Res += 1925.64*pow(abstrketa, 2);
      z0Res += -2345.10*pow(abstrketa, 3);
      z0Res += 696.98*pow(abstrketa, 4);
      z0Res += -66.26*pow(abstrketa, 5);
      z0Res += 96.74*exp(-0.5*pow((abstrketa-2.94)/0.16,2));
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
