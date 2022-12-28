double getD0ResParam_NewScenario_MoU_OutOut(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.2) {
      d0Res += 1857.43*pow(abstrketa, 0);
      d0Res += -6825.76*pow(abstrketa, 1);
      d0Res += 31599.19*pow(abstrketa, 2);
      d0Res += -58505.05*pow(abstrketa, 3);
      d0Res += 49378.16*pow(abstrketa, 4);
      d0Res += -19464.68*pow(abstrketa, 5);
      d0Res += 2919.41*pow(abstrketa, 6);
    }
    if (abstrketa>=2.2 && abstrketa<4.0) {
      d0Res += 823.42*pow(abstrketa, 0);
      d0Res += 146658.86*pow(abstrketa, 1);
      d0Res += -249509.85*pow(abstrketa, 2);
      d0Res += 168536.94*pow(abstrketa, 3);
      d0Res += -56433.56*pow(abstrketa, 4);
      d0Res += 9355.18*pow(abstrketa, 5);
      d0Res += -613.82*pow(abstrketa, 6);
      d0Res += 1000.00*exp(-0.5*pow((abstrketa-2.35)/0.15,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.1) {
      d0Res += 785.79*pow(abstrketa, 0);
      d0Res += -2811.92*pow(abstrketa, 1);
      d0Res += 13234.92*pow(abstrketa, 2);
      d0Res += -24914.73*pow(abstrketa, 3);
      d0Res += 21568.39*pow(abstrketa, 4);
      d0Res += -8756.09*pow(abstrketa, 5);
      d0Res += 1354.38*pow(abstrketa, 6);
    }
    if (abstrketa>=2.1 && abstrketa<4.0) {
      d0Res += -84991.40*pow(abstrketa, 0);
      d0Res += 110532.55*pow(abstrketa, 1);
      d0Res += -52724.60*pow(abstrketa, 2);
      d0Res += 10989.55*pow(abstrketa, 3);
      d0Res += -846.33*pow(abstrketa, 4);
      d0Res += 875.55*exp(-0.5*pow((abstrketa-2.32)/0.15,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.7) {
      d0Res += 246.87*pow(abstrketa, 0);
      d0Res += -572.56*pow(abstrketa, 1);
      d0Res += 2503.74*pow(abstrketa, 2);
      d0Res += -4221.57*pow(abstrketa, 3);
      d0Res += 3203.66*pow(abstrketa, 4);
      d0Res += -1118.69*pow(abstrketa, 5);
      d0Res += 146.15*pow(abstrketa, 6);
      d0Res += 38.99*exp(-0.5*pow((abstrketa-1.40)/0.15,2));
      d0Res += 621.39*exp(-0.5*pow((abstrketa-2.38)/0.15,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -161907.79*pow(abstrketa, 0);
      d0Res += 200429.38*pow(abstrketa, 1);
      d0Res += -92182.91*pow(abstrketa, 2);
      d0Res += 18688.97*pow(abstrketa, 3);
      d0Res += -1409.65*pow(abstrketa, 4);
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.9) {
      d0Res += 70.11*pow(abstrketa, 0);
      d0Res += 15.74*pow(abstrketa, 1);
      d0Res += -62.71*pow(abstrketa, 2);
      d0Res += 117.57*pow(abstrketa, 3);
      d0Res += -69.35*pow(abstrketa, 4);
      d0Res += 12.52*pow(abstrketa, 5);
      d0Res += 327.77*exp(-0.5*pow((abstrketa-2.38)/0.15,2));
    }
    if (abstrketa>=2.9 && abstrketa<4.0) {
      d0Res += 26533.48*pow(abstrketa, 0);
      d0Res += -22825.34*pow(abstrketa, 1);
      d0Res += 6518.12*pow(abstrketa, 2);
      d0Res += -615.99*pow(abstrketa, 3);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.9) {
      d0Res += 29.77*pow(abstrketa, 0);
      d0Res += 2.37*pow(abstrketa, 1);
      d0Res += -39.23*pow(abstrketa, 2);
      d0Res += 14.75*pow(abstrketa, 3);
      d0Res += 61.15*exp(-0.5*pow((abstrketa-1.61)/0.57,2));
      d0Res += 220.05*exp(-0.5*pow((abstrketa-2.37)/0.15,2));
    }
    if (abstrketa>=2.9 && abstrketa<4.0) {
      d0Res += 22904.39*pow(abstrketa, 0);
      d0Res += -19878.98*pow(abstrketa, 1);
      d0Res += 5719.68*pow(abstrketa, 2);
      d0Res += -544.08*pow(abstrketa, 3);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.7) {
      d0Res += 17.69*pow(abstrketa, 0);
      d0Res += -20.42*pow(abstrketa, 1);
      d0Res += 90.25*pow(abstrketa, 2);
      d0Res += -184.95*pow(abstrketa, 3);
      d0Res += 190.85*pow(abstrketa, 4);
      d0Res += -87.31*pow(abstrketa, 5);
      d0Res += 14.04*pow(abstrketa, 6);
      d0Res += 171.36*exp(-0.5*pow((abstrketa-2.36)/0.15,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -4640.55*pow(abstrketa, 0);
      d0Res += 1005.03*pow(abstrketa, 1);
      d0Res += 437.08*pow(abstrketa, 2);
      d0Res += -98.53*pow(abstrketa, 3);
      d0Res += 823.24*exp(-0.5*pow((abstrketa-2.45)/0.44,2));
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
