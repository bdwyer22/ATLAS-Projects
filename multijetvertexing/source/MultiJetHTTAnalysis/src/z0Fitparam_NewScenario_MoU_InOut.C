double getZ0ResParam_NewScenario_MoU_InOut(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<4.0) {
      z0Res += 87.01*pow(abstrketa, 0);
      z0Res += -118.05*pow(abstrketa, 1);
      z0Res += 986.83*pow(abstrketa, 2);
      z0Res += -1143.17*pow(abstrketa, 3);
      z0Res += 405.27*pow(abstrketa, 4);
      z0Res += -40.90*pow(abstrketa, 5);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.43)/0.56,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<4.0) {
      z0Res += 50.76*pow(abstrketa, 0);
      z0Res += -3.47*pow(abstrketa, 1);
      z0Res += 136.17*pow(abstrketa, 2);
      z0Res += -102.69*pow(abstrketa, 3);
      z0Res += 27.75*pow(abstrketa, 4);
      z0Res += 240.48*exp(-0.5*pow((abstrketa-2.43)/0.38,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<4.0) {
      z0Res += 34.69*pow(abstrketa, 0);
      z0Res += -43.09*pow(abstrketa, 1);
      z0Res += 80.61*pow(abstrketa, 2);
      z0Res += -23.82*pow(abstrketa, 3);
      z0Res += 0.29*pow(abstrketa, 4);
      z0Res += 1.85*pow(abstrketa, 5);
      z0Res += 117.37*exp(-0.5*pow((abstrketa-2.41)/0.29,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<4.0) {
      z0Res += 27.83*pow(abstrketa, 0);
      z0Res += -91.54*pow(abstrketa, 1);
      z0Res += 247.99*pow(abstrketa, 2);
      z0Res += -317.07*pow(abstrketa, 3);
      z0Res += 234.52*pow(abstrketa, 4);
      z0Res += -92.28*pow(abstrketa, 5);
      z0Res += 18.23*pow(abstrketa, 6);
      z0Res += -1.38*pow(abstrketa, 7);
      z0Res += 85.98*exp(-0.5*pow((abstrketa-2.38)/0.20,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<4.0) {
      z0Res += 23.53*pow(abstrketa, 0);
      z0Res += -97.29*pow(abstrketa, 1);
      z0Res += 287.65*pow(abstrketa, 2);
      z0Res += -399.10*pow(abstrketa, 3);
      z0Res += 300.58*pow(abstrketa, 4);
      z0Res += -119.63*pow(abstrketa, 5);
      z0Res += 23.77*pow(abstrketa, 6);
      z0Res += -1.83*pow(abstrketa, 7);
      z0Res += 88.39*exp(-0.5*pow((abstrketa-2.37)/0.17,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<4.0) {
      z0Res += 20.96*pow(abstrketa, 0);
      z0Res += -106.91*pow(abstrketa, 1);
      z0Res += 352.74*pow(abstrketa, 2);
      z0Res += -524.08*pow(abstrketa, 3);
      z0Res += 402.21*pow(abstrketa, 4);
      z0Res += -161.91*pow(abstrketa, 5);
      z0Res += 32.39*pow(abstrketa, 6);
      z0Res += -2.52*pow(abstrketa, 7);
      z0Res += 94.25*exp(-0.5*pow((abstrketa-2.36)/0.15,2));
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
