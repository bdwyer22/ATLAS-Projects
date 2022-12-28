double getZ0ResParam_L0_L1_InIn(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<4.0) {
      z0Res += 58.39*pow(abstrketa, 0);
      z0Res += 135.03*pow(abstrketa, 1);
      z0Res += -445.63*pow(abstrketa, 2);
      z0Res += 584.68*pow(abstrketa, 3);
      z0Res += -208.06*pow(abstrketa, 4);
      z0Res += -13.75*pow(abstrketa, 5);
      z0Res += 20.22*pow(abstrketa, 6);
      z0Res += -2.58*pow(abstrketa, 7);
      z0Res += 422.03*exp(-0.5*pow((abstrketa-2.47)/0.22,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<4.0) {
      z0Res += 40.66*pow(abstrketa, 0);
      z0Res += 43.66*pow(abstrketa, 1);
      z0Res += -172.95*pow(abstrketa, 2);
      z0Res += 265.78*pow(abstrketa, 3);
      z0Res += -99.09*pow(abstrketa, 4);
      z0Res += -6.52*pow(abstrketa, 5);
      z0Res += 10.19*pow(abstrketa, 6);
      z0Res += -1.31*pow(abstrketa, 7);
      z0Res += 250.16*exp(-0.5*pow((abstrketa-2.46)/0.27,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<4.0) {
      z0Res += 29.21*pow(abstrketa, 0);
      z0Res += -13.87*pow(abstrketa, 1);
      z0Res += -5.69*pow(abstrketa, 2);
      z0Res += 65.95*pow(abstrketa, 3);
      z0Res += -30.01*pow(abstrketa, 4);
      z0Res += -2.03*pow(abstrketa, 5);
      z0Res += 3.70*pow(abstrketa, 6);
      z0Res += -0.48*pow(abstrketa, 7);
      z0Res += 149.92*exp(-0.5*pow((abstrketa-2.43)/0.30,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<4.0) {
      z0Res += 27.10*pow(abstrketa, 0);
      z0Res += -97.89*pow(abstrketa, 1);
      z0Res += 305.97*pow(abstrketa, 2);
      z0Res += -428.98*pow(abstrketa, 3);
      z0Res += 329.07*pow(abstrketa, 4);
      z0Res += -132.18*pow(abstrketa, 5);
      z0Res += 26.40*pow(abstrketa, 6);
      z0Res += -2.03*pow(abstrketa, 7);
      z0Res += 97.32*exp(-0.5*pow((abstrketa-2.38)/0.21,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<4.0) {
      z0Res += 24.09*pow(abstrketa, 0);
      z0Res += -103.80*pow(abstrketa, 1);
      z0Res += 318.13*pow(abstrketa, 2);
      z0Res += -444.87*pow(abstrketa, 3);
      z0Res += 332.85*pow(abstrketa, 4);
      z0Res += -131.39*pow(abstrketa, 5);
      z0Res += 25.90*pow(abstrketa, 6);
      z0Res += -1.98*pow(abstrketa, 7);
      z0Res += 94.45*exp(-0.5*pow((abstrketa-2.35)/0.18,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<4.0) {
      z0Res += 22.20*pow(abstrketa, 0);
      z0Res += -109.01*pow(abstrketa, 1);
      z0Res += 332.23*pow(abstrketa, 2);
      z0Res += -469.99*pow(abstrketa, 3);
      z0Res += 352.23*pow(abstrketa, 4);
      z0Res += -140.44*pow(abstrketa, 5);
      z0Res += 28.04*pow(abstrketa, 6);
      z0Res += -2.18*pow(abstrketa, 7);
      z0Res += 98.39*exp(-0.5*pow((abstrketa-2.35)/0.17,2));
    }
  }

  if (trkpt>=100.0 && trkpt<150.0) {
    if (abstrketa<4.0) {
      z0Res += 21.76*pow(abstrketa, 0);
      z0Res += -110.21*pow(abstrketa, 1);
      z0Res += 335.30*pow(abstrketa, 2);
      z0Res += -475.59*pow(abstrketa, 3);
      z0Res += 356.78*pow(abstrketa, 4);
      z0Res += -142.73*pow(abstrketa, 5);
      z0Res += 28.61*pow(abstrketa, 6);
      z0Res += -2.24*pow(abstrketa, 7);
      z0Res += 99.70*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (trkpt>=150.0 && trkpt<200.0) {
    if (abstrketa<4.0) {
      z0Res += 21.67*pow(abstrketa, 0);
      z0Res += -110.44*pow(abstrketa, 1);
      z0Res += 335.87*pow(abstrketa, 2);
      z0Res += -476.64*pow(abstrketa, 3);
      z0Res += 357.66*pow(abstrketa, 4);
      z0Res += -143.18*pow(abstrketa, 5);
      z0Res += 28.73*pow(abstrketa, 6);
      z0Res += -2.25*pow(abstrketa, 7);
      z0Res += 99.98*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (trkpt>=200.0 && trkpt<300.0) {
    if (abstrketa<4.0) {
      z0Res += 21.61*pow(abstrketa, 0);
      z0Res += -110.60*pow(abstrketa, 1);
      z0Res += 336.26*pow(abstrketa, 2);
      z0Res += -477.36*pow(abstrketa, 3);
      z0Res += 358.25*pow(abstrketa, 4);
      z0Res += -143.49*pow(abstrketa, 5);
      z0Res += 28.81*pow(abstrketa, 6);
      z0Res += -2.26*pow(abstrketa, 7);
      z0Res += 100.18*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (trkpt>=300.0 && trkpt<500.0) {
    if (abstrketa<4.0) {
      z0Res += 21.55*pow(abstrketa, 0);
      z0Res += -110.74*pow(abstrketa, 1);
      z0Res += 336.58*pow(abstrketa, 2);
      z0Res += -477.96*pow(abstrketa, 3);
      z0Res += 358.74*pow(abstrketa, 4);
      z0Res += -143.75*pow(abstrketa, 5);
      z0Res += 28.87*pow(abstrketa, 6);
      z0Res += -2.26*pow(abstrketa, 7);
      z0Res += 100.36*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (trkpt>=500.0 && trkpt<750.0) {
    if (abstrketa<4.0) {
      z0Res += 21.52*pow(abstrketa, 0);
      z0Res += -110.82*pow(abstrketa, 1);
      z0Res += 336.77*pow(abstrketa, 2);
      z0Res += -478.31*pow(abstrketa, 3);
      z0Res += 359.03*pow(abstrketa, 4);
      z0Res += -143.90*pow(abstrketa, 5);
      z0Res += 28.91*pow(abstrketa, 6);
      z0Res += -2.27*pow(abstrketa, 7);
      z0Res += 100.48*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (trkpt>=750.0) {
    if (abstrketa<4.0) {
      z0Res += 21.50*pow(abstrketa, 0);
      z0Res += -110.87*pow(abstrketa, 1);
      z0Res += 336.86*pow(abstrketa, 2);
      z0Res += -478.48*pow(abstrketa, 3);
      z0Res += 359.17*pow(abstrketa, 4);
      z0Res += -143.98*pow(abstrketa, 5);
      z0Res += 28.93*pow(abstrketa, 6);
      z0Res += -2.27*pow(abstrketa, 7);
      z0Res += 100.53*exp(-0.5*pow((abstrketa-2.34)/0.17,2));
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
