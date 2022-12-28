double getD0ResParam_L0_L1_InIn(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<4.0) {
      d0Res += 148.72*pow(abstrketa, 0);
      d0Res += 36.58*pow(abstrketa, 1);
      d0Res += -132.01*pow(abstrketa, 2);
      d0Res += 56.55*pow(abstrketa, 3);
      d0Res += -6.12*pow(abstrketa, 4);
      d0Res += 167.58*exp(-0.5*pow((abstrketa-1.76)/0.61,2));
      d0Res += 110.98*exp(-0.5*pow((abstrketa-2.39)/0.18,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<4.0) {
      d0Res += 86.44*pow(abstrketa, 0);
      d0Res += 34.28*pow(abstrketa, 1);
      d0Res += -138.98*pow(abstrketa, 2);
      d0Res += 244.85*pow(abstrketa, 3);
      d0Res += -156.46*pow(abstrketa, 4);
      d0Res += 41.04*pow(abstrketa, 5);
      d0Res += -3.79*pow(abstrketa, 6);
      d0Res += 62.61*exp(-0.5*pow((abstrketa-2.40)/0.15,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<4.0) {
      d0Res += 44.77*pow(abstrketa, 0);
      d0Res += 9.55*pow(abstrketa, 1);
      d0Res += -34.59*pow(abstrketa, 2);
      d0Res += 75.01*pow(abstrketa, 3);
      d0Res += -50.62*pow(abstrketa, 4);
      d0Res += 13.55*pow(abstrketa, 5);
      d0Res += -1.26*pow(abstrketa, 6);
      d0Res += 30.85*exp(-0.5*pow((abstrketa-2.40)/0.15,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<4.0) {
      d0Res += 24.27*pow(abstrketa, 0);
      d0Res += -2.61*pow(abstrketa, 1);
      d0Res += 13.47*pow(abstrketa, 2);
      d0Res += -6.39*pow(abstrketa, 3);
      d0Res += 1.03*pow(abstrketa, 4);
      d0Res += 11.14*exp(-0.5*pow((abstrketa-2.38)/0.15,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<4.0) {
      d0Res += 15.32*pow(abstrketa, 0);
      d0Res += -2.61*pow(abstrketa, 1);
      d0Res += 6.97*pow(abstrketa, 2);
      d0Res += -2.76*pow(abstrketa, 3);
      d0Res += 0.51*pow(abstrketa, 4);
      d0Res += 6.15*exp(-0.5*pow((abstrketa-2.90)/0.15,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<4.0) {
      d0Res += 8.75*pow(abstrketa, 0);
      d0Res += 1.59*pow(abstrketa, 1);
      d0Res += -2.44*pow(abstrketa, 2);
      d0Res += 1.36*pow(abstrketa, 3);
      d0Res += 10.11*exp(-0.5*pow((abstrketa-2.93)/0.15,2));
    }
  }

  if (trkpt>=100.0 && trkpt<150.0) {
    if (abstrketa<4.0) {
      d0Res += 7.42*pow(abstrketa, 0);
      d0Res += 1.26*pow(abstrketa, 1);
      d0Res += -2.87*pow(abstrketa, 2);
      d0Res += 1.49*pow(abstrketa, 3);
      d0Res += 11.49*exp(-0.5*pow((abstrketa-2.94)/0.15,2));
    }
  }

  if (trkpt>=150.0 && trkpt<200.0) {
    if (abstrketa<4.0) {
      d0Res += 7.16*pow(abstrketa, 0);
      d0Res += 1.20*pow(abstrketa, 1);
      d0Res += -2.96*pow(abstrketa, 2);
      d0Res += 1.52*pow(abstrketa, 3);
      d0Res += 11.76*exp(-0.5*pow((abstrketa-2.94)/0.15,2));
    }
  }

  if (trkpt>=200.0 && trkpt<300.0) {
    if (abstrketa<4.0) {
      d0Res += 6.98*pow(abstrketa, 0);
      d0Res += 1.16*pow(abstrketa, 1);
      d0Res += -3.02*pow(abstrketa, 2);
      d0Res += 1.54*pow(abstrketa, 3);
      d0Res += 11.95*exp(-0.5*pow((abstrketa-2.94)/0.15,2));
    }
  }

  if (trkpt>=300.0 && trkpt<500.0) {
    if (abstrketa<4.0) {
      d0Res += 6.81*pow(abstrketa, 0);
      d0Res += 1.12*pow(abstrketa, 1);
      d0Res += -3.08*pow(abstrketa, 2);
      d0Res += 1.56*pow(abstrketa, 3);
      d0Res += 12.13*exp(-0.5*pow((abstrketa-2.94)/0.15,2));
    }
  }

  if (trkpt>=500.0 && trkpt<750.0) {
    if (abstrketa<4.0) {
      d0Res += 6.71*pow(abstrketa, 0);
      d0Res += 1.10*pow(abstrketa, 1);
      d0Res += -3.12*pow(abstrketa, 2);
      d0Res += 1.57*pow(abstrketa, 3);
      d0Res += 12.23*exp(-0.5*pow((abstrketa-2.95)/0.15,2));
    }
  }

  if (trkpt>=750.0 && trkpt<1000.0) {
    if (abstrketa<4.0) {
      d0Res += 6.66*pow(abstrketa, 0);
      d0Res += 1.09*pow(abstrketa, 1);
      d0Res += -3.13*pow(abstrketa, 2);
      d0Res += 1.57*pow(abstrketa, 3);
      d0Res += 12.29*exp(-0.5*pow((abstrketa-2.95)/0.15,2));
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
