double getZ0ResParam_MoU2in(float abstrketa, float trkpt, bool debug=0) {

  double z0Res = -1;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.8) {
      z0Res += 1289.71*pow(abstrketa, 0);
      z0Res += -2304.80*pow(abstrketa, 1);
      z0Res += 9224.76*pow(abstrketa, 2);
      z0Res += -12624.62*pow(abstrketa, 3);
      z0Res += 6951.04*pow(abstrketa, 4);
      z0Res += 122.61*pow(abstrketa, 5);
      z0Res += -1140.37*pow(abstrketa, 6);
      z0Res += 236.75*pow(abstrketa, 7);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.03)/0.15,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.8) {
      z0Res += 826.83*pow(abstrketa, 0);
      z0Res += -1840.70*pow(abstrketa, 1);
      z0Res += 8250.35*pow(abstrketa, 2);
      z0Res += -14017.04*pow(abstrketa, 3);
      z0Res += 11546.39*pow(abstrketa, 4);
      z0Res += -4273.51*pow(abstrketa, 5);
      z0Res += 577.49*pow(abstrketa, 6);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.04)/0.15,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.2) {
      z0Res += 476.57*pow(abstrketa, 0);
      z0Res += -46.57*pow(abstrketa, 1);
      z0Res += -335.50*pow(abstrketa, 2);
      z0Res += 2176.35*pow(abstrketa, 3);
      z0Res += -2987.16*pow(abstrketa, 4);
      z0Res += 1663.90*pow(abstrketa, 5);
      z0Res += -299.97*pow(abstrketa, 6);
    }
    if (abstrketa>=2.2 && abstrketa<2.8) {
      z0Res += 327616.26*pow(abstrketa, 0);
      z0Res += -383141.52*pow(abstrketa, 1);
      z0Res += 149360.23*pow(abstrketa, 2);
      z0Res += -19289.58*pow(abstrketa, 3);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.2) {
      z0Res += 362.04*pow(abstrketa, 0);
      z0Res += -184.83*pow(abstrketa, 1);
      z0Res += 742.70*pow(abstrketa, 2);
      z0Res += -896.38*pow(abstrketa, 3);
      z0Res += 394.05*pow(abstrketa, 4);
    }
    if (abstrketa>=2.2 && abstrketa<2.8) {
      z0Res += 162749.24*pow(abstrketa, 0);
      z0Res += -190012.68*pow(abstrketa, 1);
      z0Res += 73994.36*pow(abstrketa, 2);
      z0Res += -9549.95*pow(abstrketa, 3);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.2) {
      z0Res += 301.29*pow(abstrketa, 0);
      z0Res += -9.71*pow(abstrketa, 1);
      z0Res += 179.91*pow(abstrketa, 2);
      z0Res += -378.72*pow(abstrketa, 3);
      z0Res += 225.68*pow(abstrketa, 4);
      z0Res += 440.77*exp(-0.5*pow((abstrketa-2.06)/0.15,2));
    }
    if (abstrketa>=2.2 && abstrketa<2.8) {
      z0Res += 8578.41*pow(abstrketa, 0);
      z0Res += -6576.76*pow(abstrketa, 1);
      z0Res += 1341.90*pow(abstrketa, 2);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.2) {
      z0Res += 268.86*pow(abstrketa, 0);
      z0Res += 102.01*pow(abstrketa, 1);
      z0Res += -597.95*pow(abstrketa, 2);
      z0Res += 1276.91*pow(abstrketa, 3);
      z0Res += -1051.94*pow(abstrketa, 4);
      z0Res += -64.74*pow(abstrketa, 5);
      z0Res += 457.26*pow(abstrketa, 6);
      z0Res += -135.82*pow(abstrketa, 7);
      z0Res += 1000.00*exp(-0.5*pow((abstrketa-2.15)/0.15,2));
    }
    if (abstrketa>=2.2 && abstrketa<2.8) {
      z0Res += -62807.72*pow(abstrketa, 0);
      z0Res += 77296.32*pow(abstrketa, 1);
      z0Res += -31448.99*pow(abstrketa, 2);
      z0Res += 4245.58*pow(abstrketa, 3);
    }
  }

  if (debug) printf("z0Res = %f\n", z0Res);
  return z0Res;
}
