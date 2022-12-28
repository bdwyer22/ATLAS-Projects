double getD0ResParam_MoU2in(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.8) {
      d0Res += 762.85*pow(abstrketa, 0);
      d0Res += 65.59*pow(abstrketa, 1);
      d0Res += 111.31*pow(abstrketa, 2);
      d0Res += 27.71*pow(abstrketa, 3);
      d0Res += 5.99*pow(abstrketa, 4);
      d0Res += -3.10*pow(abstrketa, 5);
      d0Res += -4.64*pow(abstrketa, 6);
      d0Res += 45.72*exp(-0.5*pow((abstrketa-1.02)/1.00,2));
      d0Res += 903.71*exp(-0.5*pow((abstrketa-2.80)/0.69,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.8) {
      d0Res += 497.82*pow(abstrketa, 0);
      d0Res += -142.95*pow(abstrketa, 1);
      d0Res += 663.85*pow(abstrketa, 2);
      d0Res += -657.91*pow(abstrketa, 3);
      d0Res += 355.34*pow(abstrketa, 4);
      d0Res += -69.99*pow(abstrketa, 5);
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.8) {
      d0Res += 259.25*pow(abstrketa, 0);
      d0Res += 149.61*exp(-0.5*pow((abstrketa-1.57)/0.59,2));
      d0Res += 301.95*exp(-0.5*pow((abstrketa-2.35)/0.42,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.8) {
      d0Res += 143.95*pow(abstrketa, 0);
      d0Res += 59.85*exp(-0.5*pow((abstrketa-1.35)/0.46,2));
      d0Res += 218.81*exp(-0.5*pow((abstrketa-2.26)/0.42,2));
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.8) {
      d0Res += 88.27*pow(abstrketa, 0);
      d0Res += 31.43*exp(-0.5*pow((abstrketa-1.32)/0.39,2));
      d0Res += 164.70*exp(-0.5*pow((abstrketa-2.21)/0.38,2));
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.2) {
      d0Res += 48.98*pow(abstrketa, 0);
      d0Res += 12.54*exp(-0.5*pow((abstrketa-1.17)/0.07,2));
      d0Res += 160.36*exp(-0.5*pow((abstrketa-2.42)/0.50,2));
    }
    if (abstrketa>=2.2 && abstrketa<2.8) {
      d0Res += -44264.61*pow(abstrketa, 0);
      d0Res += 53693.84*pow(abstrketa, 1);
      d0Res += -21519.06*pow(abstrketa, 2);
      d0Res += 2857.85*pow(abstrketa, 3);
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
