double getD0ResParam_TDR2in(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.8) {
      d0Res += 822.38*pow(abstrketa, 0);
      d0Res += -148.46*pow(abstrketa, 1);
      d0Res += 31.73*pow(abstrketa, 2);
      d0Res += 19.87*pow(abstrketa, 3);
      d0Res += 3.72*pow(abstrketa, 4);
      d0Res += -5.43*pow(abstrketa, 5);
      d0Res += 311.79*exp(-0.5*pow((abstrketa-1.02)/0.34,2));
      d0Res += 945.98*exp(-0.5*pow((abstrketa-2.99)/0.48,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.8) {
      d0Res += 497.44*pow(abstrketa, 0);
      d0Res += -25.57*pow(abstrketa, 1);
      d0Res += 182.39*exp(-0.5*pow((abstrketa-1.07)/0.31,2));
      d0Res += 382.14*exp(-0.5*pow((abstrketa-2.76)/0.35,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.8) {
      d0Res += 259.51*pow(abstrketa, 0);
      d0Res += 72.04*pow(abstrketa, 1);
      d0Res += -53.29*pow(abstrketa, 2);
      d0Res += 88.95*exp(-0.5*pow((abstrketa-1.13)/0.26,2));
      d0Res += 462.19*exp(-0.5*pow((abstrketa-3.00)/0.53,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.0) {
      d0Res += 146.47*pow(abstrketa, 0);
      d0Res += -12.98*pow(abstrketa, 1);
      d0Res += 32.16*pow(abstrketa, 2);
      d0Res += 95.16*pow(abstrketa, 3);
      d0Res += -73.53*pow(abstrketa, 4);
      d0Res += 295.66*exp(-0.5*pow((abstrketa-2.04)/0.19,2));
    }
    if (abstrketa>=2.0 && abstrketa<2.8) {
      d0Res += 9081.63*pow(abstrketa, 0);
      d0Res += -11559.96*pow(abstrketa, 1);
      d0Res += 4918.78*pow(abstrketa, 2);
      d0Res += -684.60*pow(abstrketa, 3);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.0) {
      d0Res += 87.65*pow(abstrketa, 0);
      d0Res += 9.75*pow(abstrketa, 1);
      d0Res += -55.49*pow(abstrketa, 2);
      d0Res += 143.03*pow(abstrketa, 3);
      d0Res += -75.59*pow(abstrketa, 4);
      d0Res += 306.27*exp(-0.5*pow((abstrketa-2.13)/0.24,2));
    }
    if (abstrketa>=2.0 && abstrketa<2.8) {
      d0Res += 5482.32*pow(abstrketa, 0);
      d0Res += -7035.38*pow(abstrketa, 1);
      d0Res += 3022.93*pow(abstrketa, 2);
      d0Res += -425.41*pow(abstrketa, 3);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.0) {
      d0Res += 48.84*pow(abstrketa, 0);
      d0Res += -4.62*pow(abstrketa, 1);
      d0Res += 10.69*pow(abstrketa, 2);
      d0Res += 2.49*pow(abstrketa, 3);
      d0Res += -6.33*pow(abstrketa, 4);
      d0Res += 12.81*exp(-0.5*pow((abstrketa-1.16)/0.07,2));
      d0Res += 61.51*exp(-0.5*pow((abstrketa-2.09)/0.21,2));
    }
    if (abstrketa>=2.0 && abstrketa<2.8) {
      d0Res += 664.42*pow(abstrketa, 0);
      d0Res += -539.64*pow(abstrketa, 1);
      d0Res += 119.19*pow(abstrketa, 2);
      d0Res += 22.89*exp(-0.5*pow((abstrketa-2.42)/0.15,2));
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
