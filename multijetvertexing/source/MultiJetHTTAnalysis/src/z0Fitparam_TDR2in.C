double getZ0ResParam_TDR2in(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.8) {
      z0Res += 1134.38*pow(abstrketa, 0);
      z0Res += -403.44*pow(abstrketa, 1);
      z0Res += 2523.25*pow(abstrketa, 2);
      z0Res += -2235.70*pow(abstrketa, 3);
      z0Res += 604.31*pow(abstrketa, 4);
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.8) {
      z0Res += 823.94*pow(abstrketa, 0);
      z0Res += -1443.28*pow(abstrketa, 1);
      z0Res += 4702.95*pow(abstrketa, 2);
      z0Res += -4565.12*pow(abstrketa, 3);
      z0Res += 1713.81*pow(abstrketa, 4);
      z0Res += -197.51*pow(abstrketa, 5);
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.8) {
      z0Res += 514.15*pow(abstrketa, 0);
      z0Res += -689.21*pow(abstrketa, 1);
      z0Res += 2352.41*pow(abstrketa, 2);
      z0Res += -2381.49*pow(abstrketa, 3);
      z0Res += 916.41*pow(abstrketa, 4);
      z0Res += -107.20*pow(abstrketa, 5);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.8) {
      z0Res += 337.23*pow(abstrketa, 0);
      z0Res += 362.36*pow(abstrketa, 1);
      z0Res += -2221.81*pow(abstrketa, 2);
      z0Res += 5217.70*pow(abstrketa, 3);
      z0Res += -5005.11*pow(abstrketa, 4);
      z0Res += 1965.53*pow(abstrketa, 5);
      z0Res += -265.60*pow(abstrketa, 6);
      z0Res += 689.43*exp(-0.5*pow((abstrketa-2.05)/0.39,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.0) {
      z0Res += 283.66*pow(abstrketa, 0);
      z0Res += 461.94*pow(abstrketa, 1);
      z0Res += -2748.95*pow(abstrketa, 2);
      z0Res += 6437.60*pow(abstrketa, 3);
      z0Res += -6737.58*pow(abstrketa, 4);
      z0Res += 3158.86*pow(abstrketa, 5);
      z0Res += -543.32*pow(abstrketa, 6);
    }
    if (abstrketa>=2.0 && abstrketa<2.8) {
      z0Res += -159.46*pow(abstrketa, 0);
      z0Res += 210.77*pow(abstrketa, 1);
      z0Res += 164.26*exp(-0.5*pow((abstrketa-2.73)/0.18,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.8) {
      z0Res += 285.21*pow(abstrketa, 0);
      z0Res += -154.92*pow(abstrketa, 1);
      z0Res += 391.87*pow(abstrketa, 2);
      z0Res += -230.07*pow(abstrketa, 3);
      z0Res += -123.98*pow(abstrketa, 4);
      z0Res += 56.94*pow(abstrketa, 5);
      z0Res += 23.74*pow(abstrketa, 6);
      z0Res += -8.43*pow(abstrketa, 7);
      z0Res += 174.58*exp(-0.5*pow((abstrketa-2.00)/0.33,2));
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
