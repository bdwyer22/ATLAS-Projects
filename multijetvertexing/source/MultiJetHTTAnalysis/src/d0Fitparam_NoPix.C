double getD0ResParam_NoPix(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.4) {
      d0Res += 1075.28*pow(abstrketa, 0);
      d0Res += 442.12*pow(abstrketa, 1);
      d0Res += -610.41*pow(abstrketa, 2);
      d0Res += 508.02*pow(abstrketa, 3);
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.4) {
      d0Res += 764.98*pow(abstrketa, 0);
      d0Res += -1436.07*pow(abstrketa, 1);
      d0Res += 6894.88*pow(abstrketa, 2);
      d0Res += -13043.58*pow(abstrketa, 3);
      d0Res += 12110.94*pow(abstrketa, 4);
      d0Res += -5281.61*pow(abstrketa, 5);
      d0Res += 878.10*pow(abstrketa, 6);
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.2) {
      d0Res += 390.83*pow(abstrketa, 0);
      d0Res += -77.46*pow(abstrketa, 1);
      d0Res += 215.89*pow(abstrketa, 2);
      d0Res += -20.27*pow(abstrketa, 3);
      d0Res += 461.68*exp(-0.5*pow((abstrketa-1.59)/0.03,2));
      d0Res += 783.31*exp(-0.5*pow((abstrketa-2.33)/0.25,2));
    }
    if (abstrketa>=2.2 && abstrketa<2.4) {
      d0Res += 3268.88*pow(abstrketa, 0);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.2) {
      d0Res += 242.16*pow(abstrketa, 0);
      d0Res += -374.96*pow(abstrketa, 1);
      d0Res += 1775.75*pow(abstrketa, 2);
      d0Res += -3453.65*pow(abstrketa, 3);
      d0Res += 3372.26*pow(abstrketa, 4);
      d0Res += -1561.95*pow(abstrketa, 5);
      d0Res += 280.10*pow(abstrketa, 6);
    }
    if (abstrketa>=2.2 && abstrketa<2.4) {
      d0Res += 2712.99*pow(abstrketa, 0);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.2) {
      d0Res += 150.22*pow(abstrketa, 0);
      d0Res += -44.78*pow(abstrketa, 1);
      d0Res += 72.22*pow(abstrketa, 2);
      d0Res += 60.13*exp(-0.5*pow((abstrketa-1.58)/0.05,2));
      d0Res += 928.92*exp(-0.5*pow((abstrketa-2.36)/0.28,2));
    }
    if (abstrketa>=2.2 && abstrketa<2.4) {
      d0Res += 2431.90*pow(abstrketa, 0);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.1) {
      d0Res += 91.99*pow(abstrketa, 0);
      d0Res += 45.96*pow(abstrketa, 1);
      d0Res += -433.76*pow(abstrketa, 2);
      d0Res += 1390.95*pow(abstrketa, 3);
      d0Res += -1950.35*pow(abstrketa, 4);
      d0Res += 1232.27*pow(abstrketa, 5);
      d0Res += -279.59*pow(abstrketa, 6);
      d0Res += 1000.00*exp(-0.5*pow((abstrketa-2.10)/0.15,2));
    }
    if (abstrketa>=2.1 && abstrketa<2.4) {
      d0Res += -20723.81*pow(abstrketa, 0);
      d0Res += 10104.16*pow(abstrketa, 1);
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
