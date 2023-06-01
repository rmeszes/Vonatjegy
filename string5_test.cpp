/**
 * \file string5_test.cpp
 *
 * Tesztprogram az String osztály teszteléséhez.
 *
 */

#include <iostream>
#include <sstream>
#include <clocale>
#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
# include <windows.h>
#endif

#define ELKESZULT 11
#include "memtrace.h"     // a standard header-ek után kell lennie
#include "gtest_lite.h"
#include "string5.h"

using std::cout;
using std::cin;
using std::endl;


int string_tests() {

/**
 *  1. A paraméter nélkül hívható konstruktora üres sztringet hozzon étre!
 */
    TEST(Elkeszult1, construct) {
      String ures;
      if (ures.size() != 0)
        FAIL() << "Baj van a string hosszaval" << endl;
    } ENDM

/**
 *  2. Van olyan tagfüggvénye ( c_str() ), ami C-sztringgel, azaz nullával lezárt
 *     karaktersorozatra mutató pointerel (const char *) tér vissza.
 */
    TEST(Elkeszult2, emptyStr) {
      String ures;
      EXPECT_EQ((size_t)0, ures.size()) << "Baj van a string hosszaval" << endl;

      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << endl;
    } ENDM

/**
 * 3. Van olyan konstruktora, ami karakterből hoz létre sztringet.
 */
    TEST(Elkeszult3, fromChr) {
      char ch = 'a';
      String a(ch);
      EXPECT_EQ((size_t)1, a.size()) << "Baj van a string hosszaval" << endl;
      EXPECT_STREQ("a", a.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << endl;

      String b('a');    // konstansból is megy?
      EXPECT_STREQ("a", b.c_str()) << "Karakterbol sztring letrehozasa nem sikerult!" << endl;
    } ENDM

/**
 *  4. Van olyan konstruktora, ami C-sztringből (const char*) hoz létre sztringet.
 *  A const char* konstruktor lemásolja a sztringet, nem csak a pointert!
 */
    TEST(Elkeszult4, FromCstr) {
      const char *hello = "Hello sztring";
      String a(hello);
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van a string hosszaval" << endl;
      EXPECT_STREQ(hello, a.c_str()) << "C-sztringbol string letrehozasa nem sikerult!" << endl;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      char cpp[] = { 'C', '+', '+', '\0' };
      String b(cpp);
      cpp[0] = 'X';
      EXPECT_STRNE(cpp, b.c_str()) << "FromCstr: le kellett volna masolni a karaktertombot!" << endl;
    } ENDM

/**
 *  5. Az osztályból létrehozott objektum legyen átadható értékparaméterként!
 */
    TEST(Elkeszult5, ctor) {
      const char *hello = "Hello sztring";
      String a(hello);
      String b = a;
      EXPECT_EQ(strlen(hello), b.size()) << "Baj van a string hosszaval!" << endl;
      EXPECT_STREQ(hello, b.c_str()) << "Baj van a masolo konstruktorral!" << endl;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
         FAIL()  << "!** ctor: nem elegendo a pointereket lemasolni!" << endl;

      EXPECT_STREQ(hello, a.c_str()) << "Masolo kontsr. elromlott a forras!" << endl;
      EXPECT_EQ(strlen(hello), a.size()) << "Masolo konstr. alatt elromlott a forras hossza!" << endl;

      const String c = a;
      String d = c;     // konstansból is megy?
      EXPECT_STREQ(hello, d.c_str()) << "Baj van a masolo konstruktorral" << endl;
    } ENDM

    TEST(Elkeszult5, ctor_nullptr) {
      String d0;
      String ures = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, ures.size()) << "Baj van a string hosszaval" << endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", ures.c_str()) << "Nem ures sztring jott letre" << endl;
    } ENDM

/**
 *  6. Támogassa a többszörös értékadást (b = a = a)!
 */
    TEST(Elkeszult6, opAssign) {
      const char *hello = "Hello sztring";
      String a(hello);
      String b("Duma1"), c("Duma2");
      EXPECT_STRNE(a.c_str(), b.c_str());
      a = a;
      EXPECT_EQ(strlen(hello), a.size()) << "Baj van az ertekadassal: a = a hossz" << endl;
      EXPECT_STREQ(hello, a.c_str()) << "Baj van az ertekadassal: a = a" << endl;
      c = b = a;

      /// Ellenőrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
      if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
         FAIL()  << "!** op=: nem elegendo a pointereket lemasolni!" << endl;

      EXPECT_EQ(strlen(hello), a.size()) << "Ertekedasnal elromlott a forras hossza!" << endl;
      EXPECT_STREQ(hello, a.c_str()) << "Ertekadasnal elromlott a forras!" << endl;
      EXPECT_EQ(strlen(hello), b.size()) << "Ertekedas: nem jo a hossz!" << endl;
      EXPECT_STREQ(hello, b.c_str()) << "Ertekadas nem sikerult!" << endl;
      EXPECT_EQ(strlen(hello), c.size()) << "Ertekedas: nem jo a hossz!" << endl;
      EXPECT_STREQ(hello, c.c_str()) << "Ertekadas nem sikerult!" << endl;

      const String d("Konst.");
      c = d;        // konstansból is megy?
      EXPECT_EQ(c.size(), c.size()) << "Ertekedas konstansbol: nem jo a hossz!" << endl;
      EXPECT_STREQ(d.c_str(), c.c_str()) << "Ertekadas konstansbol nem sikerult!" << endl;
    } ENDM

    TEST(Elkeszult6, opAssign_nullptr) {
      String d0;
      String c = d0;     // üres sztringet is le tudja másolni?
      EXPECT_EQ((size_t)0, c.size()) << "Baj van a string hosszaval" << endl;
      /// Ellenőrizzük, hogy üres sztringet ("") kaptunk-e vissza?
      EXPECT_STREQ("", c.c_str()) << "Nem ures sztring jott letre" << endl;

    } ENDM

/**
 *  7. Legyenek olyan operátorai (operator+), amivel a sztring végéhez sztringet
 *     és karaktert lehet fűzni!
 */
    TEST(Elkeszult7, strPlusStr) {
      String a("Hello ");
      String b("sztring");
      String c;
      c = a + b;
      EXPECT_STREQ("Hello sztring", c.c_str()) << "Nem sikerult a + String muvelet!" << endl;
      EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;
      EXPECT_STREQ("sztring", b.c_str()) << "A + muvelet elrontja a jobb oldalt?" << endl;
      const String a1 = a, b1 = b;

      String c1;
      c1 = a1 + b1;          // konstansból is megy?
      EXPECT_STREQ("Hello sztring", c1.c_str()) << "Nem sikerult a + String muvelet!" << endl;
    } ENDM

    TEST(Elkeszult7, strPlusChr) {
      String a("Hello ");
      String b;
      b = a + 'B';
      EXPECT_STREQ("Hello B", b.c_str()) << "Nem sikerult a + char muvelet!" << endl;
      EXPECT_STREQ("Hello ", a.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;

      const String a1 = a;
      String b1;
      b1 = a1 + 'B';          // konstansból is megy?
      EXPECT_STREQ("Hello B", b1.c_str()) << "Nem sikerult a + char muvelet!" << endl;
      EXPECT_STREQ("Hello ", a1.c_str()) << "A + muvelet elrontja a bal oldalt?" << endl;

    } ENDM

/**
 *  9. A tárolt a karakterek legyenek elérhetőek a szokásos módon indexeléssel!
 *     Az indexeléssel elért elem legyen használható balértékként is!
 *     A konstans objektumok is legyenek indexelhetők.
 *     Az indexelés operátor hiba esetén dobjon const char * kivételt!
 */
    TEST(Elkeszult9, index) {
      String a("Hello 678");
      EXPECT_NO_THROW(a[0]);
      EXPECT_NO_THROW(a[7]);
      EXPECT_NO_THROW(a[8]);
      EXPECT_THROW(a[9], const char *);
      EXPECT_THROW(a[-1], const char *);
      EXPECT_EQ('7', a[7]);
      a[7] = '.';
      EXPECT_EQ('.', a[7]);
    } ENDM

/**
 * 10. Készítsen olyan << operátort, amivel egy sztring kiírható egy ostream típusú
 *     objektumra!
 */
    TEST(Elkeszult10, insert) {
      String a("Hello sztring");
      std::stringstream ss;
      ss << a;
      EXPECT_STREQ("Hello sztring", ss.str().c_str());
    } ENDM

/**
 * 11. Készítsen olyan fűzhető >> operátort, amivel be tud olvasni egy szót egy sztring-be!
 *     A beolvasó működjön úgy, mint a scanf %s, azaz a szó végét white space határolja!
 *     A szó eleji white space karaktereket pedig el kell dobni.
 *    *Megj: az istream wshite space kezelése a flags() tagfüggvénnyel szabályozható
 */
    TEST(Elkeszult11, extract) {
      String a("Hello   sztring \n Lajos12");
      std::stringstream ss;
      ss << a;
      String in1, in2, in3;
      ss >> in1 >> in2;         // fűzhetőnek kell lenni
      while (ss >> in3);        // csak kicsit gonosz a teszt !
      EXPECT_STREQ("Hello", in1.c_str());
      EXPECT_STREQ("sztring", in2.c_str());
      EXPECT_STREQ("Lajos12", in3.c_str());
    } ENDM
    return 0;
}
