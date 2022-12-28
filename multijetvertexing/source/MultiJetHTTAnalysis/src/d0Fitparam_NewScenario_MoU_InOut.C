double getD0ResParam_NewScenario_MoU_InOut(float abstrketa, float trkpt, bool debug=0) {

  double d0Res = 0;
  if (trkpt>=1.0 && trkpt<1.5) {
    if (abstrketa<2.0) {
      d0Res += 1952.44*pow(abstrketa, 0);
      d0Res += -9058.30*pow(abstrketa, 1);
      d0Res += 43248.46*pow(abstrketa, 2);
      d0Res += -80833.89*pow(abstrketa, 3);
      d0Res += 68483.65*pow(abstrketa, 4);
      d0Res += -27026.19*pow(abstrketa, 5);
      d0Res += 4051.05*pow(abstrketa, 6);
    }
    if (abstrketa>=2.0 && abstrketa<4.0) {
      d0Res += 2788.85*pow(abstrketa, 0);
      d0Res += -2324.42*pow(abstrketa, 1);
      d0Res += 653.17*pow(abstrketa, 2);
      d0Res += -58.11*pow(abstrketa, 3);
      d0Res += 101.44*exp(-0.5*pow((abstrketa-2.41)/0.15,2));
    }
  }

  if (trkpt>=1.5 && trkpt<2.5) {
    if (abstrketa<2.0) {
      d0Res += 802.08*pow(abstrketa, 0);
      d0Res += -3642.17*pow(abstrketa, 1);
      d0Res += 17357.89*pow(abstrketa, 2);
      d0Res += -32323.31*pow(abstrketa, 3);
      d0Res += 27303.48*pow(abstrketa, 4);
      d0Res += -10743.23*pow(abstrketa, 5);
      d0Res += 1605.25*pow(abstrketa, 6);
    }
    if (abstrketa>=2.0 && abstrketa<4.0) {
      d0Res += 1213.58*pow(abstrketa, 0);
      d0Res += -953.30*pow(abstrketa, 1);
      d0Res += 254.94*pow(abstrketa, 2);
      d0Res += -20.69*pow(abstrketa, 3);
      d0Res += 55.13*exp(-0.5*pow((abstrketa-2.41)/0.15,2));
    }
  }

  if (trkpt>=2.5 && trkpt<5.0) {
    if (abstrketa<2.1) {
      d0Res += 246.28*pow(abstrketa, 0);
      d0Res += -1025.32*pow(abstrketa, 1);
      d0Res += 4852.25*pow(abstrketa, 2);
      d0Res += -8934.83*pow(abstrketa, 3);
      d0Res += 7462.19*pow(abstrketa, 4);
      d0Res += -2899.15*pow(abstrketa, 5);
      d0Res += 427.02*pow(abstrketa, 6);
    }
    if (abstrketa>=2.1 && abstrketa<4.0) {
      d0Res += -3534.32*pow(abstrketa, 0);
      d0Res += 5064.39*pow(abstrketa, 1);
      d0Res += -2608.78*pow(abstrketa, 2);
      d0Res += 582.71*pow(abstrketa, 3);
      d0Res += -47.57*pow(abstrketa, 4);
      d0Res += 18.39*exp(-0.5*pow((abstrketa-2.37)/0.15,2));
    }
  }

  if (trkpt>=5.0 && trkpt<10.0) {
    if (abstrketa<2.1) {
      d0Res += 68.04*pow(abstrketa, 0);
      d0Res += -249.83*pow(abstrketa, 1);
      d0Res += 1176.04*pow(abstrketa, 2);
      d0Res += -2148.25*pow(abstrketa, 3);
      d0Res += 1793.64*pow(abstrketa, 4);
      d0Res += -697.91*pow(abstrketa, 5);
      d0Res += 102.96*pow(abstrketa, 6);
    }
    if (abstrketa>=2.1 && abstrketa<4.0) {
      d0Res += -3404.50*pow(abstrketa, 0);
      d0Res += 4750.00*pow(abstrketa, 1);
      d0Res += -2407.49*pow(abstrketa, 2);
      d0Res += 531.39*pow(abstrketa, 3);
      d0Res += -43.01*pow(abstrketa, 4);
    }
  }

  if (trkpt>=10.0 && trkpt<20.0) {
    if (abstrketa<2.7) {
      d0Res += 18.92*pow(abstrketa, 0);
      d0Res += 8.52*pow(abstrketa, 1);
      d0Res += -8.69*pow(abstrketa, 2);
      d0Res += 20.03*exp(-0.5*pow((abstrketa-1.99)/0.41,2));
      d0Res += 39.76*exp(-0.5*pow((abstrketa-2.58)/0.26,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -12481.24*pow(abstrketa, 0);
      d0Res += 15884.45*pow(abstrketa, 1);
      d0Res += -7505.40*pow(abstrketa, 2);
      d0Res += 1563.00*pow(abstrketa, 3);
      d0Res += -120.87*pow(abstrketa, 4);
    }
  }

  if (trkpt>=20.0 && trkpt<100.0) {
    if (abstrketa<2.7) {
      d0Res += 9.16*pow(abstrketa, 0);
      d0Res += -3.48*pow(abstrketa, 1);
      d0Res += 10.79*pow(abstrketa, 2);
      d0Res += -11.76*pow(abstrketa, 3);
      d0Res += 2.88*pow(abstrketa, 4);
      d0Res += 2.60*pow(abstrketa, 5);
      d0Res += -1.05*pow(abstrketa, 6);
      d0Res += 40.07*exp(-0.5*pow((abstrketa-2.69)/0.23,2));
    }
    if (abstrketa>=2.7 && abstrketa<4.0) {
      d0Res += -1979.47*pow(abstrketa, 0);
      d0Res += 1034.00*pow(abstrketa, 1);
      d0Res += -131.30*pow(abstrketa, 2);
      d0Res += 227.99*exp(-0.5*pow((abstrketa-2.33)/0.48,2));
    }
  }

  if (debug) printf("d0Res = %f\n", d0Res);
  return d0Res;
}
