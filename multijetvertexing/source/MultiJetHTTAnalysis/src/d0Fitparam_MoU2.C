double getD0ResParam_MoU2(float abstrketa, float trkpt, bool debug=0) {

  double d0Res_1 = 0;
  if (abstrketa<2.52) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_1 += 914.98469459*pow(abstrketa, 0);
d0Res_1 += -70.6237434571*pow(abstrketa, 1);
d0Res_1 += 919.071830929*pow(abstrketa, 2);
d0Res_1 += -1212.86170306*pow(abstrketa, 3);
d0Res_1 += 707.647063328*pow(abstrketa, 4);
d0Res_1 += -134.883651997*pow(abstrketa, 5);
    }
  }

  if (abstrketa<2.52) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_1 += 590.546270763*pow(abstrketa, 0);
d0Res_1 += -73.8090558349*pow(abstrketa, 1);
d0Res_1 += 672.258126655*pow(abstrketa, 2);
d0Res_1 += -876.22553692*pow(abstrketa, 3);
d0Res_1 += 503.869299783*pow(abstrketa, 4);
d0Res_1 += -94.9723308848*pow(abstrketa, 5);
    }
  }

  if (abstrketa<2.52) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_1 += 333.566862852*pow(abstrketa, 0);
d0Res_1 += -73.7874349576*pow(abstrketa, 1);
d0Res_1 += 468.573482471*pow(abstrketa, 2);
d0Res_1 += -599.680177206*pow(abstrketa, 3);
d0Res_1 += 337.531305467*pow(abstrketa, 4);
d0Res_1 += -62.5031097538*pow(abstrketa, 5);
    }
  }

  if (abstrketa<2.52) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_1 += 179.644310122*pow(abstrketa, 0);
d0Res_1 += -69.5512430202*pow(abstrketa, 1);
d0Res_1 += 332.935614253*pow(abstrketa, 2);
d0Res_1 += -417.490173511*pow(abstrketa, 3);
d0Res_1 += 229.634314417*pow(abstrketa, 4);
d0Res_1 += -41.6149138092*pow(abstrketa, 5);
    }
  }

  if (abstrketa<2.52) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_1 += 102.153101875*pow(abstrketa, 0);
d0Res_1 += -62.4903892352*pow(abstrketa, 1);
d0Res_1 += 248.685968396*pow(abstrketa, 2);
d0Res_1 += -306.345620529*pow(abstrketa, 3);
d0Res_1 += 165.58866907*pow(abstrketa, 4);
d0Res_1 += -29.4005845684*pow(abstrketa, 5);
    }
  }

  if (abstrketa<1.12) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_1 += 43.4719885088*pow(abstrketa, 0);
d0Res_1 += -6.54060289453*pow(abstrketa, 1);
d0Res_1 += 16.3082506148*pow(abstrketa, 2);
d0Res_1 += -3.8494901527*pow(abstrketa, 3);
    }
  }

  double d0Res_2 = 0;
  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=1.0 && trkpt<1.5) {
d0Res_2 += 3320.89192484*pow(abstrketa, 0);
d0Res_2 += 191.561303755*pow(abstrketa, 1);
d0Res_2 += -345.310370772*pow(abstrketa, 2);
    }
  }

  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=1.5 && trkpt<2.5) {
d0Res_2 += 2186.95464956*pow(abstrketa, 0);
d0Res_2 += 124.626647156*pow(abstrketa, 1);
d0Res_2 += -228.448115826*pow(abstrketa, 2);
    }
  }

  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=2.5 && trkpt<5.0) {
d0Res_2 += 1289.45013872*pow(abstrketa, 0);
d0Res_2 += 71.6473813272*pow(abstrketa, 1);
d0Res_2 += -135.954482486*pow(abstrketa, 2);
    }
  }

  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=5.0 && trkpt<10.0) {
d0Res_2 += 5267.08920481*pow(abstrketa, 0);
d0Res_2 += -3408.83771452*pow(abstrketa, 1);
d0Res_2 += 577.721877028*pow(abstrketa, 2);
    }
  }

  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=10.0 && trkpt<20.0) {
d0Res_2 += 5647.10106879*pow(abstrketa, 0);
d0Res_2 += -3920.47467331*pow(abstrketa, 1);
d0Res_2 += 700.075584444*pow(abstrketa, 2);
    }
  }

  if (abstrketa>=1.1 && abstrketa<2.52) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_2 += -890.839324311*pow(abstrketa, 0);
d0Res_2 += 1905.85762509*pow(abstrketa, 1);
d0Res_2 += -982.677902637*pow(abstrketa, 2);
d0Res_2 += -271.908381613*pow(abstrketa, 3);
d0Res_2 += 350.090886344*pow(abstrketa, 4);
d0Res_2 += -71.5067400249*pow(abstrketa, 5);
    }
  }

  double d0Res_3 = 0;





  if (abstrketa>=2.5 && abstrketa<2.8) {
    if (trkpt>=20.0 && trkpt<100.0) {
d0Res_3 += 5917.01066169*pow(abstrketa, 0);
d0Res_3 += -4283.86058316*pow(abstrketa, 1);
d0Res_3 += 786.975492437*pow(abstrketa, 2);
    }
  }

  double d0Res_4 = 0;






  if (debug) {
    printf("d0Res_1 = %f\n", d0Res_1);
    printf("d0Res_2 = %f\n", d0Res_2);
    printf("d0Res_3 = %f\n", d0Res_3);
    printf("d0Res_4 = %f\n", d0Res_4);
  }

  double d0Res = -1.;
  if (abstrketa<0) {{ d0Res = -1.; }}
  if (abstrketa>=0 && abstrketa<2.52 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_1; }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=1.0 && trkpt<1.5) { d0Res = d0Res_2; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=1.0 && trkpt<1.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.52 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_1; }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=1.5 && trkpt<2.5) { d0Res = d0Res_2; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=1.5 && trkpt<2.5) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.52 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=2.5 && trkpt<5.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=2.5 && trkpt<5.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.52 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=5.0 && trkpt<10.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=5.0 && trkpt<10.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<2.52 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_1; }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=10.0 && trkpt<20.0) { d0Res = d0Res_2; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=10.0 && trkpt<20.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.12 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_1; }
  if (abstrketa>=1.1 && abstrketa<2.52 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_2; }
  if (abstrketa>=1.1 && abstrketa<1.12 && trkpt>=20.0 && trkpt<100.0) {
    d0Res = (d0Res_1+d0Res_2)/2. ;
  }
  if (abstrketa>=2.5 && abstrketa<2.8 && trkpt>=20.0 && trkpt<100.0) { d0Res = d0Res_3; }
  if (abstrketa>=2.5 && abstrketa<2.52 && trkpt>=20.0 && trkpt<100.0) {
    d0Res = (d0Res_2+d0Res_3)/2. ;
  }

  return d0Res;
}
