double getZ0ResParam_N(float abstrketa, float trkpt, bool debug=0) {

  double z0Res_1 = 0;
  if (abstrketa<4.0) {
    if (trkpt>=1.0 && trkpt<1.5) {
z0Res_1 += 67.4347140702*pow(abstrketa, 0);
z0Res_1 += -96.1527720345*pow(abstrketa, 1);
z0Res_1 += 441.165428334*pow(abstrketa, 2);
z0Res_1 += -657.247358059*pow(abstrketa, 3);
z0Res_1 += 500.651870444*pow(abstrketa, 4);
z0Res_1 += -158.454191843*pow(abstrketa, 5);
z0Res_1 += 18.1190353423*pow(abstrketa, 6);
    }
  }

  if (abstrketa<4.0) {
    if (trkpt>=1.5 && trkpt<2.5) {
z0Res_1 += 46.5532974478*pow(abstrketa, 0);
z0Res_1 += -73.8342788673*pow(abstrketa, 1);
z0Res_1 += 308.616871925*pow(abstrketa, 2);
z0Res_1 += -445.022971983*pow(abstrketa, 3);
z0Res_1 += 331.357363443*pow(abstrketa, 4);
z0Res_1 += -103.810983847*pow(abstrketa, 5);
z0Res_1 += 11.810352329*pow(abstrketa, 6);
    }
  }

  if (abstrketa<4.0) {
    if (trkpt>=2.5 && trkpt<5.0) {
z0Res_1 += 30.0078108226*pow(abstrketa, 0);
z0Res_1 += -55.7216422995*pow(abstrketa, 1);
z0Res_1 += 201.988427661*pow(abstrketa, 2);
z0Res_1 += -274.633609666*pow(abstrketa, 3);
z0Res_1 += 195.86777814*pow(abstrketa, 4);
z0Res_1 += -60.1492028747*pow(abstrketa, 5);
z0Res_1 += 6.7756812251*pow(abstrketa, 6);
    }
  }

  if (abstrketa<4.0) {
    if (trkpt>=5.0 && trkpt<10.0) {
z0Res_1 += 20.0951887348*pow(abstrketa, 0);
z0Res_1 += -44.3072303095*pow(abstrketa, 1);
z0Res_1 += 135.985328003*pow(abstrketa, 2);
z0Res_1 += -169.583490693*pow(abstrketa, 3);
z0Res_1 += 112.891891179*pow(abstrketa, 4);
z0Res_1 += -33.5006628594*pow(abstrketa, 5);
z0Res_1 += 3.71083218084*pow(abstrketa, 6);
    }
  }

  if (abstrketa<4.0) {
    if (trkpt>=10.0 && trkpt<20.0) {
z0Res_1 += 15.1249670495*pow(abstrketa, 0);
z0Res_1 += -38.3066810677*pow(abstrketa, 1);
z0Res_1 += 101.554775101*pow(abstrketa, 2);
z0Res_1 += -114.753384998*pow(abstrketa, 3);
z0Res_1 += 69.8332889124*pow(abstrketa, 4);
z0Res_1 += -19.7143961803*pow(abstrketa, 5);
z0Res_1 += 2.12971157478*pow(abstrketa, 6);
    }
  }

  if (abstrketa<4.0) {
    if (trkpt>=20.0 && trkpt<100.0) {
z0Res_1 += 11.6316611708*pow(abstrketa, 0);
z0Res_1 += -34.3074084329*pow(abstrketa, 1);
z0Res_1 += 77.1135460082*pow(abstrketa, 2);
z0Res_1 += -74.8537219818*pow(abstrketa, 3);
z0Res_1 += 38.2424699028*pow(abstrketa, 4);
z0Res_1 += -9.56423259511*pow(abstrketa, 5);
z0Res_1 += 0.964799275127*pow(abstrketa, 6);
    }
  }

  double z0Res_2 = 0;






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
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=1.0 && trkpt<1.5) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=1.5 && trkpt<2.5) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=2.5 && trkpt<5.0) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=5.0 && trkpt<10.0) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=10.0 && trkpt<20.0) { z0Res = z0Res_1; }
  if (abstrketa>=0 && abstrketa<4.0 && trkpt>=20.0 && trkpt<100.0) { z0Res = z0Res_1; }

  return z0Res;
}
