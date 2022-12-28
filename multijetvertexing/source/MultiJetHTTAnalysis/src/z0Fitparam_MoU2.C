double getZ0ResParam_MoU2(float abstrketa, float trkpt, bool debug=0) {

  double z0Res_1 = 0;
  if (abstrketa<1.22) {
    if (trkpt>=1.0 && trkpt<1.5) {
z0Res_1 += 888.674972355*pow(abstrketa, 0);
z0Res_1 += 40.9823454718*pow(abstrketa, 1);
z0Res_1 += -726.045619191*pow(abstrketa, 2);
z0Res_1 += 2878.20730579*pow(abstrketa, 3);
z0Res_1 += -1525.25317159*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.22) {
    if (trkpt>=1.5 && trkpt<2.5) {
z0Res_1 += 620.476874699*pow(abstrketa, 0);
z0Res_1 += -0.998716542376*pow(abstrketa, 1);
z0Res_1 += -335.187599861*pow(abstrketa, 2);
z0Res_1 += 1613.59624366*pow(abstrketa, 3);
z0Res_1 += -860.10437982*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.22) {
    if (trkpt>=2.5 && trkpt<5.0) {
z0Res_1 += 408.328519427*pow(abstrketa, 0);
z0Res_1 += -36.5722538136*pow(abstrketa, 1);
z0Res_1 += -16.6471752044*pow(abstrketa, 2);
z0Res_1 += 600.232841181*pow(abstrketa, 3);
z0Res_1 += -328.276948194*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.24) {
    if (trkpt>=5.0 && trkpt<10.0) {
z0Res_1 += 281.710820084*pow(abstrketa, 0);
z0Res_1 += -61.3872625905*pow(abstrketa, 1);
z0Res_1 += 187.630499319*pow(abstrketa, 2);
z0Res_1 += -24.2672648083*pow(abstrketa, 3);
z0Res_1 += -2.28563409019*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.24) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_1 += 218.462835539*pow(abstrketa, 0);
z0Res_1 += -77.4350352206*pow(abstrketa, 1);
z0Res_1 += 304.073463322*pow(abstrketa, 2);
z0Res_1 += -356.193098803*pow(abstrketa, 3);
z0Res_1 += 169.237384149*pow(abstrketa, 4);
    }
  }

  if (abstrketa<1.24) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_1 += 173.794805572*pow(abstrketa, 0);
z0Res_1 += -93.1461237898*pow(abstrketa, 1);
z0Res_1 += 403.510838366*pow(abstrketa, 2);
z0Res_1 += -614.388293226*pow(abstrketa, 3);
z0Res_1 += 300.679415476*pow(abstrketa, 4);
    }
  }

  double z0Res_2 = 0;
  if (abstrketa>=1.18 && abstrketa<2.24) {
    if (trkpt>=1.0 && trkpt<1.5) {
z0Res_2 += -72648.7393317*pow(abstrketa, 0);
z0Res_2 += 144082.608086*pow(abstrketa, 1);
z0Res_2 += -65584.5565027*pow(abstrketa, 2);
z0Res_2 += -31081.3608925*pow(abstrketa, 3);
z0Res_2 += 31915.7848626*pow(abstrketa, 4);
z0Res_2 += -6550.90356338*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=1.18 && abstrketa<2.24) {
    if (trkpt>=1.5 && trkpt<2.5) {
z0Res_2 += -45716.9543756*pow(abstrketa, 0);
z0Res_2 += 90028.4490062*pow(abstrketa, 1);
z0Res_2 += -40383.8331522*pow(abstrketa, 2);
z0Res_2 += -19660.5070305*pow(abstrketa, 3);
z0Res_2 += 19863.1889566*pow(abstrketa, 4);
z0Res_2 += -4047.33294701*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=1.18 && abstrketa<2.24) {
    if (trkpt>=2.5 && trkpt<5.0) {
z0Res_2 += -24300.1382091*pow(abstrketa, 0);
z0Res_2 += 47071.9182429*pow(abstrketa, 1);
z0Res_2 += -20397.6610842*pow(abstrketa, 2);
z0Res_2 += -10538.8445646*pow(abstrketa, 3);
z0Res_2 += 10266.3189255*pow(abstrketa, 4);
z0Res_2 += -2054.98210164*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=1.22 && abstrketa<2.24) {
    if (trkpt>=5.0 && trkpt<10.0) {
z0Res_2 += -11338.6111516*pow(abstrketa, 0);
z0Res_2 += 21118.0102445*pow(abstrketa, 1);
z0Res_2 += -8382.8662434*pow(abstrketa, 2);
z0Res_2 += -4960.31920658*pow(abstrketa, 3);
z0Res_2 += 4440.64399961*pow(abstrketa, 4);
z0Res_2 += -847.2210339*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=1.22 && abstrketa<2.24) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_2 += -4708.70585111*pow(abstrketa, 0);
z0Res_2 += 7883.56319336*pow(abstrketa, 1);
z0Res_2 += -2316.85644014*pow(abstrketa, 2);
z0Res_2 += -2047.04770245*pow(abstrketa, 3);
z0Res_2 += 1441.35778073*pow(abstrketa, 4);
z0Res_2 += -227.058860983*pow(abstrketa, 5);
    }
  }

  if (abstrketa>=1.22 && abstrketa<2.24) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_2 += 185033.758364*pow(abstrketa, 0);
z0Res_2 += -575132.95423*pow(abstrketa, 1);
z0Res_2 += 706702.108515*pow(abstrketa, 2);
z0Res_2 += -428843.816657*pow(abstrketa, 3);
z0Res_2 += 128604.54946*pow(abstrketa, 4);
z0Res_2 += -15236.0963083*pow(abstrketa, 5);
    }
  }

  double z0Res_3 = 0;
  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=1.0 && trkpt<1.5) {
z0Res_3 += 38672.6057253*pow(abstrketa, 0);
z0Res_3 += -14027.8882664*pow(abstrketa, 1);
z0Res_3 += -5782.75974554*pow(abstrketa, 2);
z0Res_3 += 2438.63607688*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=1.5 && trkpt<2.5) {
z0Res_3 += 24224.8338254*pow(abstrketa, 0);
z0Res_3 += -8721.54800187*pow(abstrketa, 1);
z0Res_3 += -3601.86449465*pow(abstrketa, 2);
z0Res_3 += 1513.93672129*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=2.5 && trkpt<5.0) {
z0Res_3 += 12820.7540917*pow(abstrketa, 0);
z0Res_3 += -4533.30565856*pow(abstrketa, 1);
z0Res_3 += -1881.84365857*pow(abstrketa, 2);
z0Res_3 += 784.352415914*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=5.0 && trkpt<10.0) {
z0Res_3 += 6067.11049082*pow(abstrketa, 0);
z0Res_3 += -2053.89716548*pow(abstrketa, 1);
z0Res_3 += -865.705088402*pow(abstrketa, 2);
z0Res_3 += 352.822892749*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_3 += -25445.0558242*pow(abstrketa, 0);
z0Res_3 += 33604.7786226*pow(abstrketa, 1);
z0Res_3 += -14365.4285305*pow(abstrketa, 2);
z0Res_3 += 2033.57815506*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=2.22 && abstrketa<2.8) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_3 += -49026.944787*pow(abstrketa, 0);
z0Res_3 += 60429.5750531*pow(abstrketa, 1);
z0Res_3 += -24575.5084759*pow(abstrketa, 2);
z0Res_3 += 3313.17253238*pow(abstrketa, 3);
    }
  }

  double z0Res_4 = 0;






  if (debug) {
    printf("z0Res_1 = %f\n", z0Res_1);
    printf("z0Res_2 = %f\n", z0Res_2);
    printf("z0Res_3 = %f\n", z0Res_3);
    printf("z0Res_4 = %f\n", z0Res_4);
  }

  double z0Res = -1.;
  if (abstrketa<0) {{ z0Res = -1.; }}
  if (abstrketa>=0 && abstrketa<1.22 && trkpt>=1.0 && trkpt<1.5) { z0Res = z0Res_1; }
  if (abstrketa>=1.18 && abstrketa<2.24 && trkpt>=1.0 && trkpt<1.5) { z0Res = z0Res_2; }
  if (abstrketa>=1.18 && abstrketa<1.22 && trkpt>=1.0 && trkpt<1.5) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=1.0 && trkpt<1.5) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=1.0 && trkpt<1.5) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.22 && trkpt>=1.5 && trkpt<2.5) { z0Res = z0Res_1; }
  if (abstrketa>=1.18 && abstrketa<2.24 && trkpt>=1.5 && trkpt<2.5) { z0Res = z0Res_2; }
  if (abstrketa>=1.18 && abstrketa<1.22 && trkpt>=1.5 && trkpt<2.5) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=1.5 && trkpt<2.5) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=1.5 && trkpt<2.5) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.22 && trkpt>=2.5 && trkpt<5.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.18 && abstrketa<2.24 && trkpt>=2.5 && trkpt<5.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.18 && abstrketa<1.22 && trkpt>=2.5 && trkpt<5.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=2.5 && trkpt<5.0) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=2.5 && trkpt<5.0) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.24 && trkpt>=5.0 && trkpt<10.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.22 && abstrketa<2.24 && trkpt>=5.0 && trkpt<10.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.22 && abstrketa<1.24 && trkpt>=5.0 && trkpt<10.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=5.0 && trkpt<10.0) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=5.0 && trkpt<10.0) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.24 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.22 && abstrketa<2.24 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.22 && abstrketa<1.24 && trkpt>=10.0 && trkpt<20.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=10.0 && trkpt<20.0) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.24 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.22 && abstrketa<2.24 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.22 && abstrketa<1.24 && trkpt>=20.0 && trkpt<100.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=2.22 && abstrketa<2.8 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_3; }
  if (abstrketa>=2.22 && abstrketa<2.24 && trkpt>=20.0 && trkpt<100.0) {
    z0Res = (z0Res_2+z0Res_3)/2. ;
  }

  return z0Res;
}
