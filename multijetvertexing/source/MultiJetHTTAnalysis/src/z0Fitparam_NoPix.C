double getZ0ResParam_NoPix(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.4) {
      z0Res += 1385.29*pow(abstrketa, 0);
      z0Res += 3730.50*pow(abstrketa, 1);
      z0Res += -23537.72*pow(abstrketa, 2);
      z0Res += 54359.45*pow(abstrketa, 3);
      z0Res += -53531.68*pow(abstrketa, 4);
      z0Res += 23873.68*pow(abstrketa, 5);
      z0Res += -3833.40*pow(abstrketa, 6);
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.4) {
      z0Res += 1195.85*pow(abstrketa, 0);
      z0Res += 2205.86*pow(abstrketa, 1);
      z0Res += -13336.68*pow(abstrketa, 2);
      z0Res += 26323.39*pow(abstrketa, 3);
      z0Res += -16781.53*pow(abstrketa, 4);
      z0Res += -1600.34*pow(abstrketa, 5);
      z0Res += 5016.64*pow(abstrketa, 6);
      z0Res += -1202.66*pow(abstrketa, 7);
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.0) {
      z0Res += 945.54*pow(abstrketa, 0);
      z0Res += 4206.21*pow(abstrketa, 1);
      z0Res += -32923.17*pow(abstrketa, 2);
      z0Res += 105153.03*pow(abstrketa, 3);
      z0Res += -165622.43*pow(abstrketa, 4);
      z0Res += 136931.15*pow(abstrketa, 5);
      z0Res += -56760.19*pow(abstrketa, 6);
      z0Res += 9326.94*pow(abstrketa, 7);
    }
    if (abstrketa>=2.0 && abstrketa<2.4) {
      z0Res += 73176.55*pow(abstrketa, 0);
      z0Res += -73662.95*pow(abstrketa, 1);
      z0Res += 21119.91*pow(abstrketa, 2);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.0) {
      z0Res += 826.51*pow(abstrketa, 0);
      z0Res += 4327.59*pow(abstrketa, 1);
      z0Res += -33923.98*pow(abstrketa, 2);
      z0Res += 110370.66*pow(abstrketa, 3);
      z0Res += -177753.28*pow(abstrketa, 4);
      z0Res += 149377.54*pow(abstrketa, 5);
      z0Res += -62543.68*pow(abstrketa, 6);
      z0Res += 10322.77*pow(abstrketa, 7);
    }
    if (abstrketa>=2.0 && abstrketa<2.4) {
      z0Res += 85410.08*pow(abstrketa, 0);
      z0Res += -85541.98*pow(abstrketa, 1);
      z0Res += 23855.35*pow(abstrketa, 2);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.0) {
      z0Res += 762.21*pow(abstrketa, 0);
      z0Res += 4505.27*pow(abstrketa, 1);
      z0Res += -34759.74*pow(abstrketa, 2);
      z0Res += 113171.74*pow(abstrketa, 3);
      z0Res += -183086.63*pow(abstrketa, 4);
      z0Res += 154272.61*pow(abstrketa, 5);
      z0Res += -64624.51*pow(abstrketa, 6);
      z0Res += 10651.43*pow(abstrketa, 7);
    }
    if (abstrketa>=2.0 && abstrketa<2.4) {
      z0Res += 91675.19*pow(abstrketa, 0);
      z0Res += -91616.18*pow(abstrketa, 1);
      z0Res += 25253.35*pow(abstrketa, 2);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.0) {
      z0Res += 707.25*pow(abstrketa, 0);
      z0Res += 4872.00*pow(abstrketa, 1);
      z0Res += -36560.74*pow(abstrketa, 2);
      z0Res += 117773.86*pow(abstrketa, 3);
      z0Res += -189497.61*pow(abstrketa, 4);
      z0Res += 158892.80*pow(abstrketa, 5);
      z0Res += -66222.32*pow(abstrketa, 6);
      z0Res += 10856.85*pow(abstrketa, 7);
    }
    if (abstrketa>=2.0 && abstrketa<2.4) {
      z0Res += 96210.41*pow(abstrketa, 0);
      z0Res += -96007.34*pow(abstrketa, 1);
      z0Res += 26263.53*pow(abstrketa, 2);
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
