double getZ0ResParam_PIX3L2in(float abstrketa, float trkpt, bool debug=0) {

  double z0Res_1 = 0;
  if (abstrketa<2.8) {
    if (trkpt>=1.0 && trkpt<1.5) {
z0Res_1 += 298.401326019*pow(abstrketa, 0);
z0Res_1 += 75.593358829*pow(abstrketa, 1);
z0Res_1 += 381.49232334*pow(abstrketa, 2);
z0Res_1 += -1108.01867246*pow(abstrketa, 3);
z0Res_1 += 1750.24695974*pow(abstrketa, 4);
z0Res_1 += -940.77420688*pow(abstrketa, 5);
z0Res_1 += 173.527943096*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.8) {
    if (trkpt>=1.5 && trkpt<2.5) {
z0Res_1 += 206.185500498*pow(abstrketa, 0);
z0Res_1 += -73.2746723458*pow(abstrketa, 1);
z0Res_1 += 681.709235238*pow(abstrketa, 2);
z0Res_1 += -1407.05808764*pow(abstrketa, 3);
z0Res_1 += 1654.33004356*pow(abstrketa, 4);
z0Res_1 += -789.708938945*pow(abstrketa, 5);
z0Res_1 += 135.267082392*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.8) {
    if (trkpt>=2.5 && trkpt<5.0) {
z0Res_1 += 133.246023237*pow(abstrketa, 0);
z0Res_1 += -191.291135205*pow(abstrketa, 1);
z0Res_1 += 918.100364604*pow(abstrketa, 2);
z0Res_1 += -1639.1040357*pow(abstrketa, 3);
z0Res_1 += 1573.09986733*pow(abstrketa, 4);
z0Res_1 += -667.738167423*pow(abstrketa, 5);
z0Res_1 += 104.609076007*pow(abstrketa, 6);
    }
  }

  if (abstrketa<2.8) {
    if (trkpt>=5.0 && trkpt<10.0) {
z0Res_1 += 89.7200951197*pow(abstrketa, 0);
z0Res_1 += -261.963788134*pow(abstrketa, 1);
z0Res_1 += 1056.30210764*pow(abstrketa, 2);
z0Res_1 += -1767.85750599*pow(abstrketa, 3);
z0Res_1 += 1513.62235614*pow(abstrketa, 4);
z0Res_1 += -589.965886974*pow(abstrketa, 5);
z0Res_1 += 85.5295670405*pow(abstrketa, 6);
    }
  }

  if (abstrketa<1.68) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_1 += 64.7779799702*pow(abstrketa, 0);
z0Res_1 += -226.472169916*pow(abstrketa, 1);
z0Res_1 += 709.90880947*pow(abstrketa, 2);
z0Res_1 += -869.568795287*pow(abstrketa, 3);
z0Res_1 += 478.041578904*pow(abstrketa, 4);
z0Res_1 += -84.2426815131*pow(abstrketa, 5);
    }
  }

  if (abstrketa<1.68) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_1 += 48.2482714166*pow(abstrketa, 0);
z0Res_1 += -233.216132233*pow(abstrketa, 1);
z0Res_1 += 676.407736134*pow(abstrketa, 2);
z0Res_1 += -782.158960225*pow(abstrketa, 3);
z0Res_1 += 380.66063259*pow(abstrketa, 4);
z0Res_1 += -54.4496108594*pow(abstrketa, 5);
    }
  }

  double z0Res_2 = 0;




  if (abstrketa>=1.58 && abstrketa<2.8) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_2 += -992.995981587*pow(abstrketa, 0);
z0Res_2 += 2013.16092718*pow(abstrketa, 1);
z0Res_2 += -1152.07637508*pow(abstrketa, 2);
z0Res_2 += 230.869056844*pow(abstrketa, 3);
    }
  }

  if (abstrketa>=1.58 && abstrketa<2.8) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_2 += 273.421724686*pow(abstrketa, 0);
z0Res_2 += -149.16282494*pow(abstrketa, 1);
z0Res_2 += 44.547646945*pow(abstrketa, 2);
z0Res_2 += -0.297127038185*pow(abstrketa, 3);
    }
  }

  double z0Res_3 = 0;






  double z0Res_4 = 0;






  if (debug) {
    printf("z0Res_1 = %f\n", z0Res_1);
    printf("z0Res_2 = %f\n", z0Res_2);
    printf("z0Res_3 = %f\n", z0Res_3);
    printf("z0Res_4 = %f\n", z0Res_4);
  }

  double z0Res = -1.;
  if (abstrketa<0) {{ z0Res = -1.; }}
  if (abstrketa>=0 && abstrketa<2.8 && trkpt>=1.0 && trkpt<1.5) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<2.8 && trkpt>=1.5 && trkpt<2.5) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<2.8 && trkpt>=2.5 && trkpt<5.0) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<2.8 && trkpt>=5.0 && trkpt<10.0) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<1.68 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.58 && abstrketa<2.8 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.58 && abstrketa<1.68 && trkpt>=10.0 && trkpt<20.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }
  if (abstrketa>=0 && abstrketa<1.68 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_1; }
  if (abstrketa>=1.58 && abstrketa<2.8 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_2; }
  if (abstrketa>=1.58 && abstrketa<1.68 && trkpt>=20.0 && trkpt<100.0) {
    z0Res = (z0Res_1+z0Res_2)/2. ;
  }

  return z0Res;
}
