double getD0ResParam_PIX3L2in(float abstrketa, float trkpt, bool debug=0) {

  double d0Res_1 = 0;
  if (abstrketa<1.64) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_1 += 458.032388726*pow(abstrketa, 0);
d0Res_1 += -171.446473372*pow(abstrketa, 1);
d0Res_1 += 765.977643132*pow(abstrketa, 2);
d0Res_1 += -718.446181914*pow(abstrketa, 3);
d0Res_1 += 239.012337741*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.64) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_1 += 295.390725034*pow(abstrketa, 0);
d0Res_1 += -109.932458221*pow(abstrketa, 1);
d0Res_1 += 486.0819821*pow(abstrketa, 2);
d0Res_1 += -455.209478608*pow(abstrketa, 3);
d0Res_1 += 151.864670831*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.64) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_1 += 166.654381463*pow(abstrketa, 0);
d0Res_1 += -61.217727145*pow(abstrketa, 1);
d0Res_1 += 264.49864345*pow(abstrketa, 2);
d0Res_1 += -246.853989423*pow(abstrketa, 3);
d0Res_1 += 82.8968708432*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.64) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_1 += 89.6913754779*pow(abstrketa, 0);
d0Res_1 += -32.0580730017*pow(abstrketa, 1);
d0Res_1 += 131.976897537*pow(abstrketa, 2);
d0Res_1 += -122.307901086*pow(abstrketa, 3);
d0Res_1 += 41.688160806*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.64) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_1 += 50.2931763463*pow(abstrketa, 0);
d0Res_1 += -2.84419131335*pow(abstrketa, 1);
d0Res_1 += 1.57301912458*pow(abstrketa, 2);
d0Res_1 += 48.5591190856*pow(abstrketa, 3);
d0Res_1 += -56.8714522805*pow(abstrketa, 4);
d0Res_1 += 19.9172551307*pow(abstrketa, 5);
    }
  }

  if (abstrketa<2.8) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_1 += 24.0863782845*pow(abstrketa, 0);
d0Res_1 += -12.6787892267*pow(abstrketa, 1);
d0Res_1 += 39.8401045197*pow(abstrketa, 2);
d0Res_1 += -47.5109432524*pow(abstrketa, 3);
d0Res_1 += 26.8778828225*pow(abstrketa, 4);
d0Res_1 += -4.8339058667*pow(abstrketa, 5);
    }
  }

  double d0Res_2 = 0;
  if (abstrketa>=1.62 && abstrketa<2.8) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_2 += -48805.9628865*pow(abstrketa, 0);
d0Res_2 += 94460.7097249*pow(abstrketa, 1);
d0Res_2 += -66857.6503201*pow(abstrketa, 2);
d0Res_2 += 20749.3932605*pow(abstrketa, 3);
d0Res_2 += -2370.0378537*pow(abstrketa, 4);
    }
  }

  if (abstrketa>=1.62 && abstrketa<2.8) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_2 += -31106.3675209*pow(abstrketa, 0);
d0Res_2 += 60221.2415388*pow(abstrketa, 1);
d0Res_2 += -42647.5102403*pow(abstrketa, 2);
d0Res_2 += 13249.4520742*pow(abstrketa, 3);
d0Res_2 += -1515.41508791*pow(abstrketa, 4);
    }
  }

  if (abstrketa>=1.62 && abstrketa<2.8) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_2 += -17100.9469424*pow(abstrketa, 0);
d0Res_2 += 33128.308889*pow(abstrketa, 1);
d0Res_2 += -23490.8576807*pow(abstrketa, 2);
d0Res_2 += 7315.12154484*pow(abstrketa, 3);
d0Res_2 += -839.212418498*pow(abstrketa, 4);
    }
  }

  if (abstrketa>=1.62 && abstrketa<2.8) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_2 += -8730.36683057*pow(abstrketa, 0);
d0Res_2 += 16936.4437498*pow(abstrketa, 1);
d0Res_2 += -12042.6457909*pow(abstrketa, 2);
d0Res_2 += 3768.9227805*pow(abstrketa, 3);
d0Res_2 += -435.162030636*pow(abstrketa, 4);
    }
  }

  if (abstrketa>=1.62 && abstrketa<2.8) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_2 += -4543.64184068*pow(abstrketa, 0);
d0Res_2 += 8838.31792888*pow(abstrketa, 1);
d0Res_2 += -6317.66599399*pow(abstrketa, 2);
d0Res_2 += 1995.81142319*pow(abstrketa, 3);
d0Res_2 += -233.174350121*pow(abstrketa, 4);
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
  if (abstrketa>=0 && abstrketa<1.64 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_1; }
  if (abstrketa>=1.62 && abstrketa<2.8 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_2; }
  if (abstrketa>=1.62 && abstrketa<1.64 && trkpt>=1.0 && trkpt<1.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.64 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_1; }
  if (abstrketa>=1.62 && abstrketa<2.8 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_2; }
  if (abstrketa>=1.62 && abstrketa<1.64 && trkpt>=1.5 && trkpt<2.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.64 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_1; }
  if (abstrketa>=1.62 && abstrketa<2.8 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_2; }
  if (abstrketa>=1.62 && abstrketa<1.64 && trkpt>=2.5 && trkpt<5.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.64 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_1; }
  if (abstrketa>=1.62 && abstrketa<2.8 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_2; }
  if (abstrketa>=1.62 && abstrketa<1.64 && trkpt>=5.0 && trkpt<10.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.64 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_1; }
  if (abstrketa>=1.62 && abstrketa<2.8 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_2; }
  if (abstrketa>=1.62 && abstrketa<1.64 && trkpt>=10.0 && trkpt<20.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.8 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_1; }

  return d0Res;
}
