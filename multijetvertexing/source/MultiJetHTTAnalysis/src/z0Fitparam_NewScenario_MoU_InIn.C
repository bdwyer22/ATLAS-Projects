double getZ0ResParam_NewScenario_MoU_InIn(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<4.0) {
      z0Res += 60.35*pow(abstrketa, 0);
      z0Res += 73.49*pow(abstrketa, 1);
      z0Res += -271.01*pow(abstrketa, 2);
      z0Res += 445.65*pow(abstrketa, 3);
      z0Res += -187.01*pow(abstrketa, 4);
      z0Res += -5.68*pow(abstrketa, 5);
      z0Res += 18.11*pow(abstrketa, 6);
      z0Res += -2.50*pow(abstrketa, 7);
      z0Res += 397.77*exp(-0.5*pow((abstrketa-2.47)/0.34,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<4.0) {
      z0Res += 40.67*pow(abstrketa, 0);
      z0Res += 37.16*pow(abstrketa, 1);
      z0Res += -131.83*pow(abstrketa, 2);
      z0Res += 218.73*pow(abstrketa, 3);
      z0Res += -87.08*pow(abstrketa, 4);
      z0Res += -4.35*pow(abstrketa, 5);
      z0Res += 9.07*pow(abstrketa, 6);
      z0Res += -1.21*pow(abstrketa, 7);
      z0Res += 232.93*exp(-0.5*pow((abstrketa-2.47)/0.36,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<4.0) {
      z0Res += 29.26*pow(abstrketa, 0);
      z0Res += -16.48*pow(abstrketa, 1);
      z0Res += 21.44*pow(abstrketa, 2);
      z0Res += 23.64*pow(abstrketa, 3);
      z0Res += -14.84*pow(abstrketa, 4);
      z0Res += 3.50*pow(abstrketa, 5);
      z0Res += 106.99*exp(-0.5*pow((abstrketa-2.42)/0.31,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.4) {
      z0Res += 26.26*pow(abstrketa, 0);
      z0Res += -90.25*pow(abstrketa, 1);
      z0Res += 281.71*pow(abstrketa, 2);
      z0Res += -394.98*pow(abstrketa, 3);
      z0Res += 303.38*pow(abstrketa, 4);
      z0Res += -117.59*pow(abstrketa, 5);
      z0Res += 18.76*pow(abstrketa, 6);
    }
    if (abstrketa>=2.4 && abstrketa<4.0) {
      z0Res += 2826.23*pow(abstrketa, 0);
      z0Res += -1984.36*pow(abstrketa, 1);
      z0Res += 376.52*pow(abstrketa, 2);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<4.0) {
      z0Res += 24.14*pow(abstrketa, 0);
      z0Res += -113.48*pow(abstrketa, 1);
      z0Res += 353.51*pow(abstrketa, 2);
      z0Res += -496.20*pow(abstrketa, 3);
      z0Res += 368.31*pow(abstrketa, 4);
      z0Res += -143.69*pow(abstrketa, 5);
      z0Res += 27.96*pow(abstrketa, 6);
      z0Res += -2.11*pow(abstrketa, 7);
      z0Res += 87.81*exp(-0.5*pow((abstrketa-2.37)/0.16,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<4.0) {
      z0Res += 22.28*pow(abstrketa, 0);
      z0Res += -121.98*pow(abstrketa, 1);
      z0Res += 377.42*pow(abstrketa, 2);
      z0Res += -532.67*pow(abstrketa, 3);
      z0Res += 394.87*pow(abstrketa, 4);
      z0Res += -155.62*pow(abstrketa, 5);
      z0Res += 30.75*pow(abstrketa, 6);
      z0Res += -2.37*pow(abstrketa, 7);
      z0Res += 95.28*exp(-0.5*pow((abstrketa-2.36)/0.15,2));
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
