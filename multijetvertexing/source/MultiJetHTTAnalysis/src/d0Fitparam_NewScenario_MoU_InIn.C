double getD0ResParam_NewScenario_MoU_InIn(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<4.0) {
      d0Res += 130.53*pow(abstrketa, 0);
      d0Res += -21.14*pow(abstrketa, 1);
      d0Res += -214.15*pow(abstrketa, 2);
      d0Res += 111.08*pow(abstrketa, 3);
      d0Res += -13.70*pow(abstrketa, 4);
      d0Res += 319.39*exp(-0.5*pow((abstrketa-1.79)/0.78,2));
      d0Res += 104.03*exp(-0.5*pow((abstrketa-2.39)/0.16,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<4.0) {
      d0Res += 86.62*pow(abstrketa, 0);
      d0Res += 33.41*pow(abstrketa, 1);
      d0Res += -140.34*pow(abstrketa, 2);
      d0Res += 248.86*pow(abstrketa, 3);
      d0Res += -158.86*pow(abstrketa, 4);
      d0Res += 41.54*pow(abstrketa, 5);
      d0Res += -3.82*pow(abstrketa, 6);
      d0Res += 65.08*exp(-0.5*pow((abstrketa-2.40)/0.15,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<4.0) {
      d0Res += 44.34*pow(abstrketa, 0);
      d0Res += 15.88*pow(abstrketa, 1);
      d0Res += -56.43*pow(abstrketa, 2);
      d0Res += 102.73*pow(abstrketa, 3);
      d0Res += -65.81*pow(abstrketa, 4);
      d0Res += 17.19*pow(abstrketa, 5);
      d0Res += -1.57*pow(abstrketa, 6);
      d0Res += 35.40*exp(-0.5*pow((abstrketa-2.41)/0.15,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.7) {
      d0Res += 24.26*pow(abstrketa, 0);
      d0Res += -0.65*pow(abstrketa, 1);
      d0Res += 6.28*pow(abstrketa, 2);
      d0Res += -0.16*pow(abstrketa, 3);
      d0Res += -0.33*pow(abstrketa, 4);
      d0Res += -0.13*pow(abstrketa, 5);
      d0Res += -0.00*pow(abstrketa, 6);
      d0Res += 2.28*exp(-0.5*pow((abstrketa-1.39)/0.13,2));
      d0Res += 21.92*exp(-0.5*pow((abstrketa-2.44)/0.15,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -14360.06*pow(abstrketa, 0);
      d0Res += 18350.55*pow(abstrketa, 1);
      d0Res += -8703.29*pow(abstrketa, 2);
      d0Res += 1819.28*pow(abstrketa, 3);
      d0Res += -141.23*pow(abstrketa, 4);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.7) {
      d0Res += 14.97*pow(abstrketa, 0);
      d0Res += 0.44*pow(abstrketa, 1);
      d0Res += 0.89*pow(abstrketa, 2);
      d0Res += 0.64*pow(abstrketa, 3);
      d0Res += 1.06*pow(abstrketa, 4);
      d0Res += -0.60*pow(abstrketa, 5);
      d0Res += 20.71*exp(-0.5*pow((abstrketa-2.51)/0.19,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -13104.47*pow(abstrketa, 0);
      d0Res += 16669.65*pow(abstrketa, 1);
      d0Res += -7874.43*pow(abstrketa, 2);
      d0Res += 1639.65*pow(abstrketa, 3);
      d0Res += -126.80*pow(abstrketa, 4);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.7) {
      d0Res += 9.46*pow(abstrketa, 0);
      d0Res += -5.16*pow(abstrketa, 1);
      d0Res += 14.07*pow(abstrketa, 2);
      d0Res += -13.05*pow(abstrketa, 3);
      d0Res += 2.20*pow(abstrketa, 4);
      d0Res += 2.59*pow(abstrketa, 5);
      d0Res += -0.87*pow(abstrketa, 6);
      d0Res += 17.35*exp(-0.5*pow((abstrketa-2.59)/0.15,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -1886.72*pow(abstrketa, 0);
      d0Res += 986.58*pow(abstrketa, 1);
      d0Res += -125.23*pow(abstrketa, 2);
      d0Res += 213.53*exp(-0.5*pow((abstrketa-2.35)/0.47,2));
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
