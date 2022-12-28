double getD0ResParam_N(float abstrketa, float trkpt, bool debug=0) {

  double d0Res_1 = 0;
  if (abstrketa<2.62) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_1 += 62.2856937838*pow(abstrketa, 0);
d0Res_1 += 14.9097754088*pow(abstrketa, 1);
d0Res_1 += -51.445287964*pow(abstrketa, 2);
d0Res_1 += 117.065274473*pow(abstrketa, 3);
d0Res_1 += -97.8837027292*pow(abstrketa, 4);
d0Res_1 += 39.242929606*pow(abstrketa, 5);
d0Res_1 += -6.01707402757*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.62) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_1 += 41.5935175929*pow(abstrketa, 0);
d0Res_1 += 10.5138774781*pow(abstrketa, 1);
d0Res_1 += -38.3194670441*pow(abstrketa, 2);
d0Res_1 += 83.8848683371*pow(abstrketa, 3);
d0Res_1 += -69.2374637613*pow(abstrketa, 4);
d0Res_1 += 27.325255357*pow(abstrketa, 5);
d0Res_1 += -4.12463627442*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.62) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_1 += 25.2126600661*pow(abstrketa, 0);
d0Res_1 += 7.07787158427*pow(abstrketa, 1);
d0Res_1 += -28.1284150286*pow(abstrketa, 2);
d0Res_1 += 57.9554714055*pow(abstrketa, 3);
d0Res_1 += -46.8203054616*pow(abstrketa, 4);
d0Res_1 += 17.9839034215*pow(abstrketa, 5);
d0Res_1 += -2.63902241159*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.62) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_1 += 15.4167708039*pow(abstrketa, 0);
d0Res_1 += 5.08691765296*pow(abstrketa, 1);
d0Res_1 += -22.3256495141*pow(abstrketa, 2);
d0Res_1 += 42.940053467*pow(abstrketa, 3);
d0Res_1 += -33.7917525572*pow(abstrketa, 4);
d0Res_1 += 12.5321453558*pow(abstrketa, 5);
d0Res_1 += -1.76860574959*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.62) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_1 += 10.5042422806*pow(abstrketa, 0);
d0Res_1 += 4.14401088981*pow(abstrketa, 1);
d0Res_1 += -19.6663049667*pow(abstrketa, 2);
d0Res_1 += 35.8301439041*pow(abstrketa, 3);
d0Res_1 += -27.58065488*pow(abstrketa, 4);
d0Res_1 += 9.9131650791*pow(abstrketa, 5);
d0Res_1 += -1.34750272131*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.62) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_1 += 7.25957238605*pow(abstrketa, 0);
d0Res_1 += -0.95475707947*pow(abstrketa, 1);
d0Res_1 += 0.953799856638*pow(abstrketa, 2);
    }
  }

  double d0Res_2 = 0;
  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_2 += 10906.8560605*pow(abstrketa, 0);
d0Res_2 += -9952.34065698*pow(abstrketa, 1);
d0Res_2 += 2093.04226708*pow(abstrketa, 2);
d0Res_2 += 551.746631413*pow(abstrketa, 3);
d0Res_2 += -258.570792907*pow(abstrketa, 4);
d0Res_2 += 25.8839295786*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_2 += 6720.37298933*pow(abstrketa, 0);
d0Res_2 += -6126.13092907*pow(abstrketa, 1);
d0Res_2 += 1288.41460903*pow(abstrketa, 2);
d0Res_2 += 340.255161852*pow(abstrketa, 3);
d0Res_2 += -159.70742725*pow(abstrketa, 4);
d0Res_2 += 16.0378241492*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_2 += 3423.92281546*pow(abstrketa, 0);
d0Res_2 += -3112.73843419*pow(abstrketa, 1);
d0Res_2 += 654.51556522*pow(abstrketa, 2);
d0Res_2 += 173.638082597*pow(abstrketa, 3);
d0Res_2 += -81.7953956315*pow(abstrketa, 4);
d0Res_2 += 8.27628085373*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_2 += 1487.43421976*pow(abstrketa, 0);
d0Res_2 += -1341.85001349*pow(abstrketa, 1);
d0Res_2 += 281.800573919*pow(abstrketa, 2);
d0Res_2 += 75.5974520151*pow(abstrketa, 3);
d0Res_2 += -35.9288730288*pow(abstrketa, 4);
d0Res_2 += 3.70457767238*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_2 += -100.768182531*pow(abstrketa, 0);
d0Res_2 += 157.118213161*pow(abstrketa, 1);
d0Res_2 += -66.1709987453*pow(abstrketa, 2);
d0Res_2 += 9.02349363345*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.6 && abstrketa<4.0) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_2 += -199.079209444*pow(abstrketa, 0);
d0Res_2 += 244.826009584*pow(abstrketa, 1);
d0Res_2 += -93.600459222*pow(abstrketa, 2);
d0Res_2 += 11.7780245361*pow(abstrketa, 3);
    }
  }

  double d0Res_3 = 0;






  double d0Res_4 = 0;






  if (debug) {
    printf("d0Res_1 = %f\n", d0Res_1);
    printf("d0Res_2 = %f\n", d0Res_2);
    printf("d0Res_3 = %f\n", d0Res_3);
    printf("d0Res_4 = %f\n", d0Res_4);
  }

  double d0Res = -1.;
  if (abstrketa<0) {{ d0Res = -1.; }}
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=1.0 && trkpt<1.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=1.5 && trkpt<2.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=2.5 && trkpt<5.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=5.0 && trkpt<10.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=10.0 && trkpt<20.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.62 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.6 && abstrketa<4.0 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.6 && abstrketa<2.62 && trkpt>=20.0 && trkpt<100.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }

  return d0Res;
}
